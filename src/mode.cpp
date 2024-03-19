#include "Server.hpp"

int Server::validOptions(const string mode) const{
    const char options[] = MODE_OPTIONS;
    size_t i = 0;
    char currentOption = 0;
    char plusMinus = 0;

    while(i < mode.size() && mode[i] == ' ')
        i++;
    if (mode[i] != '+' && mode[i] != '-')
        return false;
    plusMinus = mode[i];
    i++;
    while(mode[i] && mode[i] != ' '){
        for(int j = 0; j < NB_OPTIONS; j++){
            if(mode[i] == options[j]){
                currentOption = mode[i];
                break;
            }
            if(j == NB_OPTIONS - 1)
                return false;
        }
        i++;
    }
    while(++i < mode.size() && mode[i] == ' ')
        ;
    if(mode[i])
        return false;
    // if(currentOption == 'o')

    return true;
}

int Server::mode(Client*client, std::vector<string>arg)
{
	if (arg[0].empty() || arg[1].empty())
	{
		sendMessage(client, _serverName, client->getNickname(), MODE_USAGE);
		return false;
	}
    if(doesChannelExist(arg[0]) == nullptr){
        sendMessage(client, _serverName, client->getNickname(), ERR_NOSUCHCHANNEL);
        return false;
    }
    int argSize = arg.size();
    for(int i = 0; i < argSize; i++){
	    if(!validOptions(arg[i])){
		    sendMessage(client, _serverName, client->getNickname(), INVALID_MODE);
		    return false;
        }
	}
	std::cout << "mode" << std::endl;
	return 0;
}
