#include "Channel.hpp"
#include "utils.h"

Channel::Channel(Client* op, string name, string* key) : _name(name), _inviteOnly(false), _key(key)
{
	if (op)
	this->_clients.push_back(op);
	this->_operators.push_back(op);
	this->_topic = NULL;
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
		this->_clients.push_back(client);
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
	if (!this->_key)
		return (1);
	if (key.compare(key) == 0)
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