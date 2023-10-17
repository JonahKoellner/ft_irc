/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonahkollner <jonahkollner@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:56:20 by jonahkollne       #+#    #+#             */
/*   Updated: 2023/10/14 15:50:50 by jonahkollne      ###   ########.fr       */
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

		friend class Executer;
};
