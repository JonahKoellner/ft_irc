/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModerationBot.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:15:52 by jkollner          #+#    #+#             */
/*   Updated: 2023/10/23 09:58:32 by jkollner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>
#include "Bot.hpp"

/**
 * Moderation bot to check if people are behaving
 * Can kick
 * Can disconnect User entirely
*/

class ModerationBot : private Bot {
	private:
		//std::vector<std::string> fobiddenWords;
	public:
		//ModerationBot() : forbiddenWords{"Asshole", "Cunt", "Bitch", "Motherfucker"}{

		//};
		ModerationBot();
		~ModerationBot();
};
