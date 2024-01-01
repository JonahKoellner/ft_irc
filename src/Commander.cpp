/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commander.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreidenb <mreidenb@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:51:11 by jonahkollne       #+#    #+#             */
/*   Updated: 2024/01/01 20:45:06 by mreidenb         ###   ########.fr       */
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
	// this->_commandString = commandString;
	std::cout << "Command string: " << commandString << std::endl;
	this->_userSocket_FD = userSocket_FD;
	this->_commandArguments = this->parse_command(commandString);
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
	this->_commandName = command_tokens[0];
	command_tokens.erase(command_tokens.begin());
	return (command_tokens);
}

// int Commander::execute_command(std::vector<std::string> commandTokens) {
int Commander::execute() {
	int	ret_val = 0;

	if (this->_commandArguments.size() == 0)
		return (1);
	for (std::string::iterator it = this->_commandName.begin(); it != this->_commandName.end(); ++it)
		*it = toupper(*it);
	if (this->_commandName == "PASS")
		return (this->handle_pass());
	else if (this->_commandName == "PING")
		return (this->handle_ping());
	if (this->_commandName == "CAP")
		return (this->handle_cap());
	else if (Executer(this->_database).get_user(this->_userSocket_FD).get_verification()) {
		if (this->_commandName == "JOIN")
			return (this->handle_join());
		else if (this->_commandName == "NICK")
			ret_val = this->handle_nick();
		else if (this->_commandName == "USER")
			ret_val = this->handle_user();
		//else if (this->_commandName == "/PASS")
		
		//else if (this->_commandName == "/PONG")
		else if (this->_commandName == "PRIVMSG")
			return (this->handle_privmsg());
		//else if (this->_commandName == "/NOTICE")
		else if (this->_commandName == "QUIT")
			return (this->handle_quit());
		else if (this->_commandName == "LIST")
			return (this->handle_list());
		//else if (this->_commandName == "/PART")
		//else if (this->_commandName == "/TOPIC")
		//else if (this->_commandName == "/MODE")
		//else if (this->_commandName == "/WHO")
		//else if (this->_commandName == "/WHOIS")
		//else if (this->_commandName == "/INVITE")
		//else if (this->_commandName == "/KICK")
		//else if (this->_commandName == "/KILL")
		//else if (this->_commandName == "/AWAY")
		//else if (this->_commandName == "/OPER")
		//else if (this->_commandName == "/SQUIT")
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
