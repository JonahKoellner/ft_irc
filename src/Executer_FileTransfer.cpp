/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executer_FileTransfer.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreidenb <mreidenb@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 13:10:01 by mreidenb          #+#    #+#             */
/*   Updated: 2024/01/02 13:18:21 by mreidenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Executer.hpp"


// In Executer.cpp
int Executer::handle_dcc_send(int sourceSocket_FD, const std::string& targetName, const std::string& file_path, int port, int file_size) {
	// Retrieve the source and target User objects
	User source = _database.get_user(sourceSocket_FD);
	User target = _database.get_user(_database.get_user_fd(targetName));

	// Send DCC ACCEPT command to source
	std::string command = "DCC ACCEPT " + file_path + " " + std::to_string(port) + " " + std::to_string(file_size);
	source.send_command(command);

	// Start client socket and connect to source
	ClientSocket client(source.get_ip(), port);

	// Receive file contents
	std::vector<char> buffer(file_size);
	client.receive(buffer.data(), file_size);

	// Write file contents to a file
	std::ofstream file(file_path, std::ios::binary);
	file.write(buffer.data(), file_size);

	// Close the socket
	client.close();

	return 0;
}