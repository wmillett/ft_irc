#pragma once
#include "replies.h"
#include "Client.hpp"
#include <map>

using std::string;
class Client;

/*
	Channels names are strings (beginning with a '&', '#', '+' or '!'
   character) of length up to fifty (50) characters.  Channel names are
   case insensitive.

   Apart from the the requirement that the first character being either
   '&', '#', '+' or '!' (hereafter called "channel prefix"). The only
   restriction on a channel name is that it SHALL NOT contain any spaces
   (' '), a control G (^G or ASCII 7), a comma (',' which is used as a
   list item separator by the protocol).  Also, a colon (':') is used as
   a delimiter for the channel mask.  The exact syntax of a channel name
   is defined in "IRC Server Protocol" [IRC-SERVER].

	Channels with '&' as prefix are local to the server where they are
   created.

	Channel operators are identified by the '@' symbol next to their
   nickname whenever it is associated with a channel (i.e., replies to
   the NAMES, WHO and WHOIS commands).

	Since channels starting with the character '+' as prefix do not
   support channel modes, no member can therefore have the status of
   channel operator.

   A user who creates a channel with the character '!' as prefix is
   identified as the "channel creator".  Upon creation of the channel,
   this user is also given channel operator status.

   In recognition of this status, the channel creators are endowed with
   the ability to toggle certain modes of the channel which channel
   operators may not manipulate.

   When displaying a message in the channel from a channel op, the prefix
   '@' is added before the name.

   While a client is joined to a channel, they receive all relevant information
   about that channel including the JOIN, PART, KICK, and MODE messages
   affecting the channel. They receive all PRIVMSG and NOTICE messages
   sent to the channel, and they also receive QUIT messages from other
   clients joined to the same channel (to let them know those users have
   left the channel and the network). This allows them to keep track of other
   channel members and channel modes.
*/

class Channel
{
	public:
	Channel(string name, const Client& op);
	~Channel(void);

	void printTopic(const Client& client);
	void addUser(const Client& client);
	void removeUser(const Client& client);
	string getName(void);

	private:
	string _name;
	string* _topic;
	string* _key;
	std::map<bool, const Client&> _clients;
	/* bool indicates whether the connected 
	client is an operator or not */

	enum _eInvalid // for defining invalid characters in channel names
	{
		CTRLG = 7,
		SPACE = ' ',
		COMMA = ','
	};
		
};