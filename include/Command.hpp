/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreidenb <mreidenb@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:20:08 by mreidenb          #+#    #+#             */
/*   Updated: 2023/11/28 17:56:44 by mreidenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>

class Command{
	private:
		std::string _commandName;
		std::vector<std::string> _commandArguments;
	public:
		Command(std::string commandName, std::vector<std::string> commandArguments);
		std::string get_commandName();
		std::vector<std::string> get_commandArguments();
};