/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonahkollner <jonahkollner@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:01:30 by jonahkollne       #+#    #+#             */
/*   Updated: 2023/10/08 20:05:08 by jonahkollne      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

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

int	Server::init_readSet(std::vector<int> clientSockets, fd_set &readSet) {
	FD_ZERO(&readSet);
	FD_SET(this->_serverSocketFD, &readSet);
	for(int i = 0; i < clientSockets.size(); i++) {
		FD_SET(clientSockets[i], &readSet);
	}
	int maxFd = this->_serverSocketFD;
	if (!clientSockets.empty())
	{
		int maxClientSocket = *std::max_element(clientSockets.begin(), clientSockets.end());
		if (maxClientSocket > maxFd)
			maxFd = maxClientSocket;
	}

	if (select(maxFd + 1, &readSet, nullptr, nullptr, nullptr) == -1) {
		perror("Select error");
		return (1);
	}
	return (0);
}

int	Server::handle_new_connection(std::vector<int> &clientSockets, fd_set &readSet) {
	if (FD_ISSET(this->_serverSocketFD, &readSet)) {
		int clientSocket = accept(this->_serverSocketFD, nullptr, nullptr);
		if (clientSocket != -1) {
			clientSockets.push_back(clientSocket);
			this->_usermap.insert(std::make_pair(clientSocket, std::pair<std::string, User>("", User(clientSocket))));
			//this->_users.push_back(User(clientSocket));
			//commands.insert(std::map<int, std::string>::value_type(clientSocket, std::string("")));
			std::cout << "Accepted connection" << std::endl;
		}
	}
	return (0);
}

int	Server::handle_clients(std::vector<int> &clientSockets, fd_set &readSet) {
	char buffer[RECEIVE_BUFFER_SIZE + 1];
	memset(buffer, 0, sizeof(buffer));

	for (int i = 0; i < clientSockets.size(); i++) {
	//for (int clientSocket : clientSockets) {
		if (FD_ISSET(clientSockets[i], &readSet)) {
			memset(buffer, 0, sizeof(buffer));
			int bytesRead = recv(clientSockets[i], buffer, sizeof(buffer), 0);
			if (bytesRead <= 0) {
				std::cout << "Connection closed" << std::endl;
				close(clientSockets[i]);
				clientSockets.erase(std::remove(clientSockets.begin(), clientSockets.end(), clientSockets[i]), clientSockets.end());
			} else {
				this->_usermap.find(clientSockets[i])->second.first += std::string(buffer, bytesRead);
				if (std::string(buffer, bytesRead).find('\n') != std::string::npos)
				{
					std::cout << "[Server]" << this->_usermap.find(clientSockets[i])->second.second.get_user_name() << ": " << this->_usermap.find(clientSockets[i])->second.first << std::endl;
					//if (send(clientSockets[i], commands.find(clientSockets[i])->second.c_str(), commands.find(clientSockets[i])->second.length(), 0) < 0)
						//std::cout << "Error sending response" << std::endl;
					this->_usermap.find(clientSockets[i])->second.first = "";
				}
			}
		}
	}
	return (0);
}

int	Server::server_loop() {
	std::vector<int> clientSockets;
	fd_set readSet;
	while (true)
	{
		init_readSet(clientSockets, readSet);
		handle_new_connection(clientSockets, readSet);
		handle_clients(clientSockets, readSet);
	}
	for (size_t i = 0; i < clientSockets.size(); i++)
		close(clientSockets[i]); // close all client sockets
	close(this->_serverSocketFD); // close server socket
}

int	Server::start_server() {
	if (this->bind_socket() || this->start_listening())
		return (1);
	return (server_loop());
	//return (0);
}
