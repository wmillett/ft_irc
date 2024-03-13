#include "Channel.hpp"
#include "utils.h"

Channel::Channel(Client* op, string name, string* key) : _name(name), _inviteOnly(false), _key(key), _userLimit(0)
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

}

void Channel::sendTopic(Client* client) // send to client fd
{
	if (client)
	{
		if (_topic)
		{
			
		}
	}
}

void Channel::addUser(Client* client)
{
	if (client)
	{
		this->_clients.push_back(client);
		client->addChannel(this);
	}
}

void Channel::removeUser(Client* client)
{
	(void)client;
}

string Channel::getName(void)
{
	return (_name);
}

int Channel::isKeyValid(string key)
{
	if (!this->getKey())
		return (0);
	if ((this->getKey())->compare(key) == 0)
		return (0);
	return (1);
}

string* Channel::getKey(void)
{
	return (this->_key);
}
int Channel::isInviteOnly(void)
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
	return (this->isChannelFull() && this->isInviteOnly() && \
	this->isKeyValid(*key) && this->isUserInChannel(client));
}

int Channel::isChannelFull(void) // returns 0 if channel is full
{
	if (_clients.size() == _userLimit)
	{
		return (0);
	}
	return (1);
}