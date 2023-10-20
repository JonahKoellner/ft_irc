/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PollBot.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:22:47 by jkollner          #+#    #+#             */
/*   Updated: 2023/10/20 14:28:49 by jkollner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include "Bot.hpp"
/**
 * Makes Polls for the channel
 * Start Poll
 * Vote for Poll
 * Show result
*/
class PollBot : public Bot {
	public:
		PollBot();
		~PollBot();
};
