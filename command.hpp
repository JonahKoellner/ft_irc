/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:38:55 by jkollner          #+#    #+#             */
/*   Updated: 2023/10/09 13:41:57 by jkollner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iostream"
#include "util.h"
#include "User.hpp"

class Command {

	public:
		int	Command_Handle(std::pair<int, std::pair<std::string, User> >);
};
