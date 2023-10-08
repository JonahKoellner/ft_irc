/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonahkollner <jonahkollner@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:45:33 by jonahkollne       #+#    #+#             */
/*   Updated: 2023/10/06 17:14:34 by jonahkollne      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

int	main(int argc, char *argv[]) {
	Server server("my_server", 4040, "password");
	if (server.start_server())
	{
		std::cout << "Error starting server" << std::endl;
		return (1);
	}
	return (0);
}
