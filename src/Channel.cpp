#include "Channel.hpp"
#include "utils.h"

Channel::Channel(string name) : _name(name)
{
	//this->_connectedClients = NULL;
}

Channel::~Channel(void)
{

}

void Channel::printTopic(const Client& client) // send to client fd
{
	if (_topic)
		send(client.getSocket(), _topic, _topic->size(), 0);
}