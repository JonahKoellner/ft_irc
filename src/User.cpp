/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreidenb <mreidenb@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:34:01 by jonahkollne       #+#    #+#             */
/*   Updated: 2024/01/01 20:38:11 by mreidenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User(int socketFD) {
	this->_socketFD = socketFD;
	this->_verified = false;
	this->_userName = std::string("User") + std::to_string(socketFD);
	this->_nickName = this->_userName;
	this->_currentChannel = "";
	this->_ip = "";
}

User::User(int socketFD, std::string ip) {
	this->_socketFD = socketFD;
	this->_verified = false;
	this->_userName = std::string("User") + std::to_string(socketFD);
	this->_nickName = this->_userName;
	this->_currentChannel = "";
	this->_ip = ip;
}

std::string	User::get_user_name() {
	return (this->_userName + (this->_verified ? "" : "*"));
}

std::string User::get_user_nickName() {
	return (this->_userName);
}

int	User::set_user_nickName(std::string nickName) {
	this->_userName = nickName;
	return (0);
}

int User::set_user(std::string userName, std::string nickName, std::string realName) {
	this->_userName = userName;
	this->_nickName = nickName;
	this->_realName = realName;
	return (0);
}


void User::set_verified(bool verified) {
	this->_verified = verified;
}

bool User::get_verification() {
	return (this->_verified);
}

int User::get_socket_fd() {
	return (this->_socketFD);
}

void User::set_channel(std::string channelName) {
	this->_currentChannel = channelName;
}

std::string User::get_channel() {
	return (this->_currentChannel);
}

bool User::operator==(User user) {
	return (this->_userName == user._userName || this->_socketFD == user._socketFD);
}

