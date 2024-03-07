#include "Server.hpp"

int Server::nick(Client*client, const string&arg)
{
	(void)client;
	(void)arg;

	std::cout << "nick" << std::endl;
	return 0;
}

int Server::user(Client*client, const string&arg)
{
	(void)client;
	(void)arg;

	std::cout << "user" << std::endl;
	return 0;
}

int Server::pass(Client*client, const string&arg)
{
	(void)client;
	(void)arg;

	

	std::cout << "pass" << std::endl;
	return 0;
}

int Server::quit(Client*client, const string&arg)
{
	(void)client;
	(void)arg;

	std::cout << "quit" << std::endl;
	return 0;
}

int Server::join(Client*client, const string&arg)
{
	(void)client;
	(void)arg;

	std::cout << "join" << std::endl;
	return 0;
}

int Server::topic(Client*client, const string&arg)
{
	(void)client;
	(void)arg;

	std::cout << "topic" << std::endl;
	return 0;
}

int Server::names(Client*client, const string&arg)
{
	(void)client;
	(void)arg;

	std::cout << "names" << std::endl;
	return 0;
}

int Server::invite(Client*client, const string&arg)
{
	(void)client;
	(void)arg;

	std::cout << "invite" << std::endl;
	return 0;
}

int Server::kick(Client*client, const string&arg)
{
	(void)client;
	(void)arg;

	std::cout << "kick" << std::endl;
	return 0;
}

int Server::mode(Client*client, const string&arg)
{
	(void)client;
	(void)arg;

	std::cout << "mode" << std::endl;
	return 0;
}


void Server::init(void)
{
	_commandsMap.insert(std::make_pair<string, int (Server::*)(Client *, const string &)>("NICK", &Server::nick));
	_commandsMap.insert(std::make_pair<string, int (Server::*)(Client *, const string &)>("USER", &Server::user));
	_commandsMap.insert(std::make_pair<string, int (Server::*)(Client *, const string &)>("PASS", &Server::pass));
	_commandsMap.insert(std::make_pair<string, int (Server::*)(Client *, const string &)>("QUIT", &Server::quit));
	_commandsMap.insert(std::make_pair<string, int (Server::*)(Client *, const string &)>("TOPIC", &Server::topic));
	_commandsMap.insert(std::make_pair<string, int (Server::*)(Client *, const string &)>("NAMES", &Server::names));
	_commandsMap.insert(std::make_pair<string, int (Server::*)(Client *, const string &)>("INVITE", &Server::invite));
	_commandsMap.insert(std::make_pair<string, int (Server::*)(Client *, const string &)>("KICK", &Server::kick));
	_commandsMap.insert(std::make_pair<string, int (Server::*)(Client *, const string &)>("MODE", &Server::mode));
}
