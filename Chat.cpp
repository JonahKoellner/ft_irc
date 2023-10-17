/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chat.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:22:10 by jonahkollne       #+#    #+#             */
/*   Updated: 2023/10/17 15:13:19 by jkollner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Chat.hpp"

Chat::Chat(std::string name) {
	std::cout << "Chat constructor" << std::endl;
	this->_name = name;
}

//std::string Chat::get_name() {
//	return(this->_name);
//}

void Chat::set_name(std::string name) {
	this->_name = name;
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
	this->_users.insert(std::make_pair(userSocket, user));
	return 0;
}

std::unordered_map<int, User> Chat::get_users() {
	return (this->_users);
}

int	Chat::remove_user(int userSocket) {
	return (this->_users.erase(userSocket) > 0 ? 1 : 0);
}

Chat::~Chat() {}
