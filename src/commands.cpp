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

int Server::join(Client*client, std::vector<string> arg)
{
	char delimiter = ',';

	if (arg.size() < 2)
		return (1);

	for (chIt it = _channels.begin(); it != _channels.end(); it++)
	{
		string channelName = it->getName();
		size_t last = 0, next = 0;
		while ((next = arg[0].find(delimiter, last)) != std::string::npos)
		{
			string name = arg[0].substr(last, next - last);
			if (name.compare(channelName) == 0)
			{
				
			}
			std::cout << name << std::endl;
			last = next + 1;
			std::cout << arg[0].substr(last);
		}
		std::cout << arg[0].substr(last) << std::endl;
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
