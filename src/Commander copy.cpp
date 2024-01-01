/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commander copy.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreidenb <mreidenb@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:51:11 by jonahkollne       #+#    #+#             */
/*   Updated: 2023/11/28 18:43:39 by mreidenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Command
/*
	give user and command string to the command function
	command function give the strng to the parser
	parer returns the comman name
	command excutes the given command from the parser
*/

#include "../include/Commander copy.hpp"

Commander::Commander(std::string commandString, int userSocket_FD, Database &database) : _database(database) {
	this->_commandString = commandString;
	this->_userSocket_FD = userSocket_FD;
	this->_commandTokens = this->parse_command(commandString);
}

// int Commander::execute() {
// 	// std::vector<std::string> command_tokens = this->parse_command(this->_commandString);
// 	return (this->execute_command(command_tokens));
// }

std::vector<std::string> Commander::parse_command(std::string commandString) {
	std::vector<std::string> command_tokens;
	const char* delimiters = " \r\n";
	char *token = std::strtok((char *)commandString.c_str(), delimiters);
	while (token)
	{
		command_tokens.push_back(std::string(token));
		token = std::strtok(nullptr, delimiters);
	}
	for (size_t i = 0; i < command_tokens.size(); i++)
		std::cout << "argument: " << command_tokens[i] << std::endl;
	command_tokens.erase(command_tokens.begin());
	// this->_commandArguments = command_tokens;
	return (command_tokens);
}
// int Commander::execute_command() {
int Commander::execute_command(std::vector<std::string> commandTokens) {
	int	ret_val = 0;

	if (commandTokens.size() == 0)
		return (1);
	for (std::string::iterator it = commandTokens[0].begin(); it != commandTokens[0].end(); ++it)
		*it = toupper(*it);
	if (commandTokens[0] == "PASS") {
		bool verified = Executer(this->_database).check_password(commandTokens[1]);
		Executer(this->_database).set_user_verified(this->_userSocket_FD, verified);
		if (verified)
			Executer(this->_database).send_user_message(this->_userSocket_FD, std::string("You are now verified\r\n"));
		else
			Executer(this->_database).send_user_message(this->_userSocket_FD, std::string("Wrong password\r\n"));
		ret_val = 0;
	}
	else if (commandTokens[0] == "PING")
	{
		Executer ex(this->_database);
		ret_val = ex.handle_ping(this->_userSocket_FD, commandTokens[1]);
	}
	else if (Executer(this->_database).get_user(this->_userSocket_FD).get_verification()) {
		if (commandTokens[0] == "JOIN")
		{
			if (commandTokens.size() == 1)
				ret_val = Executer(this->_database).join_channel(this->_userSocket_FD, "");
			else if (commandTokens.size() == 2 && commandTokens[1][0] == '#')
				ret_val = Executer(this->_database).join_channel(this->_userSocket_FD, commandTokens[1]);
			else
				ret_val = Executer(this->_database).send_user_message(this->_userSocket_FD, std::string("Invalid channel name, use #<channelName>\r\n"));
		}
		else if (commandTokens[0] == "PRIVMSG" 
			&& commandTokens[1] == Executer(this->_database).get_user(this->_userSocket_FD).get_channel())
		{
			std::string full_sentence = "";
			for (size_t i = 0; i < commandTokens.size(); i++)
				full_sentence += commandTokens[i] + " ";
			// could also be a check for the first \n and replace. Could protect against people putting a '\n' in their message
			full_sentence.pop_back();
			full_sentence += "\r\n";
			ret_val = Executer(this->_database).send_message_user_chat(this->_userSocket_FD, full_sentence);
			std::cout << "full sentence: " << full_sentence << std::endl;
		}
		else if (commandTokens[0] == "NICK") {
			Executer ex(this->_database);
			std::string name = ex.get_user(this->_userSocket_FD).get_user_name();
			std::string chan = ex.get_user(this->_userSocket_FD).get_channel();
			ex.send_message_chat(chan, std::string(name + " --> " + commandTokens[1] + "\r\n"));
			ret_val = ex.set_userName(this->_userSocket_FD, commandTokens[1]);
		}
		//else if (commandTokens[0] == "/USER")
		//else if (commandTokens[0] == "/PASS")
		//else if (commandTokens[0] == "/CAP")
		//else if (commandTokens[0] == "/PONG")
		else if (commandTokens[0] == "PRIVMSG" && Executer(this->_database).get_user(this->_userSocket_FD).get_channel() != "") {
			std::string full_sentence = "";
			for (size_t i = 2; i < commandTokens.size(); i++)
				full_sentence += commandTokens[i] + " ";
			// could also be a check for the first \n and replace. Could protect against people putting a '\n' in their message
			full_sentence.pop_back();
			full_sentence += "\r\n";
			Executer(this->_database).send_private_message(this->_userSocket_FD, commandTokens[1], full_sentence);
			std::cout << "commandTokens[1]: " << commandTokens[1] << std::endl;
			std::cout << "full sentence low: " << full_sentence << "channel :" << Executer(this->_database).get_user(this->_userSocket_FD).get_channel() << std::endl;
		}
		//else if (commandTokens[0] == "/NOTICE")
		else if (commandTokens[0] == "QUIT") {
			Executer ex(this->_database);
			ex.send_message_chat(ex.get_user(this->_userSocket_FD).get_channel(), "User" + std::to_string(this->_userSocket_FD) + " has left the chat.\r\n");
			ex.remove_user_channel(this->_userSocket_FD);
			ex.delete_user(this->_userSocket_FD);
			//pollfds.erase(pollfds.begin() + i);
			//close(this->_userSocket_FD); // TODO
		}
		else if (commandTokens[0] == "LIST"){
			Executer ex(this->_database);
			if (ex.get_user(this->_userSocket_FD).get_channel() != "")
				ex.list_user_channel(this->_userSocket_FD);
			else if (ex.get_user(this->_userSocket_FD).get_channel() == "")
				ex.list_channel(this->_userSocket_FD);
		}
		//else if (commandTokens[0] == "/PART")
		//else if (commandTokens[0] == "/TOPIC")
		//else if (commandTokens[0] == "/MODE")
		//else if (commandTokens[0] == "/WHO")
		//else if (commandTokens[0] == "/WHOIS")
		//else if (commandTokens[0] == "/INVITE")
		//else if (commandTokens[0] == "/KICK")
		//else if (commandTokens[0] == "/KILL")
		//else if (commandTokens[0] == "/AWAY")
		//else if (commandTokens[0] == "/OPER")
		//else if (commandTokens[0] == "/SQUIT")
		else {
			Executer(this->_database).send_user_message(this->_userSocket_FD, std::string("Unknown command\r\n"));
			ret_val = -1; // "unknown" error code
		}
	}
	else {
		Executer(this->_database).send_user_message(this->_userSocket_FD, std::string("You need to be verified to use commands (/quote PASS <password>)\r\n"));
		ret_val = 1;
	}
	return (ret_val);
}