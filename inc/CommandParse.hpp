#ifndef COMMANDPARSE_HPP
# define COMMANDPARSE_HPP

# include "utils.h"


# define KICK_USAGE "usage: KICK <channel> <user>"
# define INVITE_USAGE "usage: INVITE <user> <channel>"
# define TOPIC_USAGE "usage: TOPIC: <channel> [<topic>]"
# define MODE_USAGE "usage: MODE <channel> {[+ | -] | i | t | k | o | l}"

# define CMD_LIST {"KICK", "INVITE", "TOPIC", "MODE"}
# define ECMD_LIST {KICK,INVITE,TOPIC,MODE,INVALID}
# define MODE_OPTIONS {'i', 't', 'k', 'o', 'l'}
# define NB_CMD 4

using std::string;

enum e_cmd{
	KICK,
	INVITE,
	TOPIC, 
	MODE,
	INVALID
};

class CommandParse
{
	private:

	public:
		e_cmd validCommand(string line);

};

#endif