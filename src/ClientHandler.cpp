/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientHandler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreidenb <mreidenb@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:07:19 by jkollner          #+#    #+#             */
/*   Updated: 2024/01/01 22:06:27 by mreidenb         ###   ########.fr       */
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
	int					newSocket;
	sockaddr_storage	clientAddress;
	socklen_t			clientAddressSize = sizeof(clientAddress);
	if ((newSocket = accept(this->_serverSocketFD, (sockaddr*)&clientAddress, &clientAddressSize)) == -1) {
		perror("Error accepting connection");
	} else {
		std::string ip = inet_ntoa(((sockaddr_in*)&clientAddress)->sin_addr);
        int port = ntohs(((sockaddr_in*)&clientAddress)->sin_port);


		std::cout << "New connection established. (" << ip << ":" << std::to_string(port) << ")" << std::endl;
		Executer(this->_database).create_user(newSocket, ip + ":" + std::to_string(port));
		pollfds.push_back((pollfd){newSocket, POLLIN, 0});
	}
	return (0);
}

int	ClientHandler::handle_existing_client(std::vector<pollfd> &pollfds, int clientSocketFD, int i) {
	char buffer[RECEIVE_BUFFER_SIZE + 1];
	memset(buffer, 0, sizeof(buffer));
	int bytesRead = recv(clientSocketFD, buffer, sizeof(buffer), 0);
	if (bytesRead <= 0) {
		// Connection closed or error
		Executer ex(this->_database);
		ex.send_message_chat(ex.get_user(clientSocketFD).get_channel(), ex.get_user(clientSocketFD).get_user_name() + " has left the chat.\r\n");
		ex.remove_user_channel(clientSocketFD);
		ex.delete_user(clientSocketFD);
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
		//if (std::string(buffer, bytesRead).find("\n") != std::string::npos) // netcat
		if (bytesRead > 0) {
			std::string data = this->_clientData.find(clientSocketFD)->second;
			size_t pos = 0;
			std::string token;
			while ((pos = data.find("\r\n")) != std::string::npos) {
				token = data.substr(0, pos);
				std::cout << "Received: " << token << std::endl;
				Commander(token, clientSocketFD, this->_database).execute();
				data.erase(0, pos + 2);
			}
			this->_clientData.find(clientSocketFD)->second = data;
		}
	}
	return (0);
}
