#include "Channel.hpp"
#include "utils.h"

Channel::Channel(string name, const Client& op) : _name(name)
{
	//this->_connectedClients = NULL;
	this->_clients.insert(std::make_pair(true, op));
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
	this->_clients.insert(std::make_pair(false, client));
}

void Channel::removeUser(const Client& client)
{
	(void)client;
}

string Channel::getName(void)
{
	return (_name);
}