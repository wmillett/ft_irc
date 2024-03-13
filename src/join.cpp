#include "Server.hpp"
#include "utils.h"

void Server::createChannel(Client* client, string& name, string *key) // cannot fail
{
	if (_channels.size() < _channels.capacity()) //TODO: maybe change this
		_channels.push_back(new Channel(client, name, key));
}

Channel* Server::doesChannelExist(string& channel) //cannot fail, returns a pointer to the right channel or NULL
{
	for (chIt it = _channels.begin(); it != _channels.end(); it++)
	{
		string channelName = (*it)->getName();
		if (channelName.compare(channel) == 0)
		{
			return (*it);
		}
	}
	return (NULL);
}

int Server::joinWithKeys(Client* client, std::vector<string> arg) //join command with keys
{
	//TODO: fill once Server::join() is done
	char delimiter = ',';
	string name;
	std::vector<string> channels;
	buildStrings(arg[0], delimiter, channels);

	for (size_t i = 0; i < channels.size(); i++)
	{
		Channel* toJoin = doesChannelExist(channels[i]);
		if (toJoin)
		{
			if (toJoin->isInviteOnly() == 0)
			{
				sendMessage(client->getSocket(), "ircserv", \
				client->getNickname(), ":Channel is in invite-only mode");
				return (1); //TODO: change error string (maybe), may not return
			}
			if (toJoin->isUserInChannel(client) == 1)
				toJoin->addUser(client);
			else
				sendMessage(client->getSocket(), "ircserv", \
				client->getNickname(), ":Already in channel!"); //TODO: change error string (maybe)
		}
		else
		{
			if ((channels[i])[0] != '#') // ADD '#' to the start if not present
			{
				std::string::iterator it = channels[i].begin();
				channels[i].insert(it, '#');
			}
			this->createChannel(client, channels[i], NULL);
		}
	}

	return (0);
}

int Server::isChannelNameValid(string& name) // returns 0 if valid
{
	for (size_t i = 0; i < name.length(); i++)
	{
		if (name.at(i) == ' ' || name.at(i) == 7 || name.at(i) == ',')
			return (1);
	}
	return (0);
}

void Server::buildStrings(string arg, char delimiter, std::vector<string> vec)
{
	size_t last = 0, next = 0;
	string str;
	std::vector<string> rtn;
	while ((next = arg.find(delimiter, last)) != std::string::npos)
	{
		str = arg.substr(last, next - last);
		rtn.push_back(str);
		last = next + 1;
	}
	str = arg.substr(last);
	rtn.push_back(str);

	rtn.swap(vec);
}