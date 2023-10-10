/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:56:20 by jonahkollne       #+#    #+#             */
/*   Updated: 2023/10/10 15:19:37 by jkollner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
//#include "Chat.hpp"

class Chat;

class User{
	private:
		int	_socketFD;
		std::string _userName;
		bool	_verified;
		Chat	*_currentChannel;

	public:
		User(int socketFD);
		std::string get_user_name() { return (this->_userName + (this->_verified ? "" : "*")); };
		int set_user_name(std::string userName) { this->_userName = userName; return (0);};
		void	set_verified(bool verified) { this->_verified = verified; };
		bool	get_veification() { return (this->_verified); };
		int		get_socket_fd() {return (this->_socketFD);};
		void	set_channel(Chat *channel) { this->_currentChannel = channel; };
		Chat	*get_channel() { return (this->_currentChannel); };
		~User() {};
};
