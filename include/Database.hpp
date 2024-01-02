/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Database.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:46:18 by jkollner          #+#    #+#             */
/*   Updated: 2024/01/02 13:07:19 by jkollner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <unordered_map>
#include "Chat.hpp"
#include "User.hpp"

class Database {
	private:
		/* data && Functions*/
		std::string 							_password;
		std::unordered_map<std::string, Chat>	_chats;
		std::unordered_map<int, User>			_users;
		int	set_password(std::string new_password);
		int	create_channel(std::string channel_name);
		int	create_user(int userSocket, std::string ip);
		int	delete_user(int userSocket);
		int	delete_channel(std::string channelName);
		int	set_channel_name(std::string oldChannelName, std::string newChannelName);
		int set_channel_operator(int userSocketFD, std::string channelName);
		int	set_user_nickName(int userSocketFD, std::string nickName);
		int	set_user_User(int userSocketFD, std::string userName, std::string nickName, std::string realName);
		User	get_user(int userSocketFD);
		std::unordered_map<int, int> get_channel_user(std::string channelName);
		int	remove_user_channel(int userSocket, std::string userChannel);
		int	set_user_verification(bool verified, int userSocket);
		int	add_user_channel(int userSocket, std::string channelName);
		int get_user_fd(std::string userName);
		Chat get_channel(std::string channelName);
		std::unordered_map<std::string, Chat> get_all_channel( void );

	public:
		Database(std::string password);
		~Database();

	/*Limited Access*/
	friend class Executer;
};
