#include "Server.hpp"
#include "utils.h"

void Server::createChannel(Client* client, string& name, string *key) // cannot fail
{
	if (_channels.size() < _channels.capacity()) //TODO: new may not work here
	{
		string* allocKey = new string(*key);
		_channels.push_back(new Channel(client, name, allocKey));
	}
}

Channel* Server::doesChannelExist(string& channel) //cannot fail, returns a pointer to the right channel or NULL if it doesn't exitst
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
	std::vector<string> keys;
	buildStrings(arg[0], delimiter, channels);
	buildStrings(arg[1], delimiter, keys);

	for (size_t i = 0; i < channels.size(); i++)
	{
		Channel* toJoin = this->doesChannelExist(channels[i]);
		if (toJoin)
		{
			if (toJoin->canAddToChannel(client, ((i < keys.size()) ? (&keys[i]) : NULL)) == 0) //TODO: does this work?
				toJoin->addUser(client);
			else
				sendMessage(client->getSocket(), _serverName, \
				client->getNickname(), ERR_CANTJOINCHAN(client->getNickname(), channels[i], "other")); //TODO: change error string (maybe)
		}
		else
		{
			if ((channels[i])[0] != '#') // ADD '#' to the start if not present
			{
				std::string::iterator it = channels[i].begin();
				channels[i].insert(it, '#');
			}
			if (this->isChannelNameValid(channels[i]))
			{
				if (i < keys.size())
				this->createChannel(client, channels[i], &keys[i]);
			}
			else
				sendMessage(client->getSocket(), _serverName, \
				client->getNickname(), ERR_BADCHANMASK(channels[i]));
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