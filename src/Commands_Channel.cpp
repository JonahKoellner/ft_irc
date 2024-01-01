/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands_Channel.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreidenb <mreidenb@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 22:15:49 by mreidenb          #+#    #+#             */
/*   Updated: 2024/01/01 22:51:59 by mreidenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commander.hpp"

int	Commander::handle_mode() {
	Executer ex(this->_database);
	if (this->_commandArguments.size() < 1)
		return (1);
	if (this->_commandArguments[0][0] != '#')
		return (ex.send_user_message(this->_userSocket_FD, std::string("Invalid channel name\r\n")));
	std::string name = ex.get_user(this->_userSocket_FD).get_user_name();
	std::string chan = ex.get_user(this->_userSocket_FD).get_channel();
	std::string message = name + " has changed the mode of " + this->_commandArguments[0] + "\r\n";
	ex.send_message_chat(chan, message);
	return (0);
}

int	Commander::handle_kick () {
	Executer ex(this->_database);
	if (this->_commandArguments.size() < 1)
		return (1);
	if (this->_commandArguments[0][0] != '#')
		return (ex.send_user_message(this->_userSocket_FD, std::string("Invalid channel name\r\n")));
	std::string chan = this->_commandArguments[0];
	std::string name = this->_commandArguments[1];
	std::string message = name + " has been kicked from " + chan + "\r\n";
	ex.send_message_chat(chan, message);
	return (ex.kick_user(this->_userSocket_FD, name, chan));
}

int Commander::handle_invite() {
	Executer ex(this->_database);
	if (this->_commandArguments.size() < 1)
		return (1);
	if (this->_commandArguments[0][0] != '#')
		return (ex.send_user_message(this->_userSocket_FD, std::string("Invalid channel name\r\n")));
	std::string chan = this->_commandArguments[0];
	std::string targetName = this->_commandArguments[1];
	std::string senderName = ex.get_user(this->_userSocket_FD).get_user_name();
	std::string message = ":" + targetName + " INVITE " + senderName + " :" + chan + "\r\n";
	return (ex.send_message_to_user(targetName, message));
}

int Commander::handle_topic() {
	Executer ex(this->_database);
	if (this->_commandArguments.size() < 1)
		return (1);
	if (this->_commandArguments[0][0] != '#')
		return (ex.send_user_message(this->_userSocket_FD, std::string("Invalid channel name\r\n")));
	std::string chan = this->_commandArguments[0];
	std::string topic = this->_commandArguments[1];
	std::string name = ex.get_user(this->_userSocket_FD).get_user_name();
	std::string message = name + " has changed the topic of " + chan + " to " + topic + "\r\n";
	ex.send_message_chat(chan, message);
	return (ex.set_channelName(this->_userSocket_FD, chan, topic));
}
