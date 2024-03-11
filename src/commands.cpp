#include "Server.hpp"

int Server::nick(Client*client, std::vector<string>arg)
{
	(void)client;
	(void)arg;

	std::cout << "nick" << std::endl;
	return 0;
}

int Server::user(Client*client, std::vector<string>arg)
{
	(void)client;
	(void)arg;

	std::cout << "user" << std::endl;
	return 0;
}

int Server::pass(Client*client, std::vector<string>arg)
{
	(void)client;
	(void)arg;

	std::cout << "pass" << std::endl;
	return 0;
}

int Server::quit(Client*client, std::vector<string>arg)
{
	(void)client;
	(void)arg;

	std::cout << "quit" << std::endl;
	return 0;
}

/*
	Steps of the JOIN command: 
	1. Take the first channel passed as argument
	2. Look for the channel in the list of channels
	3. If the channel exists, look if there is a key associated to the channel, check if the key is correct.
	4. If the channel does not exist, create the channel with its associated key (if there is one)
	5. Add the client to the channel.
	6. If there is a channel topic, send the topic to the client. (Same as TOPIC command I think)
	7. Send the list of users in the channel to the client. (Same as NAMES command, maybe)


*/
int Server::join(Client*client, std::vector<string> arg)
{
	char delimiter = ',';
	string name;

	if (arg.size() < 2)
		return (1);

	string channels = arg[0];
	string keys = arg[1];

	for (chIt it = _channels.begin(); it != _channels.end(); it++)
	{
		string channelName = it->getName();
		size_t last = 0, next = 0;
		while ((next = channels.find(delimiter, last)) != std::string::npos)
		{
			name = channels.substr(last, next - last);
			if (name.compare(channelName) == 0)
			{
			}
			std::cout << name << std::endl;
			last = next + 1;
			std::cout << channels.substr(last);
		}
		name = channels.substr(last);
		if (name.compare(channelName) == 0)
		{
		}
	}

	std::cout << "join" << std::endl;
	return 0;
}

int Server::topic(Client*client, std::vector<string>arg)
{
	(void)client;
	(void)arg;

	std::cout << "topic" << std::endl;
	return 0;
}

int Server::names(Client*client, std::vector<string>arg)
{
	(void)client;
	(void)arg;

	std::cout << "names" << std::endl;
	return 0;
}

/*
	Steps of the INVITE command: 
	1. Look for nickname to see if user exists.
	2. Looks for the channel to see if it exists.
	3. Check if the inviting user is in the channel.
	4. Check if the inviting user can invite the new user to the channel.
	5. Send an invitation to the user to join the channel.
	6. Send a message to the user that invited the other user to the channel.
	7. Send a message to the channel that the user has been invited to the channel.
*/
//Errors: ERR_NOSUCHCHANNEL, ERR_NOTONCHANNEL, ERR_CHANOPRIVSNEEDED
int Server::invite(Client*client, std::vector<string>arg)
{
	if (arg.size() < 2)
		return (1);

	string channel = arg[1], user = arg[0];
	char delimiter = ' ';
	size_t next = 0, last = 0;

	for (chIt it = _channels.begin(); it != _channels.end(); it++)
	{
		string channelName = it->getName();
		
	}

	std::cout << "invite" << std::endl;
	return 0;
}

int Server::kick(Client*client, std::vector<string>arg)
{
	(void)client;
	(void)arg;

	std::cout << "kick" << std::endl;
	return 0;
}

int Server::mode(Client*client, std::vector<string>arg)
{
	(void)client;
	(void)arg;

	std::cout << "mode" << std::endl;
	return 0;
}


void Server::init(void)
{
	_commandsMap.insert(std::make_pair<string, int (Server::*)(Client *, std::vector<string>)>("NICK", &Server::nick));
	_commandsMap.insert(std::make_pair<string, int (Server::*)(Client *, std::vector<string>)>("USER", &Server::user));
	_commandsMap.insert(std::make_pair<string, int (Server::*)(Client *, std::vector<string>)>("PASS", &Server::pass));
	_commandsMap.insert(std::make_pair<string, int (Server::*)(Client *, std::vector<string>)>("QUIT", &Server::quit));
	_commandsMap.insert(std::make_pair<string, int (Server::*)(Client *, std::vector<string>)>("JOIN", &Server::join));
	_commandsMap.insert(std::make_pair<string, int (Server::*)(Client *, std::vector<string>)>("TOPIC", &Server::topic));
	_commandsMap.insert(std::make_pair<string, int (Server::*)(Client *, std::vector<string>)>("NAMES", &Server::names));
	_commandsMap.insert(std::make_pair<string, int (Server::*)(Client *, std::vector<string>)>("INVITE", &Server::invite));
	_commandsMap.insert(std::make_pair<string, int (Server::*)(Client *, std::vector<string>)>("KICK", &Server::kick));
	_commandsMap.insert(std::make_pair<string, int (Server::*)(Client *, std::vector<string>)>("MODE", &Server::mode));
}
