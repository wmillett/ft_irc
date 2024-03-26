#include "Server.hpp"

static bool checkNeedStr(char option, char orientation){

    if(orientation == '+'){
        return(option == 'k' || option == 'l' || option == 'o');
    }
    return (option == 'o');
};





// bool Server::executeOption(Client *client, Channel &channel, char option, bool orientation, string *arg) const{
// 	string optionStr(1, option);
// 	for (std::map<std::string, void(Server::*)(Client *client, Channel &channel, bool orientation, string *arg)>::const_iterator it = _optionsMap.begin(); it != _optionsMap.end(); ++it) {
// 		if(it->first == optionStr){
// 			(this->*(it->second))(client, channel, orientation, arg);
//             return false;
// 		}
//     }
// 	return true;
// };
bool Server::executeOption(Client *client, Channel &channel, char option, bool orientation, string *arg){
    string optionStr(1, option);
    for (std::map<std::string, void(Server::*)(Client *client, Channel &channel, bool orientation, string *arg)>::const_iterator it = _optionsMap.begin(); it != _optionsMap.end(); ++it) {
        if(it->first == optionStr){
            (this->*it->second)(client, channel, orientation, arg);
            return false;
        }
    }
    return true;
}




//Notes: will need to add a verification for every string argument encountered by validOptions
bool Server::validOptions(Client*client, Channel &channel, std::vector<string>arg){
    const char options[] = MODE_OPTIONS;
    const string modeStr = arg[1];
    const int sizeArg = arg.size();
    char currentOption = 0;
    char orientation = 0;
    int countArgs = 2;
    bool validCommand = 0;

    //Goes through modeStr to verify if every input is valid
    for(size_t i = 0; modeStr[i]; i++){
        while(isspace(modeStr[i])){
            i++;
        }
        validCommand = false;
        currentOption = modeStr[i];
        if(modeStr[i] == '+' || modeStr[i] == '-'){
            orientation = modeStr[i];
            currentOption = 0;
        }
        else{
            for(int j = 0; j < NB_OPTIONS; j++){
                if(modeStr[i] == options[j]){
                    validCommand = true;
                    break;
                }
				// dprint(("i: " + std::to_string(i)));
				// dprint(DEBUG_VALUE("i: ", i));
				// dprint(("modeStr[i]: " + modeStr[i]));
				// dprint(("validCommand: " + validCommand));
            }
        }
        if(orientation){
            if(currentOption){
                if(validCommand){
                    if(checkNeedStr(currentOption, orientation)){
                        if(countArgs < sizeArg)
                            executeOption(client, channel, currentOption, orientation, &arg[countArgs++]);
                        else
                            sendMessage(client, _serverName, client->getNickname(), MISSING_ARGUMENT(client->getNickname(), currentOption));
                    }
                    else{
                        executeOption(client, channel, currentOption, orientation, nullptr);
                    }
                }
                else
                    sendMessage(client, _serverName, client->getNickname(), ERR_UNKNOWNMODE(client->getNickname(), currentOption));
            }
            else
                ;
        }
        else
            sendMessage(client, _serverName, client->getNickname(), MISSING_ORIENTATION(client->getNickname(), currentOption));
    }
    return false;//
};


int Server::mode(Client*client, std::vector<string>arg)
{
	if(arg.size() == 0)
	{
		sendMessage(client, _serverName, client->getNickname(), MODE_USAGE);//or nothing? not sure how this case is even supposed to happen
		return false;
	}
	if (arg.size() > 1  && (arg[0].empty() || arg[1].empty()))
	{
		sendMessage(client, _serverName, client->getNickname(), MODE_USAGE);
		return false;
	}
	Channel* channel = isTargetAChannel(arg[0]);
    if(channel == nullptr){
        sendMessage(client, _serverName, client->getNickname(), ERR_NOSUCHCHANNEL(client->getNickname(), arg[0]));
        return false;
    }
	if(!validOptions(client, *channel, arg)){//TODO: see note above validOptions fct
	    // sendMessage(client, _serverName, client->getNickname(), INVALID_MODE);
	    return false;
    }
	//maybe add message
	return 0;
}


void Server::mode_i(Client *client, Channel &channel, bool orientation, string *arg)
{
	(void)arg;
	(void)client;
	channel.setInviteOnly(orientation);
	//send message to notify 
}

void Server::mode_t(Client *client, Channel &channel, bool orientation, string *arg)
{
	(void)arg;
	(void)client;
	channel.setTopicChange(orientation);
	//send message to notify
}

void Server::mode_k(Client *client, Channel &channel, bool orientation, string *arg)
{
	(void)client;

	if(orientation == false)
	{
	    channel.setKey(NULL);
	}
	else
	{
		if(arg->empty())
			return ;//send error message
		else
		{
			channel.setKey(arg);
		}
	}
	//send message to notify
}

void Server::mode_o(Client *client, Channel &channel, bool orientation, string *arg)
{

	if(arg->empty())
		return ;//error message

	if(client->getNickname() == *arg)
		return ;//error message 

	Client *target = channel.getUserByString(*arg);
	if(!target)
		return ;//error message

	if(orientation == true)
	{
		channel.addUserOp(target);
	}
	else
	{
		channel.removeUserOp(target);
	}

	//send message to notify
}

void Server::mode_l(Client *client, Channel &channel, bool orientation, string *arg)
{
	(void)client;

	if(orientation == false)
	{
		channel.setUserLimit(0);
	}
	else
	{
		if(arg->empty() || !digitsCheck(*arg))
		{
			//send error message
			return;
		}
		channel.setUserLimit(atoi(arg->c_str()));
	}
	
	//send message to notify
}













// int Server::validOptions(const string mode) const{
//     const char options[] = MODE_OPTIONS;
//     size_t i = 0;
//     char currentOption = 0;
//     char plusMinus = 0;

//     while(i < mode.size() && mode[i] == ' ')
//         i++;
//     if (mode[i] != '+' && mode[i] != '-')
//         return false;
//     plusMinus = mode[i];
//     i++;
//     while(mode[i] && mode[i] != ' '){
//         for(int j = 0; j < NB_OPTIONS; j++){
//             if(mode[i] == options[j]){
//                 currentOption = mode[i];
//                 break;
//             }
//             if(j == NB_OPTIONS - 1)
//                 return false;
//         }
//         i++;
//     }
//     while(++i < mode.size() && mode[i] == ' ')
//         ;
//     if(mode[i])
//         return false;
//     if(currentOption == 'o' || (currentOption == 'k' && plusMinus == '+') || (currentOption == 'l' && plusMinus == '+'))
//         return 2;//to take into account to check another parameter after
//     return true;
// }