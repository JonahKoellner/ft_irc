/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commander.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:51:11 by jonahkollne       #+#    #+#             */
/*   Updated: 2023/10/23 10:30:35 by jkollner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Command
/*
	give user and command string to the command function
	command function give the strng to the parser
	parer returns the comman name
	command excutes the given command from the parser
*/

#include "Commander.hpp"

Commander::Commander(std::string commandString, int userSocket_FD, Database &database) : _database(database) {
	this->_commandString = commandString;
	this->_userSocket_FD = userSocket_FD;
}

int Commander::execute() {
	std::vector<std::string> command_tokens = this->parse_command(this->_commandString);
	return (this->execute_command(command_tokens));
}

std::vector<std::string> Commander::parse_command(std::string commandString) {
	std::vector<std::string> command_tokens;
	const char* delimiters = " \r\n";
	char *token = std::strtok((char *)commandString.c_str(), delimiters);
	while (token)
	{
		command_tokens.push_back(std::string(token));
		token = std::strtok(nullptr, delimiters);
	}
	//for (int i = 0; i < command_tokens.size(); i++)
	//	std::cout << "argument: " << command_tokens[i] << std::endl;
	return (command_tokens);
}

int Commander::execute_command(std::vector<std::string> commandTokens) {
	int	ret_val;

	if (commandTokens.size() == 0)
		return (1);
	for (std::string::iterator it = commandTokens[0].begin(); it != commandTokens[0].end(); ++it)
		*it = toupper(*it);



	if (Executer(this->_database).get_user(this->_userSocket_FD).get_verification()) {
		if (commandTokens[0] == "/JOIN")
			ret_val = Executer(this->_database).join_channel(this->_userSocket_FD, commandTokens[1]);
		else if (commandTokens[0] == "/ME")
		{
			std::string full_sentence = "";
			for (int i = 1; i < commandTokens.size(); i++)
				full_sentence += commandTokens[i] + " ";
			// could also be a check for the first \n and replace. Could protect against people putting a '\n' in their message
			full_sentence.pop_back();
			full_sentence += "\r\n";
			ret_val = Executer(this->_database).send_message_user_chat(this->_userSocket_FD, full_sentence);
		}
		else if (commandTokens[0] == "/NICK") {
			Executer ex(this->_database);
			std::string name = ex.get_user(this->_userSocket_FD).get_user_name();
			std::string chan = ex.get_user(this->_userSocket_FD).get_channel();
			ex.send_message_chat(chan, std::string(name + " --> " + commandTokens[1] + "\r\n"));
			ret_val = ex.set_userName(this->_userSocket_FD, commandTokens[1]);
		}
		//else if (commandTokens[0] == "/USER")
		//else if (commandTokens[0] == "/PASS")
		//else if (commandTokens[0] == "/CAP")
		//else if (commandTokens[0] == "/PING")
		//else if (commandTokens[0] == "/PONG")
		else if (commandTokens[0] == "/PRIVMSG" && Executer(this->_database).get_user(this->_userSocket_FD).get_channel() != "") {
			std::string full_sentence = "";
			for (int i = 2; i < commandTokens.size(); i++)
				full_sentence += commandTokens[i] + " ";
			// could also be a check for the first \n and replace. Could protect against people putting a '\n' in their message
			full_sentence.pop_back();
			full_sentence += "\r\n";
			Executer(this->_database).send_private_message(this->_userSocket_FD, commandTokens[1], full_sentence);
		}
		//else if (commandTokens[0] == "/NOTICE")
		else if (commandTokens[0] == "/QUIT") {
			Executer ex(this->_database);
			ex.send_message_chat(ex.get_user(this->_userSocket_FD).get_channel(), "User" + std::to_string(this->_userSocket_FD) + " has left the chat.\r\n");
			ex.remove_user_channel(this->_userSocket_FD);
			ex.delete_user(this->_userSocket_FD);
			//pollfds.erase(pollfds.begin() + i);
			//close(this->_userSocket_FD); // TODO
		}
		else if (commandTokens[0] == "/LIST"){
			Executer(this->_database).list_user_channel(this->_userSocket_FD);
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
	} else if (commandTokens[0] == "/PASS") {
		bool verified = Executer(this->_database).check_password(commandTokens[1]);
		Executer(this->_database).set_user_verified(this->_userSocket_FD, verified);
		if (verified)
			Executer(this->_database).send_user_message(this->_userSocket_FD, std::string("You are now verified\r\n"));
		else
			Executer(this->_database).send_user_message(this->_userSocket_FD, std::string("Wrong password\r\n"));
		ret_val = 0;
	}
	else {
		Executer(this->_database).send_user_message(this->_userSocket_FD, std::string("You need to be verified to use commands (/pass <password>)\r\n"));
		ret_val = 1;
	}
	return (ret_val);
}
