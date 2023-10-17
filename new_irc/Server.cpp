/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonahkollner <jonahkollner@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:01:30 by jonahkollne       #+#    #+#             */
/*   Updated: 2023/10/16 19:34:07 by jonahkollne      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server( std::string servername, int port, std::string password ) {
	_servername = servername;
	_port = port;
	_password = password;
}

Server::Server( std::string password ) {
	_servername = "default";
	_port = 4242;
	_password = password;
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

int	Server::handle_new_connection(std::vector<pollfd> &pollfds) {
	int	newSocket;
	if ((newSocket = accept(this->_serverSocketFD, nullptr, nullptr)) == -1) {
		perror("Error accepting connection");
	} else {
		std::cout << "New connection established." << std::endl;
		std::string response("Welcome Traveler\r\n");
		if (send(newSocket, response.c_str(), response.size(), 0) < 0)
			return (std::cout << "Error sending CAP LS response" << std::endl, 1);
		this->_users.insert(std::make_pair(newSocket, std::pair<std::string, User>("", User(newSocket))));
		pollfds.push_back((pollfd){newSocket, POLLIN});
	}
	return (0);
}

int	Server::handle_client_data(std::vector<pollfd> &pollfds, int clientSocketFD, int i) {
	char buffer[RECEIVE_BUFFER_SIZE + 1];
	memset(buffer, 0, sizeof(buffer));
	int bytesRead = recv(clientSocketFD, buffer, sizeof(buffer), 0);
	if (bytesRead <= 0) {
		// Connection closed or error
		std::string channelName = this->_users.find(pollfds[i].fd)->second.second.get_channel();
		std::string userName = this->_users.find(pollfds[i].fd)->second.second.get_user_name();
		if (channelName != "") {
			//this->_chats.find(channelName)->second.remove_user(userName);
			if (this->_chats.find(channelName)->second.get_users().size() == 0)
				this->_chats.erase(channelName);
		}
		//Commander().send_server_message(std::string("gsr"), this->_chats);
		//Commander().send_server_message(std::string(this->_users.find(pollfds[i].fd)->second.second.get_user_name() + "disconnected"), this->_chats.find(this->_users.find(pollfds[i].fd)->second.second.get_channel())->second);
		//std::cout << this->_users.find(pollfds[i].fd)->second.second.get_user_name() << " disconnected." << std::endl;
		close(clientSocketFD);
		this->_users.erase(pollfds[i].fd);
		pollfds.erase(pollfds.begin() + i);
	} else {
		// Process data from connected client
		this->_users.find(pollfds[i].fd)->second.first += std::string(buffer, bytesRead);
		//if (std::string(buffer, bytesRead).find("\r\n") != std::string::npos) // irssi client
		if (std::string(buffer, bytesRead).find("\n") != std::string::npos) // netcat
		{
			std::pair<std::string, User>& user_pair = this->_users.find(pollfds[i].fd)->second;
			Commander(user_pair.first, user_pair.second, this->_chats).execute();
			std::cout << "[Server]" << this->_users.find(pollfds[i].fd)->second.second.get_user_name() << ": " << this->_users.find(pollfds[i].fd)->second.first << std::endl;
			this->_users.find(pollfds[i].fd)->second.first = "";
		}
	}
	return (0);
}

int	Server::server_loop() {
	std::vector<pollfd> fds;
	fds.push_back((pollfd){this->_serverSocketFD, POLLIN}); // Add server socket to the poll set

	while (true) {
		int numReady = poll(fds.data(), fds.size(), -1);

		if (numReady == -1) {
			perror("Error in poll");
			return (1);
		}
		for (size_t i = 0; i < fds.size(); ++i) {
			if (fds[i].revents & POLLIN) {
				if (fds[i].fd == this->_serverSocketFD) {
					// New connection
					handle_new_connection(fds);
				} else {
					// Handle data from a client
					handle_client_data(fds, fds[i].fd, i);
				}
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
