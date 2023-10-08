/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonahkollner <jonahkollner@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:46:17 by jonahkollne       #+#    #+#             */
/*   Updated: 2023/10/08 19:53:25 by jonahkollne      ###   ########.fr       */
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
#include "Chat.hpp"
#include "User.hpp"

#define RECEIVE_BUFFER_SIZE 5

class Server {
	private:
		std::string			_servername;
		int					_port;
		std::string			_password;
		std::vector<Chat>	_chats;
		int					_serverSocketFD;
		//std::vector<User>	_users;
		std::unordered_map<int, std::pair<std::string, User> > _usermap;
		int	bind_socket();
		int	start_listening();
		int	server_loop();
		int init_readSet(std::vector<int> clientSockets, fd_set &readSet);
		int handle_new_connection(std::vector<int> &clientSockets, fd_set &readSet);
		int handle_clients(std::vector<int> &clientSockets, fd_set &readSet);

	public:
		//Server() {};
		Server(std::string servername, int port, std::string password);
		Server(std::string password);
		~Server();
		int	start_server();
};
