#include "Server.hpp"

int Server::user(Client*client, const string&arg)
{

	std::cout << "user" << std::endl;
	return 0;




}

int Server::nick(Client*client, const string&arg)
{
	//return error if no argument
	
	if(!nicknameCheck(arg) || arg.size() > NICKLEN)
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

int Server::pass(Client*client, std::vector<string>arg)
{
	(void)client;

	if(arg == _password)
		return 1;
	else 
		return 0; //and throw error and then close connection for that client
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
	(void)client;
	(void)arg;
	// char delimiter = ',';

	// std::cout << arg << std::endl;
	// //TODO: test when what I receive is clear
	// for (chIt it = _channels.begin(); it != _channels.end(); it++)
	// {
	// 	string channelName = it->getName();
	// 	size_t last = 0, next = 0;
	// 	while ((next = arg.find(delimiter, last)) != std::string::npos)
	// 	{
	// 		string name = arg.substr(last, next - last);
	// 		if (name.compare(channelName) == 0)
	// 		{

	// 		}
	// 		std::cout << name << std::endl;
	// 		last = next + 1;
	// 		std::cout << arg.substr(last);
	// 	}
	// 	std::cout << arg.substr(last) << std::endl;
	// }

	// std::cout << "join" << std::endl;
	// return 0;
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
	(void)client;
	(void)arg;
	// string a = arg, channel, user;
	// char delimiter = ' ';
	// size_t next = 0, last = 0;

	// for (chIt it = _channels.begin(); it != _channels.end(); it++)
	// {
	// 	string channelName = it->getName();
		
	// }

	// std::cout << "invite" << std::endl;
	// return 0;
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
