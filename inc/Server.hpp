#ifndef SERVER_HPP
# define SERVER_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/poll.h>
#include "utils.h"

using std::string;

class Server
{
	private:
                int _port;
                int _sockfd;
                string _password;
                // sockaddr_in serverAddr;

                bool digitsCheck(const std::string &arg) const;
                void SetupServer();
        		
	public:
                Server(const string& port_str,  const string& password);
                ~Server();

                int Run();
};

#endif
