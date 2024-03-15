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

# include "replies.h"
//Defines
# define CHARACTER_LIMIT 512
# define RESET_TERM "\033[2J\033[H"

class Channel;
class Client;
class Server;

typedef std::vector<Channel*>::iterator chIt;
typedef std::vector<Client*>::iterator clIt;
typedef std::vector<std::string>::iterator strIt;

void sendArgs(Server* irc, Client* sender, Client* target, std::vector<std::string>& arg);

#endif