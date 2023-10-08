/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonahkollner <jonahkollner@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:56:20 by jonahkollne       #+#    #+#             */
/*   Updated: 2023/10/08 20:05:33 by jonahkollne      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>

class User{
	private:
		int	_socketFD;
		std::string _userName;

	public:
		User(int socketFD);
		std::string get_user_name() { return (this->_userName); };
		int set_user_name(std::string userName) { this->_userName = userName; return (0);};
		~User() {};
};
