/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:01:30 by jonahkollne       #+#    #+#             */
/*   Updated: 2023/10/09 15:40:08 by jkollner         ###   ########.fr       */
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

// SELECT VARIATION
/*
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
			// send password request
			if (send(clientSocket, "Enter password: ", 16, 0) < 0)
				std::cout << "Error sending response" << std::endl;
			clientSockets.push_back(clientSocket);
			this->_usermap.insert(std::make_pair(clientSocket, std::pair<std::string, User>("", User(clientSocket))));
			std::cout << "Accepted connection" << std::endl;
		}
	}
	return (0);
}

int	Server::handle_clients(std::vector<int> &clientSockets, fd_set &readSet) {
	char buffer[RECEIVE_BUFFER_SIZE + 1];
	memset(buffer, 0, sizeof(buffer));

	for (int i = 0; i < clientSockets.size(); i++) {
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

*/

// Command
/*
	give user and command string to the command function
	command function give the strng to the parser
	parer returns the comman name
	command excutes the given command from the parser
*/

COMMANDS parse(std::string command_message) {
	COMMANDS command = ERROR;

	if (command_message[0] != '/')
		return (command);

	std::string command_part = command_message.substr(1, command_message.find(' '));
	std::transform(command_part.begin(), command_part.end(), command_part.begin(), ::toupper);

	if (command_part == "JOIN")
		command = JOIN;
	else if (command_part == "NICK")
		command = NICK;
	else if (command_part == "USER")
		command = USER;
	else if (command_part == "PASS")
		command = PASS;
	else if (command_part == "CAP")
		command = CAP;
	else if (command_part == "PING")
		command = PING;
	else if (command_part == "PONG")
		command = PONG;
	else if (command_part == "PRIVMSG")
		command = PRIVMSG;
	else if (command_part == "NOTICE")
		command = NOTICE;
	else if (command_part == "QUIT")
		command = QUIT;
	else if (command_part == "PART")
		command = PART;
	else if (command_part == "TOPIC")
		command = TOPIC;
	else if (command_part == "MODE")
		command = MODE;
	else if (command_part == "WHO")
		command = WHO;
	else if (command_part == "WHOIS")
		command = WHOIS;
	else if (command_part == "LIST")
		command = LIST;
	else if (command_part == "INVITE")
		command = INVITE;
	else if (command_part == "KICK")
		command = KICK;
	else if (command_part == "KILL")
		command = KILL;
	else if (command_part == "AWAY")
		command = AWAY;
	else if (command_part == "OPER")
		command = OPER;
	else if (command_part == "SQUIT")
		command = SQUIT;
	else if (command_part == "ERROR")
		command = ERROR;
	else
		command = UNKNOWN;
	return command;
}

int command_executing(std::pair<int, std::pair<std::string, User> > user_entry) {
	COMMANDS command = parse(user_entry.second.first);
	if (!user_entry.second.second.get_veification())
	{
		if (command == PASS)
		{
			// check password
			// if correct
			user_entry.second.second.set_verified(true);
			// else
			// send wrong password message
			return (1);
		}
		else
		{
			// send error / "give password" message
			return (1);
		}
	}
	switch (command) {
		case JOIN:
			// Handle JOIN command
			break;
		case NICK:
			// Handle NICK command
			break;
		case USER:
			// Handle USER command
			break;
		case PASS:
			// Handle PASS command
			break;
		case CAP:
			// Handle CAP command
			break;
		case PING:
			// Handle PING command
			break;
		case PONG:
			// Handle PONG command
			break;
		case PRIVMSG:
			// Handle PRIVMSG command
			break;
		case NOTICE:
			// Handle NOTICE command
			break;
		case QUIT:
			// Handle QUIT command
			break;
		case PART:
			// Handle PART command
			break;
		case TOPIC:
			// Handle TOPIC command
			break;
		case MODE:
			// Handle MODE command
			break;
		case WHO:
			// Handle WHO command
			break;
		case WHOIS:
			// Handle WHOIS command
			break;
		case LIST:
			// Handle LIST command
			break;
		case INVITE:
			// Handle INVITE command
			break;
		case KICK:
			// Handle KICK command
			break;
		case KILL:
			// Handle KILL command
			break;
		case AWAY:
			// Handle AWAY command
			break;
		case OPER:
			// Handle OPER command
			break;
		case SQUIT:
			// Handle SQUIT command
			break;
		case ERROR:
			// Handle ERROR command
			break;
		case UNKNOWN:
			// Handle UNKNOWN command
			break;
	}
	return (0);
}

int	Server::handle_new_connection(std::vector<pollfd> &pollfds) {
	int	newSocket;
	if ((newSocket = accept(this->_serverSocketFD, nullptr, nullptr)) == -1) {
		perror("Error accepting connection");
	} else {
		std::cout << "New connection established." << std::endl;
		std::string response("CAP LS\r\n");
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
		close(clientSocketFD);
		pollfds.erase(pollfds.begin() + i);
		std::cout << this->_users.find(pollfds[i].fd)->second.second.get_user_name() << " disconnected." << std::endl;
	} else {
		// Process data from connected client
		this->_users.find(pollfds[i].fd)->second.first += std::string(buffer, bytesRead);
		//if (std::string(buffer, bytesRead).find("\r\n") != std::string::npos) // irssi
		if (std::string(buffer, bytesRead).find("\n") != std::string::npos) // netcat
		{
			std::cout << "[Server]" << this->_users.find(pollfds[i].fd)->second.second.get_user_name() << ": " << this->_users.find(pollfds[i].fd)->second.first << std::endl;
			this->_users.find(pollfds[i].fd)->second.first = "";
		}
	}
	return (0);
}

// POLL VARIATION
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
	server_out = this->server_loop();
	close(this->_serverSocketFD);
	return (server_out);
}
