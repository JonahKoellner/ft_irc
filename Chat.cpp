/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chat.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:38:28 by jkollner          #+#    #+#             */
/*   Updated: 2023/10/10 15:26:20 by jkollner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Chat.hpp"

int	send_user_message(User user_entry, std::string message) {
	struct pollfd pfd = {user_entry.get_socket_fd(), POLLOUT, 0 };
	int poll_result = poll(&pfd, 1, -1);
	if (poll_result < 0) {
		std::cerr << "Error in poll(): " << strerror(errno) << std::endl;
		return (1);
	}
	else if (poll_result == 0) {
		std::cerr << "Timeout in poll()" << std::endl;
		return (1);
	}
	else if (pfd.revents & POLLOUT) {
		ssize_t bytes_sent = send(user_entry.get_socket_fd(), message.c_str(), message.length(), 0);
		if (bytes_sent < 0) {
			std::cerr << "Error sending message: " << strerror(errno) << std::endl;
			return (1);
		}
		else if (bytes_sent != message.length()) {
			std::cerr << "Incomplete message sent" << std::endl;
			return (1);
		}
		else {
			return (0);
		}
	}
	else {
		std::cerr << "Unknown error in poll()" << std::endl;
		return (1);
	}
}

int Chat::send_message_to_chat(std::string message, User user) {
	std::cout << this->_users.size() << std::endl;
	for (std::vector<User>::iterator it = this->_users.begin(); it != this->_users.end(); it++) {
		std::cout << "Sending message to " << it->get_user_name() << std::endl;
		if (it->get_socket_fd() != user.get_socket_fd()) {
			if (send_user_message(*it, message) != 0) {
				std::cerr << "Error sending message to user " << it->get_user_name() << std::endl;
				return (1);
			}
		}
	}
	return (0);
}

void Chat::add_user(User user) {
	this->_users.push_back(user);
}
