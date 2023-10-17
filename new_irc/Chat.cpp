/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chat.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonahkollner <jonahkollner@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:22:10 by jonahkollne       #+#    #+#             */
/*   Updated: 2023/10/14 15:52:50 by jonahkollne      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Chat.hpp"

Chat::Chat(std::string name) {
	this->_name = name;
}

std::string Chat::get_name() {
	return(this->_name);
}

void Chat::set_name(std::string name) {
	this->_name = name;
}

std::vector<User> Chat::get_users() {
	return (this->_users);
}

int Chat::add_user(User user) {
	for (std::vector<User>::iterator it = this->_users.begin(); it != this->_users.end(); it++) {
		if (*it == user) {
			std::cerr << "User " << user.get_user_name() << " already in chat " << this->_name << std::endl;
			return (1);
		}
	}
	this->_users.push_back(user);
	return (0);
}

Chat::~Chat() {}
