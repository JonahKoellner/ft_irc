/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commander.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreidenb <mreidenb@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:58:20 by jonahkollne       #+#    #+#             */
/*   Updated: 2024/01/01 22:06:17 by mreidenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "User.hpp"
#include "Chat.hpp"
#include "Executer.hpp"

class Commander{
	private:
		// std::string					_commandString;
		std::string					_commandName;
		std::vector<std::string>	_commandArguments;
		//User 						&_user;
		int 						_userSocket_FD;
		Database					&_database;
		// std::vector<std::string>	_commandTokens;
		//std::unordered_map<std::string, Chat>		&_userChats;
		std::vector<std::string>	tokenize_command(std::string commandString);
		int	execute_command(std::vector<std::string> commandTokens);
		std::vector<std::string> parse_command(std::string commandString);
		int	handle_pass();
		int	handle_user();
		int	handle_nick();
		int	handle_privmsg();
		int	handle_join();
		int	handle_leave();
		int	handle_who();
		int	handle_list();
		int	handle_users();
		int	handle_names();
		int	handle_quit();
		int	handle_away();
		int	handle_topic();
		int	handle_ping();
		int	handle_kick();
		int	handle_invite();
	public:
		//Commander();
		Commander(std::string commandString, int userSocket_FD, Database &database);
		//Commander(std::string commandString, User &user, std::unordered_map<std::string, Chat> &user_chat);
		int execute();
		//int send_server_message(std::string, Chat chat);
};
