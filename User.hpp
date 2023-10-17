/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:56:20 by jonahkollne       #+#    #+#             */
/*   Updated: 2023/10/17 17:38:18 by jkollner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>

class User{
	private:
		int	_socketFD;
		std::string _userName;
		bool	_verified;
		std::string	_currentChannel;
		void	set_channel(std::string channelName);
		int		set_user_name(std::string userName);
		void	set_verified(bool verified);

	public:
		User(int socketFD);
		std::string get_user_name();
		bool	get_verification();
		int		get_socket_fd();
		std::string get_channel();
		bool operator==(User user);
		~User() {};

		friend class Database;
};
