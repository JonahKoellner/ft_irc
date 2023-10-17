/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientHandler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:07:19 by jkollner          #+#    #+#             */
/*   Updated: 2023/10/17 16:00:42 by jkollner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientHandler.hpp"

ClientHandler::ClientHandler(int serverSocket, Database &database) : _database(database) {
	this->_serverSocketFD = serverSocket;
}

int ClientHandler::handle(std::vector<pollfd> &pollfds, int clientSocketFD, int i) {
	if (clientSocketFD == this->_serverSocketFD)
		return (this->handle_new_connection(pollfds));
	else
		return (this->handle_existing_client(pollfds, clientSocketFD, i));
}

int	ClientHandler::handle_new_connection(std::vector<pollfd> &pollfds) {
	int	newSocket;
	if ((newSocket = accept(this->_serverSocketFD, nullptr, nullptr)) == -1) {
		perror("Error accepting connection");
	} else {
		std::cout << "New connection established." << std::endl;
		std::string response("Welcome Traveler: User" + std::to_string(newSocket) + "\r\n");
		if (send(newSocket, response.c_str(), response.size(), 0) < 0)
			return (std::cout << "Error sending CAP LS response" << std::endl, 1);
		Executer(this->_database).create_user(newSocket);
		pollfds.push_back((pollfd){newSocket, POLLIN});
	}
	return (0);
}

int	ClientHandler::handle_existing_client(std::vector<pollfd> &pollfds, int clientSocketFD, int i) {
	char buffer[RECEIVE_BUFFER_SIZE + 1];
	memset(buffer, 0, sizeof(buffer));
	int bytesRead = recv(clientSocketFD, buffer, sizeof(buffer), 0);
	if (bytesRead <= 0) {
		// Connection closed or error
		Executer(this->_database).delete_user(clientSocketFD);
		pollfds.erase(pollfds.begin() + i);
		close(clientSocketFD);
	} else {
		// Process data from connected client
		std::unordered_map<int, std::string>::iterator it = this->_clientData.find(clientSocketFD);
		if (it == this->_clientData.end()) {
			// Key does not exist in map, insert new key-value pair
			this->_clientData.insert(std::make_pair(clientSocketFD, std::string(buffer, bytesRead)));
		} else {
			// Key exists in map, append to existing value
			it->second += std::string(buffer, bytesRead);
		}
		//if (std::string(buffer, bytesRead).find("\r\n") != std::string::npos) // irssi client
		if (std::string(buffer, bytesRead).find("\n") != std::string::npos) // netcat
		{
			Commander(this->_clientData.find(clientSocketFD)->second, clientSocketFD, this->_database).execute();
			this->_clientData.find(clientSocketFD)->second = std::string("");
		}
	}
	return (0);
}
