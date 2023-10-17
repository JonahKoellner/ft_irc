/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executer.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonahkollner <jonahkollner@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:51:25 by jonahkollne       #+#    #+#             */
/*   Updated: 2023/10/14 15:59:56 by jonahkollne      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Executer.hpp"

int	Executer::send_message_chat(User user, Chat chat, std::string message) {
	std::vector<User> users = chat.get_users();
	for (std::vector<User>::iterator it = users.begin(); it != users.end(); it++) {
		if (!(*it == user)) {
			if (send_user_message(*it, message))
				return (1);
		}
	}
	return (0);
}

int	Executer::send_user_message(User user, std::string message) {
	struct pollfd pfd = {user.get_socket_fd(), POLLOUT, 0 };
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
		ssize_t bytes_sent = send(user.get_socket_fd(), message.c_str(), message.length(), 0);
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

int	Executer::join_channel(User &user, std::unordered_map<std::string, Chat> &chat, std::string channel_name) {
	std::unordered_map<std::string, Chat>::iterator chatIT = chat.find(channel_name);
	if (chatIT == chat.end()) {
		if (_blackListedChannelNames.find(channel_name) != _blackListedChannelNames.end()) {
			send_user_message(user, std::string("Channel name is blacklisted\r\n"));
			return (1);
		}
		std::pair<std::string, Chat> newChatEntry(channel_name, Chat(channel_name));
		newChatEntry.second.add_user(user);
		chat.insert(newChatEntry);
	} else
		chatIT->second.add_user(user);
	user.set_channel(channel_name);
	return (0);
}

int	Executer::set_userName(User &user, std::string userName) {
	if (_blackListedNames.find(userName) != _blackListedNames.end()) {
		send_user_message(user, std::string("Username is blacklisted\r\n"));
		return (1);
	}
	// check if username is already taken
	user.set_user_name(userName);
	return (0);
}

int Executer::set_channelName(Chat &chat, std::string channelName) {
	if (_blackListedChannelNames.find(channelName) != _blackListedChannelNames.end()) {
		send_message_chat(User(-1), chat, std::string("Channel name is blacklisted\r\n"));
		return (1);
	}
	// check for dups
	chat.set_name(channelName);
	return (0);
}
