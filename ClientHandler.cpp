/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientHandler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:07:19 by jkollner          #+#    #+#             */
/*   Updated: 2023/11/14 16:28:43 by jkollner         ###   ########.fr       */
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
	sockaddr_storage	clientAddress;
	socklen_t			clientAddressSize = sizeof(clientAddress);
	if ((newSocket = accept(this->_serverSocketFD, (sockaddr*)&clientAddress, &clientAddressSize)) == -1) {
		perror("Error accepting connection");
	} else {
		std::string ip = inet_ntoa(((sockaddr_in*)&clientAddress)->sin_addr);
        int port = ntohs(((sockaddr_in*)&clientAddress)->sin_port);


		std::cout << "New connection established. (" << ip << ":" << std::to_string(port) << ")" << std::endl;
		//std::string response(":server-name CAP your-nick ACK :NICK JOIN PRIVMSG ME PASS\r\n");

		std::string server_info_response = "";
		std::string client_nick_name = "User" + std::to_string(newSocket);
		server_info_response += ":irc.majo.42 001 " + client_nick_name + " :Welcome to the Internet Relay Network of majo@42\r\n";
		server_info_response += ":irc.majo.42 002 " + client_nick_name + " :Your host is irc.majo.42, running version 1.0\r\n";
		server_info_response += ":irc.majo.42 004 " + client_nick_name + " irc.majo.42 1.0 a\r\n";
		server_info_response += ":irc.majo.42 005 " + client_nick_name + " MODES=a, CHANTYPES=#, CHANLIMIT=#:50, PREFIX=(ov)@+\r\n";

		//std::string response(":irc.majo.42 001 User" + std::to_string(newSocket) + " :Welcome to the Internet Relay Network User" + std::to_string(newSocket) + "\r\n");
		if (send(newSocket, server_info_response.c_str(), server_info_response.size(), 0) < 0)
			return (std::cout << "Error sending CAP LS response" << std::endl, 1);



		Executer(this->_database).create_user(newSocket, ip + ":" + std::to_string(port));
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
		if (std::string(buffer, bytesRead).find("\r\n") != std::string::npos || std::string(buffer, bytesRead).find("\n") != std::string::npos) // irssi client
		{
			std::cout << "Received: " << this->_clientData.find(clientSocketFD)->second << std::endl;
			Commander(this->_clientData.find(clientSocketFD)->second, clientSocketFD, this->_database).execute();
			this->_clientData.find(clientSocketFD)->second = std::string("");
		}
	}
	return (0);
}
