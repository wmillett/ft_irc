#include "Server.hpp"

Client* Server::isTargetAUser(string& target) //returns a pointer to the user if it exists
{
	for (std::map<int,Client*>::iterator it = _clients.begin(); it != _clients.end(); it++) // why error
	{
		if (it->second->getNickname() == target)
			return (it->second);
	}
	return (NULL);
}


Channel* Server::isTargetAChannel(string& target) // returns a pointer to the channel if it exists
{
	std::cout << _channels.size() << std::endl;
	for (chIt it = _channels.begin(); it < _channels.end(); it++)
	{
		std::cout << (*it)->getName() << std::endl;
		if ((*it)->getName() == target)
			return (*it);
	}
	
	return (NULL);
}

void sendArgs(Server* irc, Client* sender, Client* target, std::vector<string>& arg)
{
	if (sender == target)
		return ;

	string message;
	for (strIt it = arg.begin(); it != arg.end(); it++)
	{
		if ((it + 1) != arg.end())
			message += (*it + " ");
		else
			message += *it;
	}

	irc->sendMessage(target, sender->getNickname(), target->getNickname(), message);
}