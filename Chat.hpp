/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chat.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:50:02 by jonahkollne       #+#    #+#             */
/*   Updated: 2023/10/10 09:59:16 by jkollner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include "User.hpp"

class Chat {
	private:
		std::vector<User>	_users;
		int					chat_id;
	public:
		Chat() {};
		~Chat() {};
		int		send_message_to_chat(std::string message, User user) { return (0); };
		void	add_user(User user) {};
};
