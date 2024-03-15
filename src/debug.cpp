#include "Server.hpp"

void Server::dprint(string message) const{
    if(debug)
        this->print(MESSAGE_COLOR("\033[33;1m", message));
}
