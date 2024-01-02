/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:56:20 by jonahkollne       #+#    #+#             */
/*   Updated: 2024/01/02 13:19:46 by jkollner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <vector>

class User{
	private:
		int	_socketFD;
		std::string _userName;
		std::string _nickName;
		std::string _realName;
		std::string _ip;
		bool	_verified;
		std::string	_currentChannel;
		std::vector<std::string> _joinedChannel;
		void	set_channel(std::string channelName);
		int		join_channel(std::string channelName);
		int		set_user_nickName(std::string nickName);
		int		set_user(std::string userName, std::string nickName, std::string realName);
		void	set_verified(bool verified);

	public:
		User(int socketFD);
		User(int socketFD, std::string ip);
		std::string get_user_name();
		std::string	get_user_nickName();
		bool	get_verification();
		int		get_socket_fd();
		std::string get_channel();
		std::vector<std::string> get_joined_channel();
		bool operator==(User user);
		~User() {};

		friend class Database;
};
