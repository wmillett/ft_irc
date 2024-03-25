#include "Server.hpp"

void Server::createChannel(Client* client, string& name, string *key) // cannot fail
{
	//TODO: add message confirming channel has been created
	if (key)
	{
		string* allocKey = new string(*key);
		_channels.push_back(new Channel(client, name, allocKey));
	}
	else
	{
		_channels.push_back(new Channel(client, name, key));
	}
	sendMessage(client, _serverName, client->getNickname(), "channel created");
}

int Server::joinWithKeys(Client* client, std::vector<string> arg) //join command with keys
{
	//TODO: fill once Server::join() is done
	char delimiter = ',';
	string name;
	std::vector<string> channels;
	std::vector<string> keys;
	channels = buildStrings(arg[0], delimiter, channels);
	keys = buildStrings(arg[1], delimiter, keys);

	for (size_t i = 0; i < channels.size(); i++)
	{
		if ((channels[i])[0] != '#') // ADD '#' to the start if not present
		{
			std::string::iterator it = channels[i].begin();
			channels[i].insert(it, '#');
		}
		Channel* toJoin = this->isTargetAChannel(channels[i]);
		if (toJoin)
		{
			if (toJoin->canAddToChannel(client, ((i < keys.size()) ? &keys[i] : NULL)) == 0) // TODO: does this work?
				toJoin->addUser(this, client);
			else
				sendMessage(client, _serverName, client->getNickname(), ERR_CANTJOINCHAN(client->getNickname(), channels[i], "other")); //TODO: change error string (maybe)
		}
		else
		{
			if (this->isChannelNameValid(channels[i]) == 0)
			{
				if (i < keys.size())
				this->createChannel(client, channels[i], &keys[i]);
			}
			else
				sendMessage(client, _serverName, \
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

std::vector<string> Server::buildStrings(string arg, char delimiter, std::vector<string> vec)
{
	size_t last = 0, next = 0;
	string str;
	std::vector<string> rtn;
	while ((next = arg.find(delimiter, last)) != std::string::npos)
	{
		str = arg.substr(last, next - last);
		vec.push_back(str);
		last = next + 1;
	}
	str = arg.substr(last);
	vec.push_back(str);

	vec.swap(rtn);
	return (rtn);
}