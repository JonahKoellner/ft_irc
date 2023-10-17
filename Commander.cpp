/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commander.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:51:11 by jonahkollne       #+#    #+#             */
/*   Updated: 2023/10/17 13:53:12 by jkollner         ###   ########.fr       */
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

//int Commander::send_server_message(std::string message, Chat chat) {
//	std::string server_message = "[Server]: " + message + "\r\n";
//	std::cout << "message" << std::endl;
//	std::vector<User> users = chat.get_users();
//    for (std::vector<User>::iterator it = users.begin(); it != users.end(); it++) {
//			if (send(it->get_socket_fd(), server_message.c_str(), server_message.length(), 0) == -1) {
//				std::cerr << "Error sending message to user " << it->get_user_name() << std::endl;
//				return (1);
//		}
//	}
//	return (0);
//}

Commander::Commander(std::string commandString, int userSocket_FD, Database &database) : _database(database) {
	this->_commandString = commandString;
	this->_userSocket_FD = userSocket_FD;
}

//Commander::Commander() : _user(*(new User(0))), _userChats(*(new std::unordered_map<std::string, Chat>())){}

//Commander::Commander(std::string commandString, User &user, std::unordered_map<std::string, Chat> &user_chat) : _user(user), _userChats(user_chat) {
//	this->_commandString = commandString;
//}

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

	std::string full_sentence = "";
	for (int i = 0; i < commandTokens.size(); i++)
		full_sentence += commandTokens[i] + " ";

	//if (this->_user.get_verification()) {
	if (Executer(this->_database).get_user(this->_userSocket_FD).get_verification()) {
		if (commandTokens[0] == "/JOIN")
			ret_val = Executer(this->_database).join_channel(this->_userSocket_FD, commandTokens[1]);
		else if (commandTokens[0] == "/ME")
			ret_val = Executer(this->_database).send_message_user_chat(this->_userSocket_FD, full_sentence);
		else if (commandTokens[0] == "/NICK")
			// check in executer if the name is already taken. NO DUPLICATE NAMES
			ret_val = Executer(this->_database).set_userName(this->_userSocket_FD, commandTokens[1]);
		//else if (commandTokens[0] == "/USER")
		//else if (commandTokens[0] == "/PASS")
		//else if (commandTokens[0] == "/CAP")
		//else if (commandTokens[0] == "/PING")
		//else if (commandTokens[0] == "/PONG")
		//else if (commandTokens[0] == "/PRIVMSG")
		//else if (commandTokens[0] == "/NOTICE")
		//else if (commandTokens[0] == "/QUIT")
		//else if (commandTokens[0] == "/PART")
		//else if (commandTokens[0] == "/TOPIC")
		//else if (commandTokens[0] == "/MODE")
		//else if (commandTokens[0] == "/WHO")
		//else if (commandTokens[0] == "/WHOIS")
		//else if (commandTokens[0] == "/LIST")
		//else if (commandTokens[0] == "/INVITE")
		//else if (commandTokens[0] == "/KICK")
		//else if (commandTokens[0] == "/KILL")
		//else if (commandTokens[0] == "/AWAY")
		//else if (commandTokens[0] == "/OPER")
		//else if (commandTokens[0] == "/SQUIT")
		else
			ret_val = -1; // "unknown" error code
	} else if (commandTokens[0] == "/PASS")
		Executer(this->_database).set_user_verified(this->_userSocket_FD, true);
		// let executer try the password and get the result
		//ret_val = 0;
	else
		ret_val = 1;
	return (ret_val);
}
