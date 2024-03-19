#pragma once
#include "replies.h"
#include "Client.hpp"
#include <map>

using std::string;

class Channel
{
	public:
	Channel(Client* op, string name, string* key);
	~Channel(void);

	enum e_channelErrors
	{
		INVITEONLY,
		NEEDMOREPARAMS,
		BADKEY,
		CHANNELISFULL
	};

	void sendTopic(Client* client);
	void addUser(Server* server, Client* client);
	void removeUser(Client* client);
	string getName(void);
	string* getKey(void);
	int isKeyValid(string* key); // checks if the key is valid for joining channel
	int isInviteOnly(void);
	int isUserInChannel(Client* client);
	int isUserAnOp(Client* client);
	int isChannelFull(void);
	int canAddToChannel(Client* client, string* key); //does the checks to see if user can be added to the channel
	void sendMessage(Server* irc, Client* sender, std::vector<string> arg); // sends the message to all user in the channel
	void sendMessage(Server* irc, Client* sender, std::string str); // same thing but a single string

	private:
	string _name;
	string* _topic;
	string* _key;
	std::vector<Client*> _clients;
	std::vector<Client*> _operators;
	size_t _userLimit; //if user limit is 0, there is no limit
	bool _inviteOnly;

};