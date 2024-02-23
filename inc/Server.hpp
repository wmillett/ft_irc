#ifndef SERVER_HPP
# define SERVER_HPP

#include "utils.h"


using std::string;

class Server
{
	private:
        int _port;
        string _password;

        bool digitsCheck(const std::string &arg) const;
        		
	public:
        Server(const string& port_str,  const string& password);
        ~Server();
        
    class InvalidInputException: public std::exception
    {
        public:
            virtual const char* what() const throw();
    };

    class PortOffRangeException: public std::exception
    {
        public:
            virtual const char* what() const throw();
    };
};

#endif