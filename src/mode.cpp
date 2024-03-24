#include "Server.hpp"

static bool checkNeedStr(char option, char orientation){

    if(orientation == '+'){
        return(option == 'k' || option == 'l' || option == 'o');
    }
    return (option == 'o');
};

//Notes: will need to add a verification for every string argument encountered by validOptions
bool Server::validOptions(std::vector<string>arg) const{
    const char options[] = MODE_OPTIONS;
    const string modeStr = arg[1];
    const int sizeArg = arg.size();
    char currentOption = 0;
    char orientation = 0;
    int countArgs = 2;
    bool done = 0;
    size_t i = 0;

    while(i < modeStr.size() && modeStr[i] == ' ')
        i++;
    if (modeStr[i] != '+' && modeStr[i] != '-')
        return false;//
    orientation = modeStr[i++];

    //Goes through modeStr to verify if every input is valid
    while(modeStr[i]){
        if(modeStr[i] == '+' || modeStr[i] == '-'){
            orientation = modeStr[i];
            done = false;
            currentOption = 0;
        }
        else{
            for(int j = 0; j < NB_OPTIONS; j++){
                if(modeStr[i] == options[j]){
                    currentOption = modeStr[i];
                    done = true;
                    break;
                }
                if(j == NB_OPTIONS - 1)
                    return false;//
            }
        }
        if(currentOption){
            if(checkNeedStr(currentOption, orientation)){
                if(countArgs < sizeArg){
                    countArgs++;
                }
                else
                    return false;//could change return for char* with error message or something else
            }
        }
        i++;
    }
    if (done == true)
        return true;//
    return false;//
};


int Server::mode(Client*client, std::vector<string>arg)
{
	if(arg.size() == 0)
	{
		return false;
	}
	if (arg.size() > 1  && (arg[0].empty() || arg[1].empty()))
	{
		sendMessage(client, _serverName, client->getNickname(), MODE_USAGE);
		return false;
	}
    if(isTargetAChannel(arg[0]) == nullptr){
        sendMessage(client, _serverName, client->getNickname(), ERR_NOSUCHCHANNEL(client->getNickname(), arg[0]));
        return false;
    }
	if(!validOptions(arg)){//TODO: see note above validOptions fct
	    sendMessage(client, _serverName, client->getNickname(), INVALID_MODE);
	    return false;
    }
	std::cout << "mode" << std::endl;
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

	Client * client = channel.getUserByString(*arg);
	if(!client)
		return ;//error message

	if(orientation == true)
	{
		channel.addUserOp(client);
	}
	else
	{
		channel.removeUserOp(client);
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