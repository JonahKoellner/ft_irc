/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executer.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:13:03 by jonahkollne       #+#    #+#             */
/*   Updated: 2023/10/17 16:14:51 by jkollner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "User.hpp"
#include "Chat.hpp"
#include <unordered_set>
#include "Database.hpp"

class Executer{
	private:
		Database &_database;
		std::unordered_set<std::string> _blackListedNames;
		std::unordered_set<std::string> _blackListedChannelNames;
		int	join_channel(int userSocket_FD, std::string channel_name);
		int	send_user_message(int userSocket_FD, std::string message);
		int	send_message_chat(std::string channelName, std::string message);
		int send_message_user_chat(int userSocket_FD, std::string message);
		int	set_userName(int userSocket_FD, std::string userName);
		int	set_user_verified(int userSocketFD, bool verified);
		int set_channelName(int userSocketFD, std::string oldChannelName, std::string newChannelName);
		int	delete_user(int userSocket);
		int	create_user(int userSocket);
		int	create_channel(std::string channel_name);
		int	delete_channel(std::string channelName);
		User	get_user(int userSocket_FD);
		bool	check_password(std::string);
		int	remove_user_channel(int userSocket);
	public:
		Executer(Database &database);

	friend class Commander;
	friend class ClientHandler;
};
