/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonahkollner <jonahkollner@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:41:13 by jonahkollne       #+#    #+#             */
/*   Updated: 2023/10/08 20:03:10 by jonahkollne      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User(int socketFD) {
	this->_socketFD = socketFD;
	this->_userName = std::string("User") + std::to_string(socketFD);
	std::cout << "Constructed " << this->_userName << "(" << this->_socketFD << ")" << std::endl;
}
