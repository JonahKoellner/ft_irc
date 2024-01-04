/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chat.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:50:02 by jonahkollne       #+#    #+#             */
/*   Updated: 2024/01/04 16:28:37 by jkollner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include <poll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unordered_map>
#include "User.hpp"
#include "Bot.hpp"

enum ChatModes {
	none = 0, // No modes
	i = 1 << 0, // Set/remove invite-only channel
	t = 1 << 1, // Set/remove the restrictions of the TOPIC comadn to channel operators
	k = 1 << 2, // Set/remove the channel key (password)
	o = 1 << 3, // Give/take channel operator privileges
	l = 1 << 4, // Set/remove the user limit to channel
};

class Chat {
	private:
		std::unordered_map<int, int> _users; // <socketFD, channel_id>
		std::unordered_map<int, int> _operators; // <socketFD, channel_id>
		std::string			_name;
		std::string			_topic;
		uint8_t				_modes;

		void				set_topic(std::string topic);
		void				set_name(std::string name);
		int					add_user(User user);
		int					remove_user(int	userSocket);
		void				set_operator(int socketFD);
		void				remove_operator(int socketFD);
		void				set_mode(ChatModes mode);
		void 				unset_mode(ChatModes mode);
		bool				has_mode(ChatModes mode);
		std::bitset<8>		get_modes(); // Debug function

	public:
		Chat();
		Chat(std::string name);
		~Chat();
		int size();
		std::string	get_name();
		std::string	get_topic();
		std::unordered_map<int, int>	get_operators();
		std::unordered_map<int, int>	get_users();

	friend class Database;
};
