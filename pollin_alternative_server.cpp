/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pollin_alternative_server.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonahkollner <jonahkollner@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 20:14:00 by jonahkollne       #+#    #+#             */
/*   Updated: 2023/10/08 20:14:04 by jonahkollne      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <poll.h>

constexpr int MAX_CLIENTS = 10;
constexpr int PORT = 8080;

int main() {
    int serverSocket, newSocket;
    sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    // Create socket
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error creating socket");
        return -1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error binding");
        return -1;
    }

    // Listen
    if (listen(serverSocket, MAX_CLIENTS) == -1) {
        perror("Error listening");
        return -1;
    }

    std::vector<pollfd> fds;
    fds.push_back({serverSocket, POLLIN}); // Add server socket to the poll set

    while (true) {
        int numReady = poll(fds.data(), fds.size(), -1);

        if (numReady == -1) {
            perror("Error in poll");
            break;
        }

        for (size_t i = 0; i < fds.size(); ++i) {
            if (fds[i].revents & POLLIN) {
                if (fds[i].fd == serverSocket) {
                    // New connection
                    if ((newSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen)) == -1) {
                        perror("Error accepting connection");
                    } else {
                        std::cout << "New connection established." << std::endl;
                        fds.push_back({newSocket, POLLIN});
                    }
                } else {
                    // Handle data from a client
                    char buffer[1024];
                    int bytesRead = recv(fds[i].fd, buffer, sizeof(buffer), 0);
                    if (bytesRead <= 0) {
                        // Connection closed or error
                        close(fds[i].fd);
                        fds.erase(fds.begin() + i);
                        std::cout << "Client disconnected." << std::endl;
                    } else {
                        // Process data from the client
                        buffer[bytesRead] = '\0';
                        std::cout << "Received: " << buffer << std::endl;
                    }
                }
            }
        }
    }

    // Close all client sockets
    for (size_t i = 1; i < fds.size(); ++i) {
        close(fds[i].fd);
    }

    // Close the server socket
    close(serverSocket);

    return 0;
}
