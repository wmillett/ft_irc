#include "Channel.hpp"
#include "Server.hpp"
#include "utils.h"

Channel::Channel(Client* op, string name, string* key) : _name(name), _key(key), _userLimit(0), _inviteOnly(false)
{
	if (op)
	{
		this->_clients.push_back(op);
		this->_operators.push_back(op);
		this->_topic = NULL;
		op->addChannel(this);
	}
}

Channel::~Channel(void)
{
	if (this->_key)
	{
		delete _key;
		_key = NULL;
	}
	if (this->_topic)
	{
		delete _topic;
		_topic = NULL;
	}
}

void Channel::sendTopic(Client* client) // TODO: sent to client fd if there is a topic
{
	(void)client;
	if (_topic)
	{

	}
}

void Channel::addUser(Client* client) // sends a message to all users in channel that <client> joined
{
	std::cout << "ADDINGUSER" <<std::endl;
	this->_clients.push_back(client);
	client->addChannel(this);
}

void Channel::removeUser(Client* client) //removes user from _operators and _clients if valid
{
	if (isUserAnOp(client) == 0)
	{
		for (clIt it = _operators.begin(); it != _operators.end(); it++)
		{
			if (*it == client)
			{
				_operators.erase(it);
			}
		}
	}
	if (isUserInChannel(client) == 0)
	{
		for (clIt it = _clients.begin(); it != _clients.end(); it++)
		{
			if (*it == client)
			{
				_clients.erase(it);
			}
		}
	}
}

string Channel::getName(void)
{
	return (_name);
}

string* Channel::getKey(void)
{
	return (this->_key);
}

int Channel::isKeyValid(string* key) // returns 0 if channel has no key or if key is correct
{
	if (this->getKey() == NULL || key == NULL)
	{
		if (this->getKey() == NULL)
			return (0);
		else
			return (1);
	}
	if (*_key == *key)
		return (0);
	return (1);
}
int Channel::isInviteOnly(void) // returns 0 if channel is invite-only
{
	if (_inviteOnly == true)
		return (0);
	return (1);
}

int Channel::isUserInChannel(Client* client) // returns 0 if Client is in channel
{
	for (clIt it = this->_clients.begin(); it < this->_clients.end(); it++)
	{
		if ((*it) == client)
		{
			return (0);
		}
	}
	return (1);
}

int Channel::isUserAnOp(Client* client) // returns 0 if Client is an operator
{
	for (clIt it = this->_operators.begin(); it < this->_operators.end(); it++)
	{
		if ((*it) == client)
		{
			return (0);
		}
	}
	return (1);
}

int Channel::canAddToChannel(Client *client, string* key)
{
	if (this->isChannelFull() == 1 && this->isInviteOnly() == 1 && \
	this->isKeyValid(key) == 0 && this->isUserInChannel(client) == 1)
		return (0);
	return (1);
}

int Channel::isChannelFull(void) // returns 0 if channel is full
{
	if (_clients.size() == _userLimit)
	{
		return (0);
	}
	return (1);
}

void Channel::sendMessage(Server* irc, Client* sender, std::vector<string> arg)
{
	for (clIt it = _clients.begin(); it != _clients.end(); it++)
	{
		if (*it == sender)
			continue ;
		sendArgs(irc, sender, *it, arg);
	}
}

void Channel::sendMessage(Server* irc, Client* sender, std::string& str)
{
	for (clIt it = _clients.begin(); it != _clients.end(); it++)
	{
		if (*it == sender)
			continue ;
		irc->sendMessage(*it, irc->getName(), (*it)->getNickname(), str);
	}
}

//TODO: listUsers method