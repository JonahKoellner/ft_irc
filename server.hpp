/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:46:17 by jonahkollne       #+#    #+#             */
/*   Updated: 2023/10/23 12:14:02 by jkollner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <unordered_map>
#include "Chat.hpp"
#include "User.hpp"
#include "Commander.hpp"
#include "Database.hpp"
#include "ClientHandler.hpp"

#define RECEIVE_BUFFER_SIZE 5

class Server {
	private:
		std::string	_servername;
		int			_port;
		int			_serverSocketFD;
		Database	_database;
		int	bind_socket();
		int	start_listening();
		int	server_loop();
		int	handle_new_connection(std::vector<pollfd> &pollfds);
		int	handle_client_data(std::vector<pollfd> &pollfds, int clientSocketFD, int i);
		int	create_channel(std::string channel_name);

	public:
		//Server() {};
		Server(std::string servername, int port, std::string password);
		Server(std::string password);
		~Server();
		int	start_server();
};

