/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventBot.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:30:40 by jkollner          #+#    #+#             */
/*   Updated: 2023/10/23 09:46:59 by jkollner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Bot.hpp"

/**
 * Can create events
 * Events are channel that are opened after a given time / timer
 * The channel name is the Event name
 * Invite people ?
*/

class EventBot : private Bot {
	public:
		EventBot(std::string channleName, std::string eventName, std::string eventTime);
		EventBot(std::string channelName, std::string eventName, std::string eventTime, std::string eventDescription);
		EventBot(std::string channelName, std::string eventName, std::string eventDescription);
		~EventBot();
};
