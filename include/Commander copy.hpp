/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commander copy.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreidenb <mreidenb@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:58:20 by jonahkollne       #+#    #+#             */
/*   Updated: 2023/11/28 18:40:46 by mreidenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "User.hpp"
#include "Chat.hpp"
#include "Executer.hpp"

class Commander{
	private:
		std::string					_commandString;
		//User 						&_user;
		int 						_userSocket_FD;
		Database					&_database;
		std::vector<std::string>	_commandTokens;
		//std::unordered_map<std::string, Chat>		&_userChats;
		std::vector<std::string>	tokenize_command(std::string commandString);
		int	execute_command(std::vector<std::string> commandTokens);
		std::vector<std::string> parse_command(std::string commandString);
	public:
		//Commander();
		Commander(std::string commandString, int userSocket_FD, Database &database);
		//Commander(std::string commandString, User &user, std::unordered_map<std::string, Chat> &user_chat);
		int execute();
		//int send_server_message(std::string, Chat chat);
};
