/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModerationBot.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:15:52 by jkollner          #+#    #+#             */
/*   Updated: 2023/10/20 14:29:23 by jkollner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include "Bot.hpp"

/**
 * Moderation bot to check if people are behaving
 * Can kick
 * Can disconnect User entirely
*/

class ModerationBot : public Bot {
	public:
		ModerationBot();
		~ModerationBot();
};
