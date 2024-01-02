/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:01:30 by jonahkollne       #+#    #+#             */
/*   Updated: 2024/01/02 17:42:47 by jkollner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server( std::string servername, int port, std::string password ) : _database(Database(password)){
	_servername = servername;
	_port = port;
	//_database = Database(password);
}

Server::Server( std::string password ) : _database(Database(password)){
	_servername = "default";
	_port = 4242;
	//_database = Database(password);
}

Server::~Server() { };

int	Server::bind_socket() {
	if ((this->_serverSocketFD = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		std::cout << "Error opening socket" << std::endl;
		return (1);
	}

	int flags = fcntl(this->_serverSocketFD, F_GETFL, 0);
	fcntl(this->_serverSocketFD, F_SETFL, flags | O_NONBLOCK); // set socket to non-blocking

	sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(this->_port);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(this->_serverSocketFD, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		std::cout << "Error binding socket" << std::endl;
		return (1);
	}
	return (0);
}

int	Server::start_listening() {
	if (listen(this->_serverSocketFD, SOMAXCONN) < 0)
	{
		std::cout << "Error listening" << std::endl;
		close(this->_serverSocketFD);
		return (1);
	}
	return (0);
}

int	Server::server_loop() {
	std::vector<pollfd> fds;
	fds.push_back((pollfd){this->_serverSocketFD, POLLIN, 0}); // Add server socket to the poll set
	ClientHandler CH(this->_serverSocketFD, this->_database);

	while (true) {
		int numReady = poll(fds.data(), fds.size(), -1);

		if (numReady == -1) {
			perror("Error in poll");
			return (1);
		}
		for (size_t i = 0; i < fds.size(); ++i) {
			if (fds[i].revents & POLLIN) {
				if (CH.handle(fds, fds[i].fd, i))
					break;
				//if (fds[i].fd == this->_serverSocketFD) {
				//	// New connection
				//	handle_new_connection(fds);
				//} else {
				//	// Handle data from a client
				//	handle_client_data(fds, fds[i].fd, i);
				//}
			}
		}
	}

	// Close all client sockets
	for (size_t i = 1; i < fds.size(); ++i) {
		close(fds[i].fd);
	}
	return (0);
}

int	Server::start_server() {
	int server_out;
	if (this->bind_socket() || this->start_listening())
		return (1);
	std::cout << "Starting server..." << std::endl;
	server_out = this->server_loop();
	close(this->_serverSocketFD);
	return (server_out);
}
