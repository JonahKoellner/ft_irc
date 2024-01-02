/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Database.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:57:30 by jkollner          #+#    #+#             */
/*   Updated: 2024/01/02 17:00:30 by jkollner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Database.hpp"

#include <map>
#include <utility>
#include "Database.hpp"

Database::Database(std::string password) {
	_password = password;
}

int	Database::create_user(int userSocket, std::string ip) {
	if (this->_users.find(userSocket) != this->_users.end())
		return (1);
	this->_users.insert(std::make_pair(userSocket, User(userSocket, ip)));
	return (0);
}

int	Database::delete_channel(std::string channelName) {
	return (this->_chats.erase(channelName));
}

int Database::remove_user_channel(int userSocket, std::string userChannel) {
	// remove user from channel
	//std::string user_channel = this->_users.find(userSocket)->second.get_channel();

	//for (auto i : this->_chats)
		//std::cout << i.first << std::endl;

	Chat chat = this->_chats.find(userChannel)->second; //// BUGUGUGUGUGUGUGUGU!!!!!!! ! ! ! TODO
	if (userChannel != "") {
		chat.remove_user(userSocket);
		this->_users.find(userSocket)->second.set_channel("");
		std::cout << " setting channel" << std::endl;
		if (chat.size() == 0)
			this->_chats.erase(userChannel);
		// If user is operator, remove operator status
		if (chat._operators.find(userSocket) != chat._operators.end())
			chat.remove_operator(userSocket);
		return (0);
	}
	return (1);
}

int	Database::delete_user(int userSocket) {
	return (this->_users.erase(userSocket) > 0 ? 1 : 0);
}

int Database::set_password(std::string new_password) {
	this->_password = new_password;
	return (0);
}

int Database::create_channel(std::string channel_name) {
	if (this->_chats.find(channel_name) != this->_chats.end())
		return (1); // channel already exists
	this->_chats.insert(std::make_pair(channel_name, Chat(channel_name)));
	return (0);
}

int Database::set_channel_operator(int userSocket, std::string channelName) {
	this->_chats.find(channelName)->second.set_operator(userSocket);
	return (0);
}

int Database::set_user_verification(bool verified, int userSocket) {
	this->_users.find(userSocket)->second.set_verified(verified);
	return (0);
}

int Database::add_user_channel(int userSocketFD, std::string channelName) {
	this->_chats.find(channelName)->second.add_user(this->_users.find(userSocketFD)->second);
	this->_users.find(userSocketFD)->second.set_channel(channelName);
	return (0);
}

User Database::get_user(int userSocketFD) {
	std::unordered_map<int, User>::iterator it = this->_users.find(userSocketFD);
	if (it == this->_users.end())
		return (User(-1));
	return (it->second);
}

int Database::get_user_fd(std::string userName) {
	for (std::unordered_map<int, User>::iterator it = this->_users.begin(); it != this->_users.end(); it++) {
		if (it->second.get_user_name() == userName)
			return (it->second.get_socket_fd());
	}
	return (-1);
}

int Database::set_channel_name(std::string oldChannelName, std::string newChannelName) {
	this->_chats.find(oldChannelName)->second.set_name(newChannelName);
	return (0);
}

std::unordered_map<int, int> Database::get_channel_user(std::string channelName) {
	std::unordered_map<std::string, Chat>::iterator it = this->_chats.find(channelName);
	if (it == this->_chats.end())
		return (std::unordered_map<int, int>());
	return (it->second.get_users());
}

int Database::set_user_nickName(int userSocketFD, std::string nickName) {
	return (this->_users.find(userSocketFD)->second.set_user_nickName(nickName));
}

int	Database::set_user_User(int userSocketFD, std::string userName, std::string nickName, std::string realName) {
	return (this->_users.find(userSocketFD)->second.set_user(userName, nickName, realName));
}

Chat Database::get_channel(std::string channelName) {
	return (this->_chats.find(channelName)->second);
}

std::unordered_map<std::string, Chat> Database::get_all_channel( void ) {
	return (this->_chats);
}

std::unordered_map<int, User> Database::get_all_users( void ) {
	return (this->_users);
}

Database::~Database() {
	// delete all chats
	this->_chats.clear();
	// delete all users
	this->_users.clear();
}
