#pragma once
#include "utils.h"
#include "Channel.hpp"


using std::string;
class Channel;
/*
the characters {}|^ are
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
   two (2) seconds without being adversely affected.  Services MAY also
   be subject to this mechanism.
*/

class Client
{
	private:
		int _sockfd;
		string _username;
		string _nickname;
		string *oldNickname; // array of old nicknames
	
	public:
		Client(int sockfd);
		~Client();

		int getSocket(void) const;
};
