/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chat.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:50:02 by jonahkollne       #+#    #+#             */
/*   Updated: 2023/10/17 14:21:49 by jkollner         ###   ########.fr       */
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

class Chat {
	private:
		//std::vector<User>	_users;
		std::unordered_map<int, User> _users;
		std::string			_name;
		void				set_name(std::string name);
		int					add_user(User user);
		int					remove_user(int	userSocket);
		std::unordered_map<int, User>	get_users();

	public:
		Chat();
		Chat(std::string name);
		~Chat();
		int size();
		//std::string	get_name();
		//std::vector<User>	get_users();

		//friend class Executer;
		friend class Database;
};
