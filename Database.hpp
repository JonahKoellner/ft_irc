/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Database.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:46:18 by jkollner          #+#    #+#             */
/*   Updated: 2023/10/17 13:28:33 by jkollner         ###   ########.fr       */
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
		std::string 											_password;
		std::unordered_map<std::string, Chat>					_chats;
		std::unordered_map<int, User>	_users;
		int	set_password(std::string new_password);
		int	create_channel(std::string channel_name);
		int	create_user(int userSocket);
		int	delete_user(int userSocket);
		int	delete_channel(std::string channelName);
		int	set_channel_name(std::string oldChannelName, std::string newChannelName);
		int	set_user_name(int userSocketFD, std::string userName);
		User	get_user(int userSocketFD);
		std::unordered_map<int, User> get_channel_user(std::string channelName);
		int	remove_user_channel(int userSocket);
		int	set_user_verification(bool verified, int userSocket);
		int	add_user_channel(int userSocket, std::string channelName);

	public:
		Database(std::string password);
		~Database();

	/*Limited Access*/
	friend class Executer;
};
