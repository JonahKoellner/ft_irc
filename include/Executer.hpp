/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executer.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreidenb <mreidenb@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:13:03 by jonahkollne       #+#    #+#             */
/*   Updated: 2024/01/01 21:52:46 by mreidenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <unordered_set>
#include "User.hpp"
#include "Chat.hpp"
#include "Database.hpp"


class Executer{
	static const std::string SERVER_NAME;
	private:
		Database &_database;
		std::unordered_set<std::string> _blackListedNames;
		std::unordered_set<std::string> _blackListedChannelNames;
		int	join_channel(int userSocket_FD, std::string channel_name);
		int	send_user_message(int userSocket_FD, std::string message);
		int	send_message_chat(std::string channelName, std::string message);
		int send_message_user_chat(int userSocket_FD, std::string message);
		int	set_user_nickName(int userSocket_FD, std::string userName);
		int	send_message_user_chat(int userSocketFD, std::string message, std::string channelName);
		int	send_message_to_user(std::string userName, std::string message);
		int send_server_message(int userSocketFD, std::string message, std::string code);
		int	set_userName(int userSocket_FD, std::string userName);
		int set_user_User(int userSocket_FD, std::string userName, std::string nickName, std::string realName);
		int	set_user_verified(int userSocketFD, bool verified);
		int set_channelName(int userSocketFD, std::string oldChannelName, std::string newChannelName);
		int	delete_user(int userSocket);
		int	create_user(int userSocket, std::string ip);
		int	create_channel(std::string channel_name);
		int	delete_channel(std::string channelName);
		User	get_user(int userSocket_FD);
		bool	check_password(std::string);
		int	remove_user_channel(int userSocket);
		int send_private_message(int userSocketFD, std::string targetUserName, std::string message);
		int list_user_channel(int userSocketFD);
		int	list_channel( int userSocketFD, std::string nickName );
		int	handle_ping(int userSocketFD, const std::string &message);
		int	kick_user(int userSocketFD, std::string targetUserName, std::string channelName);
	public:
		Executer(Database &database);

	friend class Commander;
	friend class ClientHandler;
};
