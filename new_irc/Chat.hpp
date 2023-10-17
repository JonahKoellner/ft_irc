/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chat.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonahkollner <jonahkollner@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:50:02 by jonahkollne       #+#    #+#             */
/*   Updated: 2023/10/14 15:51:59 by jonahkollne      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include <poll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "User.hpp"

class Chat {
	private:
		std::vector<User>	_users;
		std::string			_name;
		void		set_name(std::string name);
		int			add_user(User user);
		int			remove_user(std::string userName);

	public:
		Chat();
		Chat(std::string name);
		~Chat();
		std::string	get_name();
		std::vector<User>	get_users();

		friend class Executer;
};
