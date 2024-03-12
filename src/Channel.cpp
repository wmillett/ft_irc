#include "Channel.hpp"
#include "utils.h"

Channel::Channel(string name, const Client& op) : _name(name), _inviteOnly(false)
{
	//this->_connectedClients = NULL;
	this->_clients.push_back(op);
	this->_operators.push_back(op);
	this->_topic = NULL;
}

Channel::~Channel(void)
{

}

void Channel::printTopic(const Client& client) // send to client fd
{
	if (_topic)
	{
		send(client.getSocket(), _topic, _topic->size(), 0);
		send(client.getSocket(), "\r\n", 2, 0);
	}
}

void Channel::addUser(const Client& client)
{
	this->_clients.push_back(client);
}

void Channel::removeUser(const Client& client)
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