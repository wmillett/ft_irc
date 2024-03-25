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

	string* getTopic(void);
	void setTopic(Server* server, Client* client, std::vector<string> topic);
	void addUser(Server* server, Client* client);
	void removeUser(Server* server, Client* client);
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
	void sendUsers(Server *irc, Client* sender);
	

	//zone pour la commande mode de alex et will (pour faciliter le merge avec ta branche )
	void setInviteOnly(bool inviteOnly);
	void setKey(string *key);
	void setUserLimit(int n);
	void addUserOp(Client *client);
	void removeUserOp(Client *client);
	void setTopicChange(bool topicChange);
	Client* getUserByString(string user);

	private:
	string _name;
	string* _topic;
	string* _key;
	std::vector<Client*> _clients;
	std::vector<Client*> _operators;
	size_t _userLimit; //if user limit is 0, there is no limit
	bool _inviteOnly;

	//mode zone
	bool _topicChange;

};