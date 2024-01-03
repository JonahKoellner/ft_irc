/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chat.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:22:10 by jonahkollne       #+#    #+#             */
/*   Updated: 2024/01/03 10:44:32 by jkollner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Chat.hpp"

Chat::Chat(std::string name) {
	std::cout << "Chat constructor" << std::endl;
	this->_name = name;
}

std::string Chat::get_name() {
	return(this->_name);
}

void Chat::set_name(std::string name) {
	this->_name = name;
}

void Chat::set_topic(std::string topic) {
	this->_topic = topic;
}

void Chat::set_operator(int socketFD) {
	this->_operators.insert(std::make_pair(socketFD, this->_operators.size()));
}

std::unordered_map<int, int> Chat::get_operators() {
	return (this->_operators);
}

void Chat::remove_operator(int socketFD) {
	this->_operators.erase(socketFD);
}

//std::vector<User> Chat::get_users() {
//	return (this->_users);
//}

int Chat::add_user(User user) {
	int userSocket = user.get_socket_fd();
	if (this->_users.find(userSocket) != this->_users.end()) {
		// User already exists in the chat
		return -1;
	}
	this->_users.insert(std::make_pair(userSocket, this->_users.size()));
	return 0;
}

std::unordered_map<int, int> Chat::get_users() {
	return (this->_users);
}

int	Chat::remove_user(int userSocket) {
	return (this->_users.erase(userSocket) > 0 ? 1 : 0);
}

int Chat::size() {
	return (this->_users.size());
}

std::string Chat::get_topic() {
	return (this->_topic);
}

Chat::~Chat() {}
