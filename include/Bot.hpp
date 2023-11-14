/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:17:08 by jkollner          #+#    #+#             */
/*   Updated: 2023/10/23 09:53:01 by jkollner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

class Bot {
	virtual void	joinChannel(std::string channel) = 0;
	virtual void	start_bot() = 0;
	virtual void	stop_bot() = 0;
	virtual void	sendMessage(std::string message) = 0;
};
