#ifndef COMMANDPARSE_HPP
# define COMMANDPARSE_HPP

# include <map>
# include <list>
# include <vector>
# include "utils.h"

//Usage error messages
# define KICK_USAGE "usage: KICK <channel> <user>"
# define INVITE_USAGE "usage: INVITE <channel> <user>"
# define TOPIC_USAGE "usage: TOPIC: <channel> [<topic>]"
# define MODE_USAGE "usage: MODE <channel> {[+ | -] | i | t | k | o | l}"

//Defines for the commands
# define CMD_LIST {"KICK ", "INVITE ", "TOPIC ", "MODE "}
# define ECMD_LIST {KICK,INVITE,TOPIC,MODE,INVALID}
# define NB_CMD 4

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