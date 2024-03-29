#ifndef UTILS_HPP
# define UTILS_HPP

//Librairies
# include <iostream>
# include <cstdbool>
# include <cstdlib>
# include <limits>
# include <sys/socket.h>
# include <iterator>
# include <netdb.h>
# include <sys/types.h>
# include <vector>
# include <string>
# include <map>
# include "replies.h"

//Defines
# define CHARACTER_LIMIT 512
# define RESET_TERM "\033[2J\033[H"

//Debug
extern bool debug;
extern bool skipPass;
# define DEBUG_STR(x, y) (std::string(x) + std::string(y))
# define DEBUG_VALUE(x, y) (std::string(x) + std::to_string(y))

//General purpose
# define CLIENT_MESS(client, message) (std::string(client) + std::string(message))

//Using
using std::string;
using std::map;
using std::endl;
using std::cout;


//Colours
# define BLACK    = "\033[30;1m"
# define RED      = "\033[0;31m"
# define GREEN    = "\033[32;1m"
# define YELLOW   = "\033[33;1m"
# define BLUE     = "\033[34;1m"
# define PURPLE   = "\033[35;1m"
# define CYAN     = "\033[36;1m"
# define WHITE    = "\033[37;1m"
# define GRAY     = "\033[90;1m"
# define MAGENTA  = "\033[0;95m"
# define BOLD     = "\033[1m"
# define RESET_COLOR    = "\033[0m"
# define MESSAGE_COLOR(x, y) x + y + "\033[0m"


class Channel;
class Client;
class Server;

typedef std::vector<Channel*>::iterator chIt;
typedef std::vector<Client*>::iterator clIt;
typedef std::vector<std::string>::iterator strIt;

void print(string message);
void dprint(string message);

void sendArgs(Server* irc, Client* sender, Client* target, std::vector<std::string>& arg);

#endif