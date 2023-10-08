#include <iostream>
#include <cstring>
#include <vector>
#include <unistd.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <map>

int main() {
	int serverSocket, maxClients = 5;
	fd_set readSet;
	std::vector<int> clientSockets;

	// Create a non-blocking server socket
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1) {
		perror("Socket creation failed");
		return 1;
	}

	// Set the socket to non-blocking mode
	int flags = fcntl(serverSocket, F_GETFL, 0);
	fcntl(serverSocket, F_SETFL, flags | O_NONBLOCK);

	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(8888);

	if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
		perror("Binding failed");
		close(serverSocket);
		return 1;
	}

	if (listen(serverSocket, maxClients) == -1) {
		perror("Listening failed");
		close(serverSocket);
		return 1;
	}

	char buffer[5] ;
	memset(buffer, 0, sizeof(buffer));
	std::unordered_map<int, std::string> commands;
	while (true) {
		// int init_readSet(std::vector<int>clientSockets, fd_set &readSet);
		//{
		FD_ZERO(&readSet);
		FD_SET(serverSocket, &readSet);

		for(int i = 0; i < clientSockets.size(); i++) {
			FD_SET(clientSockets[i], &readSet);
		}
		int maxFd = serverSocket;
		if (!clientSockets.empty())
		{
			int maxClientSocket = *std::max_element(clientSockets.begin(), clientSockets.end());
			if (maxClientSocket > maxFd)
				maxFd = maxClientSocket;
		}

		if (select(maxFd + 1, &readSet, nullptr, nullptr, nullptr) == -1) {
			perror("Select error");
			break;
		}
		//}

		// int handle_new_connections(std::vector<int> &clientSockets, fd_set &readSet);
		//{
		// Check for incoming connections
		if (FD_ISSET(serverSocket, &readSet)) {
			int clientSocket = accept(serverSocket, nullptr, nullptr);
			if (clientSocket != -1) {
				clientSockets.push_back(clientSocket);
				commands.insert(std::map<int, std::string>::value_type(clientSocket, std::string("")));
				//FD_SET(clientSocket, &readSet);
				std::cout << "Accepted connection" << std::endl;
			}
		}
		//}

		
		// Check for data from clients
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
					commands.find(clientSockets[i])->second += std::string(buffer, bytesRead);
					if (std::string(buffer, bytesRead).find('\n') != std::string::npos)
					{
						std::cout << "Received: " << commands.find(clientSockets[i])->second << std::endl;
						if (send(clientSockets[i], commands.find(clientSockets[i])->second.c_str(), commands.find(clientSockets[i])->second.length(), 0) < 0)
							std::cout << "Error sending response" << std::endl;
						commands.find(clientSockets[i])->second = "";
					}
				}
			}
		}
	}

	// Close server socket when done
	close(serverSocket);

	return 0;
}
