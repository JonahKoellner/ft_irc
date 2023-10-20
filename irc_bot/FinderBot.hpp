/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FinderBot.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:27:15 by jkollner          #+#    #+#             */
/*   Updated: 2023/10/20 14:28:15 by jkollner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Bot.hpp"

/**
 * Bot to find other user by their name. Returns the channel they are in.
 * You can also make yourself invisible to this bot
*/
class FinderBot : public Bot {
	public:
		FinderBot();
		~FinderBot();
};
