/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreidenb <mreidenb@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:39:31 by mreidenb          #+#    #+#             */
/*   Updated: 2024/01/01 22:16:27 by mreidenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commander.hpp"

int	Commander::handle_pass() {
	bool verified = Executer(this->_database).check_password(this->_commandArguments[0]);
	Executer(this->_database).set_user_verified(this->_userSocket_FD, verified);
	if (verified)
		Executer(this->_database).send_user_message(this->_userSocket_FD, std::string("You are now verified\r\n"));
	else
		Executer(this->_database).send_user_message(this->_userSocket_FD, std::string("Wrong password\r\n"));
	return (0);
}

int	Commander::handle_nick() {
	Executer ex(this->_database);
	std::string name = ex.get_user(this->_userSocket_FD).get_user_name();
	std::string chan = ex.get_user(this->_userSocket_FD).get_channel();
	ex.send_message_chat(chan, std::string(name + " --> " + this->_commandArguments[0] + "\r\n"));
	return (ex.set_userName(this->_userSocket_FD, this->_commandArguments[0]));
}

int	Commander::handle_privmsg() {
	Executer ex(this->_database);
	if (this->_commandArguments.size() < 2)
		return (1);
	if (this->_commandArguments[0][0] != '#')
		return (ex.send_private_message(this->_userSocket_FD, this->_commandArguments[0], this->_commandArguments[1]));
	std::string name = ex.get_user(this->_userSocket_FD).get_user_name();
	std::string chan = ex.get_user(this->_userSocket_FD).get_channel();
	std::string message = name + " --> " + this->_commandArguments[0] + ": " + this->_commandArguments[1] + "\r\n";
	ex.send_message_chat(chan, message);
	ex.send_private_message(this->_userSocket_FD, this->_commandArguments[0], message);
	return (0);
}

int	Commander::handle_join() {
	Executer ex(this->_database);
	if (this->_commandArguments.size() < 1)
		return (1);
	if (this->_commandArguments[0] == ":")
		return (ex.remove_user_channel(this->_userSocket_FD));
	if (this->_commandArguments[0][0] != '#')
		return (ex.send_user_message(this->_userSocket_FD, std::string("Invalid channel name\r\n")));
	std::string name = ex.get_user(this->_userSocket_FD).get_user_name();
	std::string chan = ex.get_user(this->_userSocket_FD).get_channel();
	std::string message = name + " has joined " + this->_commandArguments[0] + "\r\n";
	ex.send_message_chat(chan, message);
	return (ex.join_channel(this->_userSocket_FD, this->_commandArguments[0]));
}

int	Commander::handle_leave() {
	Executer ex(this->_database);
	std::string name = ex.get_user(this->_userSocket_FD).get_user_name();
	std::string chan = ex.get_user(this->_userSocket_FD).get_channel();
	std::string message = name + " has left " + chan + "\r\n";
	ex.send_message_chat(chan, message);
	return (ex.remove_user_channel(this->_userSocket_FD));
}

int	Commander::handle_quit() {
	Executer ex(this->_database);
	std::string name = ex.get_user(this->_userSocket_FD).get_user_name();
	std::string chan = ex.get_user(this->_userSocket_FD).get_channel();
	std::string message = name + " has quit\r\n";
	ex.send_message_chat(chan, message);
	ex.remove_user_channel(this->_userSocket_FD);
	//pollfds.erase(pollfds.begin() + i);
	//close(this->_userSocket_FD); // TODO
	return (ex.delete_user(this->_userSocket_FD));
}

int	Commander::handle_list() {
	Executer ex(this->_database);
	return (ex.list_channel(this->_userSocket_FD, ex.get_user(this->_userSocket_FD).get_user_name()));
}

int	Commander::handle_ping() {
	Executer ex(this->_database);
	return (ex.handle_ping(this->_userSocket_FD, this->_commandArguments[0]));
}

int Commander::handle_user() {
	Executer ex(this->_database);
	if (this->_commandArguments.size() < 1)
		return (1);
	std::string userName = this->_commandArguments[0];
	std::string nickName = this->_commandArguments[1];
	std::string realName = (this->_commandArguments[3].substr(1)) + " " + (this->_commandArguments[4]);
	if (!ex.set_user_User(this->_userSocket_FD, userName, nickName, realName))
		return (ex.send_server_message(this->_userSocket_FD, "Welcome to the Internet Relay Network " + userName + "\r\n", "001"));
	return ex.send_server_message(this->_userSocket_FD, "You may not reregister\r\n", "462");
}