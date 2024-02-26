#ifndef UTILS_HPP
# define UTILS_HPP

//Librairies
# include <iostream>
# include <cstdbool>
# include <cstdlib>

//Defines
# define NO_PORT "Error: no port provided"
# define NO_PASSWORD "Error: no password provided"
# define PORT_TOO_LARGE "Error: port provided is above the max limit"
# define PORT_TOO_SMALL "Error: port provided is under the min limit"
# define INVALID_INPUT  "Error: invalid input"
# define PORT_OUT_RANGE "Error: port provided is out of the range"
# define MISSING_ARGS "Error: missing 2 arguments"
# define USAGE_MESS "Error: Usage: ./ircserv <port> <password>"
# define NCREATE_PORT "Error: could not create port"
# define ERROR_BIND "Error: Failed to bind socket"
# define ERROR_LISTEN "Error: Failed to listen for connections"

#endif