#ifndef COMMAND_HPP
# define COMMAND_HPP

# include <map>
# include <list>
# include <vector>
# include "CustomException.hpp"
# include "Client.hpp"
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
*/

//Usage error messages
# define KICK_USAGE "usage: KICK <channel> <user>\n"
# define INVITE_USAGE "usage: INVITE <channel> <user>\n"
# define TOPIC_USAGE "usage: TOPIC: <channel> [<topic>]\n"
# define MODE_USAGE "usage: MODE <channel> {[+ | -] | i | t | k | o | l}\n"
# define NICK_USAGE "usage: NICK <nickname>\n"
# define USER_USAGE "usage: USER <username>\n"
# define PASS_USAGE "usage: PASS <password>\n"
# define QUIT_USAGE "usage: QUIT [<Quit message>]\n"
# define JOIN_USAGE "usage: JOIN <channel>{,<channel>,...} [<key>{,<key>,...}]\n"
# define NAMES_USAGE "usage: NAMES\n"

//Error
// # define TOO_MANY_ARGS "Too many parameters"

//Defines for the commands
# define CMD_LIST {"KICK", "INVITE", "TOPIC", "MODE", "NICK", "USER", "PASS", "QUIT", "JOIN", "NAMES", "PRIVMSG"}
# define ECMD_LIST {KICK,INVITE,TOPIC,MODE,NICK,USER,PASS,QUIT,JOIN,NAMES,PRIVMSG,INVALID}
# define NB_CMD 11
# define MAX_ARG_SIZE 15

//Defines for the options in the MODE command
# define MODE_OPTIONS {'i', 't', 'k', 'o', 'l'}
# define NB_OPTIONS 5


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
	PRIVMSG,
	INVALID
};

class Command
{
	private:
      bool _valid;
      string _currentCommand;
      e_cmd _enumCommand;
      int _commandReturn;
      std::vector<string> _args;
		void setArgs(string line, size_t startPos);
		bool validOptions(void);

	public:
      Command();
      ~Command();

      int getReturn(void) const;
      void commandReset(void);
      bool getValid(void) const;
      string getCommand(void) const;
      std::vector<string> getArgs(void) const;
      void setReturn(int value);
		bool validCommand(string line);
      bool allowedCommand(Registration access, bool admin);
};

#endif
