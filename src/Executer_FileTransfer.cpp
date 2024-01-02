/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executer_FileTransfer.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreidenb <mreidenb@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 13:10:01 by mreidenb          #+#    #+#             */
/*   Updated: 2024/01/02 15:09:25 by mreidenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Executer.hpp"


// In Executer.cpp
int Executer::handle_dcc_send(int sourceSocket_FD, const std::string& DCC_message, std::string& targetName) {
	// Retrieve the source and target User objects
	User source = _database.get_user(sourceSocket_FD);
	User target = _database.get_user(_database.get_user_fd(targetName));
	return (this->send_message_to_user(targetName, DCC_message));
}