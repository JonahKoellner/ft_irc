/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:41:13 by jonahkollne       #+#    #+#             */
/*   Updated: 2023/10/10 14:46:33 by jkollner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User(int socketFD) {
	this->_socketFD = socketFD;
	this->_verified = false;
	this->_userName = std::string("User") + std::to_string(socketFD);
	this->_currentChannel = NULL;
	std::cout << "Constructed " << this->_userName << "(" << this->_socketFD << ")" << std::endl;
}
