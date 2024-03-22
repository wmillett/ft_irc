#pragma once
#include "utils.h"
#include "Channel.hpp"
#include <vector>


using std::string;
class Channel;
/*
   The characters {}|^ are
   considered to be the lower case equivalents of the characters []\~,
   respectively. This is a critical issue when determining the
   equivalence of two nicknames, or channel names.

   Controlling Flood:
    With a large network of interconnected IRC servers, it is quite easy
   for any single client attached to the network to supply a continuous
   stream of messages that result in not only flooding the network, but
   also degrading the level of service provided to others.  Rather than
   require every 'victim' to provide their own protection, flood
   protection was written into the server and is applied to all clients
   except services.  The current algorithm is as follows:

   * check to see if client's `message timer' is less than current time
     (set to be equal if it is);

   * read any data present from the client;

   * while the timer is less than ten (10) seconds ahead of the current
     time, parse any present messages and penalize the client by two (2)
     seconds for each message;

   * additional penalties MAY be used for specific commands which
     generate a lot of traffic across the network.

   This in essence means that the client may send one (1) message every
   two (2) seconds without being adversely affected.
*/

//Message for successful registration
#define SUCCESS_REGISTER "You are now registered\n"

enum Registration
{
	AUTHENTICATION,
	IDENTIFICATION,
	REGISTERED
};


class Client
{
	private:
		int _sockfd;
		string _username;
		// char _ip[INET_ADDRSTRLEN];
		string _nickname;
		std::vector<Channel*> _channels;
		Registration _registration;
		bool _inLimechat;

	enum _eInvalid // for defining invalid characters in clients, with their ascii value
	{
		SPACE = ' ',
		COMMA = ',',
		QMARK = '?',
		EMARK = '!',
		ATSIGN = '@',
		DOLLAR = '$',
		POUND = '#',
		AMPERSAND = '&',
		TILDE = '~',
		PERCENT = '%',
		PLUS = '+',
		DOT = '.'
	};
	
	public:
		Client(int sockfd);
		~Client();

		string clientInput;

		string getNickname(void) const;
		void setNickname(string nickname);
		string getUsername(void) const;
		void setUsername(string username);
		int getSocket(void) const;
		void setLimeState(bool toSet);

		bool getLimeState(void) const;
		// bool isAdmin(void) const;
		void addChannel(Channel* channel);
		void removeChannel(Channel *channel);
		
		Registration getState(void) const;
		void setState(Registration newState);

		void leaveAllChannels(Server* server);
};
