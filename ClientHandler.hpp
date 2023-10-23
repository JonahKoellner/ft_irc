/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:59:03 by jkollner          #+#    #+#             */
/*   Updated: 2023/10/23 13:10:07 by jkollner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <poll.h>
#include <vector>
#include <unistd.h>
#include <arpa/inet.h>
#include "Executer.hpp"
#include "Commander.hpp"

#define RECEIVE_BUFFER_SIZE 5

class ClientHandler {
	private:
		int _serverSocketFD;
		Database &_database;
		std::unordered_map<int, std::string> _clientData;
		int handle_new_connection(std::vector<pollfd> &pollfds);
		int handle_existing_client(std::vector<pollfd> &pollfds, int clientSocketFD, int i);

	public:
		//enum CLIENT_ACTION {
			//NEW_CONNECTION,
			//EXISTING_CLIENT,
			//CLIENT_DISCONNECTED,
			//CLIENT_ACTION_LENGTH}
		ClientHandler(int serverSocket, Database &database);
		int handle(std::vector<pollfd> &pollfds, int clientSocketFD, int i);
};
