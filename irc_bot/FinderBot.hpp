/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FinderBot.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:27:15 by jkollner          #+#    #+#             */
/*   Updated: 2023/10/23 09:41:47 by jkollner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Bot.hpp"

/**
 * Bot to find other user by their name. Returns the channel they are in.
 * You can also make yourself invisible to this bot
*/
class FinderBot : private Bot {
	public:
		FinderBot();
		~FinderBot();
};
