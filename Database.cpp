/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Database.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:57:30 by jkollner          #+#    #+#             */
/*   Updated: 2023/10/17 14:21:33 by jkollner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Database.hpp"

#include <map>
#include <utility>
#include "Database.hpp"

Database::Database(std::string password) {
	_password = password;
}

int	Database::create_user(int userSocket) {
	std::pair<std::unordered_map<int, User>::iterator, bool> result =
		this->_users.insert(std::make_pair(userSocket, User(userSocket)));
	return (result.second ? 1 : 0);
}

int	Database::delete_channel(std::string channelName) {
	return (this->_chats.erase(channelName));
}

int Database::remove_user_channel(int userSocket) {
	// remove user from channel
	std::string user_channel = this->_users.find(userSocket)->second.get_channel();
	if (user_channel != "") {
		this->_chats.find(user_channel)->second.remove_user(userSocket);
		this->_users.find(userSocket)->second.set_channel("");
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
	std::pair<std::unordered_map<std::string, Chat>::iterator, bool> result =
		this->_chats.insert(std::make_pair(channel_name, Chat(channel_name)));
	return (result.second ? 1 : 0);
}

int Database::set_user_verification(bool verified, int userSocket) {
	this->_users.find(userSocket)->second.set_verified(verified);
	return (0);
}

int Database::add_user_channel(int userSocketFD, std::string channelName) {
	this->_chats.find(channelName)->second.add_user(this->_users.find(userSocketFD)->second);
	return (0);
}

User Database::get_user(int userSocketFD) {
	return (this->_users.find(userSocketFD)->second);
}

int Database::set_channel_name(std::string oldChannelName, std::string newChannelName) {
	this->_chats.find(oldChannelName)->second.set_name(newChannelName);
	return (0);
}

std::unordered_map<int, User> Database::get_channel_user(std::string channelName) {
	return (this->_chats.find(channelName)->second.get_users());
}

int Database::set_user_name(int userSocketFD, std::string userName) {
	this->_users.find(userSocketFD)->second.set_user_name(userName);
	return (0);
}

Database::~Database() {
	// delete all chats
	this->_chats.clear();
	// delete all users
	this->_users.clear();
}
