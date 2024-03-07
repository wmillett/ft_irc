#include "Server.hpp"

int Server::user(Client*client, const string&arg)
{
	(void)client;
	(void)arg;

	std::cout << "user" << std::endl;
	return 0;
}

int Server::nick(Client*client, const string&arg)
{
	//return error if no argument
	
	if(!nicknameCheck(arg))
	{
		//error
		return 0;
	}

	std::map<int,Client*>::iterator it;
	for(it = _clients.begin(); it != _clients.end(); it++)
	{
		if(it->second->getNickname() == arg)
		{
			//error
			return 0;
		}
	}
	
	if(!client->getNickname().empty())
		std::cout << client->getNickname() << " changed his nickname to " << arg << std::endl; //send to everyone

	client->setNickname(arg);

	return 0;
}

int Server::pass(Client*client, const string&arg)
{
	(void)client;
	(void)arg;

	if(arg == _password)
		return 1;
	else 
		return 0; //and throw error and then close connection for that client
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
	//TODO: add JOIN command
}
