/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chat.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreidenb <mreidenb@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:50:02 by jonahkollne       #+#    #+#             */
/*   Updated: 2023/11/14 20:55:27 by mreidenb         ###   ########.fr       */
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
		std::string			_name;
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
		//std::vector<User>	get_users();

		friend class Database;
};
