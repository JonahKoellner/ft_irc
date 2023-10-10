/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:46:17 by jonahkollne       #+#    #+#             */
/*   Updated: 2023/10/10 15:13:58 by jkollner         ###   ########.fr       */
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

#define RECEIVE_BUFFER_SIZE 5

enum COMMANDS {JOIN, ME, NICK, USER, PASS, CAP, PING, PONG, PRIVMSG, NOTICE, QUIT, PART, TOPIC, MODE, WHO, WHOIS, LIST, INVITE, KICK, KILL, AWAY, OPER, SQUIT, ERROR, UNKNOWN};

class Server {
	private:
		std::string			_servername;
		int					_port;
		std::string			_password;
		std::vector<Chat>	_chats;
		int					_serverSocketFD;
		//std::vector<User>	_users;
		std::unordered_map<int, std::pair<std::string, User> > _users;
		int	bind_socket();
		int	start_listening();
		int	server_loop();
		int init_readSet(std::vector<int> clientSockets, fd_set &readSet);
		int	handle_new_connection(std::vector<pollfd> &pollfds);
		int	handle_client_data(std::vector<pollfd> &pollfds, int clientSocketFD, int i);
		int command_executing(std::pair<std::string, User> &user_entry);
		int	send_user_message(User user_entry, std::string message);
		int	join_channel(User &user, std::string channel_name);
		int	create_channel(std::string channel_name);

	public:
		//Server() {};
		Server(std::string servername, int port, std::string password);
		Server(std::string password);
		~Server();
		int	start_server();
};
