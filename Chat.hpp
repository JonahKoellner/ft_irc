/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chat.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:50:02 by jonahkollne       #+#    #+#             */
/*   Updated: 2023/10/10 15:26:00 by jkollner         ###   ########.fr       */
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
		int					chat_id;
		std::string			_name;
	public:
		Chat() {};
		~Chat() {};
		int		send_message_to_chat(std::string message, User user);
		std::string	get_name() { return (_name); };
		void set_name(std::string name) { _name = name; };
		void	add_user(User user);
};
