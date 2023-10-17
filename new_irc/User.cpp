/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonahkollner <jonahkollner@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:34:01 by jonahkollne       #+#    #+#             */
/*   Updated: 2023/10/14 15:51:00 by jonahkollne      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User(int socketFD) {
	this->_socketFD = socketFD;
	this->_verified = false;
	this->_userName = std::string("User") + std::to_string(socketFD);
	this->_currentChannel = "";
}

std::string	User::get_user_name() {
	return (this->_userName + (this->_verified ? "" : "*"));
}

int	User::set_user_name(std::string userName) {
	this->_userName = userName;
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

