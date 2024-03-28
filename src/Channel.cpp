#include "Channel.hpp"
#include "Server.hpp"
#include "utils.h"

Channel::Channel(Client* op, string name, string* key) : _name(name), _key(key), _userLimit(0), _inviteOnly(false), _topicChange(false)
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

string* Channel::getTopic(void)
{
	if (_topic)
	{
		return (_topic);
	}
	return (NULL);
}

void Channel::setTopic(Server* server, Client* client, std::vector<string> topic)
{
	if (_topic)
	{
		delete _topic;
		_topic = NULL;
	}
	
	string tempTopic;
	for (strIt it = topic.begin(); it != topic.end(); it++) // puts the args together in a single string
	{
		if ((it + 1) != topic.end())
			tempTopic += (*it + " ");
		else
			tempTopic += *it;
	}

	if (tempTopic.length() > TOPICLEN)
	{
		server->sendMessage(client, SERVER_NAME, \
		client->getNickname(), ERR_TOPICTOOLONG(client->getNickname()));
	}

	string* newTopic = new string(tempTopic);
	_topic = newTopic;
	
	this->sendMessage(server, client, RPL_NEWTOPIC(client->getNickname(), this->getName(), *_topic));
}

void Channel::addUser(Server* irc, Client* client) // sends a message to all users in channel that <client> joined
{
	this->_clients.push_back(client);
	client->addChannel(this);

	if(client->getLimeState()){
		string limechatMessage = ":" + client->getNickname() +  " JOIN " + this->getName() + "\r\n";
		send(client->getSocket(), limechatMessage.c_str(), limechatMessage.length(), 0);
	}
	else{
		string ncMessage = irc->getName() + ": " + "Channel joined." + "\n";
		send(client->getSocket(), ncMessage.c_str(), ncMessage.length(), 0);
	}

	this->sendMessage(irc, client, RPL_JOINCHANNEL(client->getNickname(), this->getName()));

	if (this->_topic)
		irc->sendMessage(client, irc->getName(), client->getNickname(), \
		RPL_TOPIC(client->getNickname(), this->getName(), *this->getTopic()));
	sendUsers(irc, client);
}

void Channel::removeUser(Server* irc, Client* client) //removes user from _operators and _clients if valid
{
	if (isUserAnOp(client) == 0)
	{
		for (clIt it = _operators.begin(); it != _operators.end(); it++)
		{
			if (*it == client)
			{
				_operators.erase(it);
				break ;
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
				break ;
			}
		}
		this->sendMessage(irc, client, RPL_LEFTCHANNEL(client->getNickname(), this->getName()));
		irc->sendMessage(client, irc->getName(), client->getNickname(), \
		RPL_LEFTCHANNEL(client->getNickname(), this->getName()));
	}
}

string Channel::getName(void)
{
	return (this->_name);
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
	if (_userLimit > 0 && _clients.size() == _userLimit)
	{
		return (0);
	}
	return (1);
}

void Channel::sendMessage(Server* irc, Client* sender, std::vector<string> arg)
{
	strIt it = arg.begin();
	arg.insert(it, this->getName());
	for (clIt it = _clients.begin(); it != _clients.end(); it++)
	{
		sendArgs(irc, sender, *it, arg);
	}
}

void Channel::sendMessage(Server* irc, Client* sender, std::string str)
{
	for (clIt it = _clients.begin(); it != _clients.end(); it++)
	{
		irc->sendMessage(*it, sender->getNickname(), (*it)->getNickname(), str);
	}
}

void Channel::sendUsers(Server *irc, Client* sender) //lists all the user on the server
{
	irc->sendMessage(sender, irc->getName(), \
	sender->getNickname(), "Sending list of users in " + this->getName() + ":");

	for (clIt it = _clients.begin(); it != _clients.end(); it++)
	{
		if (isUserAnOp(*it) == 0)
		{
			irc->sendMessage(sender, irc->getName(), sender->getNickname(), "@" + (*it)->getNickname());
		}
		else
		{
			irc->sendMessage(sender, irc->getName(), sender->getNickname(), (*it)->getNickname());
		}
	}
}

void Channel::setInviteOnly(bool inviteOnly)
{
	_inviteOnly = inviteOnly;
}

void Channel::setKey(string *key)
{
	if(_key)
		delete _key;
	if(key)
		_key = new string(*key);
	else
		_key = NULL;
}

void Channel::setUserLimit(int n)
{
	_userLimit = n;
}

Client* Channel::getUserByString(string user)
{
	for (clIt it = _clients.begin(); it != _clients.end(); it++)
	{
		if ((*it)->getNickname() == user)
		{
			return *it;
		}
	}
	return NULL;
}

void Channel::addUserOp(Client *client)
{
	if(isUserAnOp(client) == 0)
		return ;
	else
	{
		_operators.push_back(client);
	}
}

void Channel::removeUserOp(Client *client)
{
	for (clIt it = _operators.begin(); it != _operators.end(); it++)
	{
		if (*it == client)
		{
			_operators.erase(it);
		}
	}
}

void Channel::setTopicChange(bool topicChange)
{
	_topicChange = topicChange;
}

bool Channel::getTopicChange(void)
{
	return _topicChange;
}

size_t Channel::getUserLimit(void){
	return _userLimit;
}