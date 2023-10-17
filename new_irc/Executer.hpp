/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executer.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonahkollner <jonahkollner@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:13:03 by jonahkollne       #+#    #+#             */
/*   Updated: 2023/10/14 15:50:19 by jonahkollne      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "User.hpp"
#include "Chat.hpp"
#include <unordered_set>

class Executer{
	private:
		std::unordered_set<std::string> _blackListedNames;
		std::unordered_set<std::string> _blackListedChannelNames;
		int	join_channel(User &user, std::unordered_map<std::string, Chat> &chat, std::string channel_name);
		int	send_user_message(User user_entry, std::string message);
		int	send_message_chat(User user, Chat chat, std::string message);
		int	set_userName(User &user, std::string userName);
		int set_channelName(Chat &chat, std::string channelName);

	public:
		Executer() {
			_blackListedNames.insert("server");
			_blackListedChannelNames.insert("");
		};
		//~Executer();

	friend class Commander; // Limites Executer rights to only Commander
};
