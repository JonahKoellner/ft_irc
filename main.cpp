/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:45:33 by jonahkollne       #+#    #+#             */
/*   Updated: 2023/10/09 10:09:13 by jkollner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

#include <iostream>
#include <string>

#include "main.hpp"

#include "main.hpp"

#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
	if (argc != 3) {
		return 1;
	}

	int port = std::stoi(argv[1]);
	Server server("my_server", port, argv[2]);

	if (server.start_server()) {
		std::cout << "Error starting server" << std::endl;
		return 1;
	}

	return 0;
}
