#include "Server.hpp"

int Server::user(Client*client, std::vector<string>arg)
{
	string username;

	if(arg.size() == 0)
	{
		send(client->getSocket(), USER_USAGE, strlen(PASS_USAGE), 0);
		return 0;
	}
	
	if(arg[0].empty())
	{
		send(client->getSocket(), USER_USAGE, strlen(PASS_USAGE), 0);
		return 0;
	}	

	if(!client->getUsername().empty())
	{
		send(client->getSocket(), ALREADY_IN, strlen(ALREADY_IN), 0);
		return 0;
	}
	if(!nameCheck(arg[0]))
	{
		send(client->getSocket(), NOT_ALPHA, strlen(NOT_ALPHA), 0);
		return 0;
	}

	if(username.size() > USERLEN)
		username = arg[0].substr(0,USERLEN);
	else
		username = arg[0];
	
	client->setUsername(username);
	client->checkIdentified();
	return 0;
}

int Server::nick(Client*client, std::vector<string>arg)
{

	if(arg.size() == 0)
	{
		send(client->getSocket(), NICK_USAGE, strlen(NICK_USAGE), 0);
		return 0;
	}
	
	if(!nameCheck(arg[0]) || arg[0].size() > NICKLEN)
	{
		//error
		return 0;
	}

	std::map<int,Client*>::iterator it;
	for(it = _clients.begin(); it != _clients.end(); it++)
	{
		if(it->second->getNickname() == arg[0])
		{
			//error
			return 0;
		}
	}
	
	if(!client->getNickname().empty())
		std::cout << client->getNickname() << " changed his nickname to " << arg[0] << std::endl; //send to everyone

	client->setNickname(arg[0]);
	client->checkIdentified();
	return 0;
}

int Server::pass(Client*client, std::vector<string>arg)
{

	// std::cout << _serverName << std::endl;

	if(arg.size() == 0){
		send(client->getSocket(), PASS_USAGE, strlen(PASS_USAGE), 0);
		return 0;
	}


	if(arg[0] == _password){
		if(client->getState() == AUTHENTICATION){
			client->setState(IDENTIFICATION);
			identificationMessage(client);
		}
		return 1;
	}
	else{
		send(client->getSocket(), ERROR_PASSWORD, strlen(ERROR_PASSWORD), 0);
		return 0; //and throw error and then close connection for that client
	}
		//throw CustomException::WrongPassword();
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

	Channels names are strings (beginning with a '&', '#', '+' or '!'
	character) of length up to fifty (50) characters.  Channel names are
	case insensitive.
*/
int Server::join(Client* client, std::vector<string> arg) // standard command to create / join channels
{

	if (arg.size() < 1)
		return (1); //TODO: send appropriate error, this checl may not be necessary

	if (arg.size() == 1 && arg[0].compare("0") == 0)
	{
		//TODO: user leaves all channels it's connected to
	}
	
	if (arg.size() > 1)
	{
		return (this->joinWithKeys(client, arg));
	}

	char delimiter = ',';
	string name;
	std::vector<string> channels;
	buildStrings(arg[0], delimiter, channels);

	for (int i = 0; i < channels.size(); i++)
	{
		Channel* toJoin = isChannelValid(channels[i]);
		if (toJoin)
		{
			if (toJoin->isInviteOnly() == 0)
				return (1); //TODO: make sure the appropriate error is sent too
			toJoin->addUser(client);
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
