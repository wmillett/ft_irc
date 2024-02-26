#ifndef SERVER_HPP
# define SERVER_HPP

#include "utils.h"
#define MAX_CLIENT 10


using std::string;

class Server
{
	private:
        int _port;
        string _password;
		int _socket;

        bool digitsCheck(const std::string &arg) const;
        		
	public:
        Server(const string& port_str,  const string& password);
        ~Server();
};

#endif