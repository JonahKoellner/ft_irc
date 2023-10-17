/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commander.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonahkollner <jonahkollner@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:58:20 by jonahkollne       #+#    #+#             */
/*   Updated: 2023/10/13 22:18:25 by jonahkollne      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "User.hpp"
#include "Chat.hpp"
#include "Executer.hpp"

class Commander{
	private:
		std::string	_commandString;
		User 		&_user;
		std::unordered_map<std::string, Chat>		&_userChats;
		std::vector<std::string>	tokenize_command(std::string commandString);
		int	execute_command(std::vector<std::string> commandTokens);
		std::vector<std::string> parse_command(std::string commandString);

	public:
		Commander();
		Commander(std::string commandString, User &user, std::unordered_map<std::string, Chat> &user_chat);
		int execute();
		int send_server_message(std::string, Chat chat);
};
