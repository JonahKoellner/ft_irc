/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PollBot.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:22:47 by jkollner          #+#    #+#             */
/*   Updated: 2023/10/23 09:54:26 by jkollner         ###   ########.fr       */
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
class PollBot : private Bot {
	public:
		PollBot();
		void StartPoll();
		void VoteInPoll();
		void ShowPollResult();
		~PollBot();
};
