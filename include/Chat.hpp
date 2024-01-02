/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chat.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:50:02 by jonahkollne       #+#    #+#             */
/*   Updated: 2024/01/02 17:58:59 by jkollner         ###   ########.fr       */
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

class Chat {
	private:
		std::unordered_map<int, int> _users; // <socketFD, channel_id>
		std::unordered_map<int, int> _operators; // <socketFD, channel_id>
		std::string			_name;
		std::string			_topic;
		//std::unordered_map<std::string, Bot> _bots;
		void				set_name(std::string name);
		int					add_user(User user);
		int					remove_user(int	userSocket);
		std::unordered_map<int, int>	get_users();

	public:
		Chat();
		Chat(std::string name);
		~Chat();
		int size();
		std::string	get_name();
		std::string	get_topic();
		void		set_topic(std::string topic);
		void		set_operator(int socketFD);
		std::unordered_map<int, int>	get_operators();
		void		remove_operator(int socketFD);
		//std::vector<User>	get_users();

		friend class Database;
};
