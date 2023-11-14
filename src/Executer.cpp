/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executer.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreidenb <mreidenb@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:51:25 by jonahkollne       #+#    #+#             */
/*   Updated: 2023/11/14 20:58:48 by mreidenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Executer.hpp"

Executer::Executer(Database &database) : _database(database){
	_blackListedNames.insert("server");
	_blackListedChannelNames.insert("");
}

int	Executer::send_message_user_chat(int userSocketFD, std::string message) {
	std::string channel_name = this->_database.get_user(userSocketFD).get_channel();
	std::unordered_map<int, int> users = this->_database.get_channel_user(channel_name);
	message = this->_database.get_user(userSocketFD).get_user_name() + ": " + message;
	for (std::unordered_map<int, int>::iterator it = users.begin(); it != users.end(); it++) {
		if (!(it->first == userSocketFD)) {
			if (send_user_message(it->first, message))
				return (1);
		}
	}
	return (0);
}

int	Executer::send_message_chat(std::string channelName, std::string message) {
	std::unordered_map<int, int> users = this->_database.get_channel_user(channelName);
	for (std::unordered_map<int, int>::iterator it = users.begin(); it != users.end(); it++) {
			if (send_user_message(it->first, message))
				return (1);
	}
	return (0);
}

int Executer::send_private_message(int userSocketFD, std::string targetUserName, std::string message) {
	int targetFD = this->_database.get_user_fd(targetUserName);
	User targetUser = this->_database.get_user(targetFD);

	if (targetFD == -1 || targetUser.get_socket_fd() == -1) {
		send_user_message(userSocketFD, std::string("User is not in the same channel\r\n"));
		return (1);
	}
	std::string channelName = this->_database.get_user(userSocketFD).get_channel();
	if (channelName == "" || channelName != this->_database.get_user(userSocketFD).get_channel()) {
		send_user_message(userSocketFD, std::string("User is not in the same channel\r\n"));
		return (1);
	}
	message = "[private] " + this->_database.get_user(userSocketFD).get_user_name() + ": " + message;
	send_user_message(targetFD, message);
	return (0);
}

int Executer::list_user_channel(int userSocketFD) {
	User user = this->_database.get_user(userSocketFD);
	if (user.get_socket_fd() == -1)
		return (-1);
	std::unordered_map<int, int> users = this->_database.get_channel_user(user.get_channel());
	std::string list_message = "";
	list_message += ("Users in channel '" + user.get_channel() + "':\n");
	for (std::unordered_map<int, int>::iterator it = users.begin(); it != users.end(); it++) {
		list_message+= ("\t-'" + this->_database.get_user(it->first).get_user_name() + "'\n");
	}
	send_user_message(userSocketFD, (list_message + "\r\n"));
	return (0);
}

int	Executer::send_user_message(int	userSocketFD, std::string message) {
	struct pollfd pfd = {userSocketFD, POLLOUT, 0 };
	int poll_result = poll(&pfd, 1, -1);
	if (poll_result < 0) {
		std::cout << "Error in poll(): " << strerror(errno) << std::endl;
		return (1);
	}
	else if (poll_result == 0) {
		std::cout << "Timeout in poll()" << std::endl;
		return (1);
	}
	else if (pfd.revents & POLLOUT) {
		ssize_t bytes_sent = send(userSocketFD, message.c_str(), message.length(), 0);
		if (bytes_sent < 0) {
			std::cout << "Error sending message: " << strerror(errno) << std::endl;
			return (1);
		}
		else if (bytes_sent != static_cast<ssize_t>(message.length())) {
			std::cout << "Incomplete message sent" << std::endl;
			return (1);
		}
		else {
			return (0);
		}
	}
	else {
		std::cout << "Unknown error in poll()" << std::endl;
		return (1);
	}
}

int	Executer::join_channel(int userSocket_FD, std::string channel_name) {
	this->_database.create_channel(channel_name);
	this->_database.add_user_channel(userSocket_FD, channel_name);
	send_message_chat(channel_name, "User" + std::to_string(userSocket_FD) + " has joined the chat.\r\n");
	return (0);
}

int	Executer::set_userName(int userSocketFD, std::string userName) {
	if (_blackListedNames.find(userName) != _blackListedNames.end()) {
		send_user_message(userSocketFD, std::string("Username is blacklisted\r\n"));
		return (1);
	}
	//Chat channel = this->_database.get_user(userSocketFD).get_channel(); // if check for duplicate -> implement
	this->_database.set_user_name(userSocketFD, userName);
	return (0);
}

int Executer::set_channelName(int userSocketFD, std::string oldChannelName, std::string newChannelName) {
	if (_blackListedChannelNames.find(newChannelName) != _blackListedChannelNames.end()) {
		send_user_message(userSocketFD, std::string("Channel name is blacklisted\r\n"));
		return (1);
	}
	this->_database.set_channel_name(oldChannelName, newChannelName);
	return (0);
}

bool Executer::check_password(std::string password) {
	return (this->_database._password == password);
}

User Executer::get_user(int userSocket_FD) {
	return (this->_database.get_user(userSocket_FD));
}

int	Executer::set_user_verified(int userSocketFD, bool verified) {
	this->_database.set_user_verification(verified, userSocketFD);
	return (0);
}

int	Executer::create_user(int userSocket, std::string ip) {
	this->_database.create_user(userSocket, ip);
	return (0);
}

int Executer::delete_user(int userSocket) {
	this->_database.delete_user(userSocket);
	return (0);
}

int Executer::remove_user_channel(int userSocket) {
	this->_database.remove_user_channel(userSocket);
	return (0);
}

int Executer::list_channel( int userSocketFD ) {
	std::unordered_map<std::string, Chat> channels = this->_database.get_all_channel();
	std::string list_message = "";
	list_message += ("Channels:\n");
	for (std::unordered_map<std::string, Chat>::iterator it = channels.begin(); it != channels.end(); it++) {
		list_message+= ("\t-'" + it->first + "'\n");
	}
	list_message += "\r\n";
	return (send_user_message(userSocketFD, list_message));
}
