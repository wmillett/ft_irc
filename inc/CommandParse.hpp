#ifndef COMMANDPARSE_HPP
# define COMMANDPARSE_HPP

# include <map>
# include <list>
# include <vector>
# include "utils.h"

/*
https://www.rfc-editor.org/rfc/rfc2813#section-3.3.1 Section 3.3 Messages
When a server receives a message, it MUST identify its source using
   the (eventually assumed) prefix.  If the prefix cannot be found in
   the server's internal database, it MUST be discarded, and if the
   prefix indicates the message comes from an (unknown) server, the link
   from which the message was received MUST be dropped.  Dropping a link
   in such circumstances is a little excessive but necessary to maintain
   the integrity of the network and to prevent future problems.  Another
   common error condition is that the prefix found in the server's
   internal database identifies a different source (typically a source
   registered from a different link than from which the message
   arrived).

If a full set of parameters is presented, then each MUST be checked
   for validity and appropriate responses sent back to the client.  In
   the case of messages which use parameter lists using the comma as an
   item separator, a reply MUST be sent for each item.

   //TODO: Please implement NAMES and LIST command
*/

//Usage error messages
# define KICK_USAGE "usage: KICK <channel> <user>"
# define INVITE_USAGE "usage: INVITE <channel> <user>"
# define TOPIC_USAGE "usage: TOPIC: <channel> [<topic>]"
# define MODE_USAGE "usage: MODE <channel> {[+ | -] | i | t | k | o | l}"
# define NICK_USAGE "usage: NICK <username> <nickname>"
# define USER_USAGE "usage: USER <username>"
# define PASS_USAGE "usage: PASS <password>"
# define QUIT_USAGE "usage: QUIT [<Quit message>]"
# define JOIN_USAGE "usage: JOIN <channel>"
# define NAMES_USAGE "usage: NAMES"

//Defines for the commands
# define CMD_LIST {"KICK", "INVITE", "TOPIC", "MODE", "NICK", "USER", "PASS", "QUIT", "JOIN", "NAMES"}
# define ECMD_LIST {KICK,INVITE,TOPIC,MODE,NICK,USER,PASS,QUIT,JOIN,NAMES,INVALID}
# define NB_CMD 10

//Defines for the options in the MODE command
# define MODE_OPTIONS {'i', 't', 'k', 'o', 'l'}
# define NB_OPTIONS 5

using std::string;
using std::map;
using std::endl;
using std::cout;

enum e_cmd{
	KICK,
	INVITE,
	TOPIC, 
	MODE,
   NICK,
   USER,
   PASS,
   QUIT,
   JOIN,
   NAMES,
	INVALID
};

class CommandParse
{
	private:
		e_cmd currentCommand;
		map<string, string> _args;
		void setArgs(string line, size_t start_pos, std::list<string> listArgs);
		bool validOptions(void);
	public:
		bool validCommand(string line);

};

#endif