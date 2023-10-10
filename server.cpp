/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:01:30 by jonahkollne       #+#    #+#             */
/*   Updated: 2023/10/10 10:15:36 by jkollner         ###   ########.fr       */
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
	command_part = command_part.substr(0, command_part.find('\n'));
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
	else
		command = UNKNOWN;
	return command;
}

int	send_user_message(std::pair<int, std::pair<std::string, User> > user_entry, std::string message) {
	struct pollfd pfd = {user_entry.first, POLLOUT, 0 };
	int poll_result = poll(&pfd, 1, -1);
	if (poll_result < 0) {
		std::cerr << "Error in poll(): " << strerror(errno) << std::endl;
		return (1);
	}
	else if (poll_result == 0) {
		std::cerr << "Timeout in poll()" << std::endl;
		return (1);
	}
	else if (pfd.revents & POLLOUT) {
		ssize_t bytes_sent = send(user_entry.first, message.c_str(), message.length(), 0);
		if (bytes_sent < 0) {
			std::cerr << "Error sending message: " << strerror(errno) << std::endl;
			return (1);
		}
		else if (bytes_sent != message.length()) {
			std::cerr << "Incomplete message sent" << std::endl;
			return (1);
		}
		else {
			return (0);
		}
	}
	else {
		std::cerr << "Unknown error in poll()" << std::endl;
		return (1);
	}
}

int command_executing(std::pair<int, std::pair<std::string, User> > user_entry) {
	COMMANDS command = parse(user_entry.second.first);
	if (!user_entry.second.second.get_veification())
	{
		if (command == PASS)
		{
			// check password
			// if correct
			send_user_message(user_entry, "Password accepted\r\n");
			user_entry.second.second.set_verified(true); // not a pointer so outside isnt changed
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
			std::cout << "Handling JOIN command" << std::endl;
			// Handle JOIN command
			break;
		case NICK:
			std::cout << "Handling NICK command" << std::endl;
			// Handle NICK command
			break;
		case USER:
			std::cout << "Handling USER command" << std::endl;
			// Handle USER command
			break;
		case PASS:
			std::cout << "Handling PASS command" << std::endl;
			// Handle PASS command
			break;
		case CAP:
			std::cout << "Handling CAP command" << std::endl;
			// Handle CAP command
			break;
		case PING:
			std::cout << "Handling PING command" << std::endl;
			// Handle PING command
			break;
		case PONG:
			std::cout << "Handling PONG command" << std::endl;
			// Handle PONG command
			break;
		case PRIVMSG:
			std::cout << "Handling PRIVMSG command" << std::endl;
			// Handle PRIVMSG command
			break;
		case NOTICE:
			std::cout << "Handling NOTICE command" << std::endl;
			// Handle NOTICE command
			break;
		case QUIT:
			std::cout << "Handling QUIT command" << std::endl;
			// Handle QUIT command
			break;
		case PART:
			std::cout << "Handling PART command" << std::endl;
			// Handle PART command
			break;
		case TOPIC:
			std::cout << "Handling TOPIC command" << std::endl;
			// Handle TOPIC command
			break;
		case MODE:
			std::cout << "Handling MODE command" << std::endl;
			// Handle MODE command
			break;
		case WHO:
			std::cout << "Handling WHO command" << std::endl;
			// Handle WHO command
			break;
		case WHOIS:
			std::cout << "Handling WHOIS command" << std::endl;
			// Handle WHOIS command
			break;
		case LIST:
			std::cout << "Handling LIST command" << std::endl;
			// Handle LIST command
			break;
		case INVITE:
			std::cout << "Handling INVITE command" << std::endl;
			// Handle INVITE command
			break;
		case KICK:
			std::cout << "Handling KICK command" << std::endl;
			// Handle KICK command
			break;
		case KILL:
			std::cout << "Handling KILL command" << std::endl;
			// Handle KILL command
			break;
		case AWAY:
			std::cout << "Handling AWAY command" << std::endl;
			// Handle AWAY command
			break;
		case OPER:
			std::cout << "Handling OPER command" << std::endl;
			// Handle OPER command
			break;
		case SQUIT:
			std::cout << "Handling SQUIT command" << std::endl;
			// Handle SQUIT command
			break;
		case ERROR:
			std::cout << "Handling ERROR command" << std::endl;
			// Handle ERROR command
			break;
		case UNKNOWN:
			std::cout << "Handling UNKNOWN command" << std::endl;
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
		std::cout << this->_users.find(pollfds[i].fd)->second.second.get_user_name() << " disconnected." << std::endl;
		pollfds.erase(pollfds.begin() + i);
	} else {
		// Process data from connected client
		this->_users.find(pollfds[i].fd)->second.first += std::string(buffer, bytesRead);
		//if (std::string(buffer, bytesRead).find("\r\n") != std::string::npos) // irssi
		if (std::string(buffer, bytesRead).find("\n") != std::string::npos) // netcat
		{
			command_executing(*this->_users.find(pollfds[i].fd));
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
