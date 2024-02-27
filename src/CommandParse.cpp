#include "CommandParse.hpp"

void CommandParse::setArgs(string line, size_t startPos, std::list<string> listArgs){
    string currentString;
    string buffer;

    for (std::list<string>::iterator it = listArgs.begin(); it != listArgs.end(); ++it){
        currentString = *it;
        while(line[startPos] == ' ')
            startPos++;
        while(line[startPos] && line[startPos] != ' ')
            buffer.push_back(line[startPos++]);
        this->_args[currentString] = buffer;
        cout << buffer << endl;
        buffer.clear();
    }
}

bool CommandParse::validOptions(void){
    const char options[] = MODE_OPTIONS;
    const string mode = _args["option"];
    size_t i = 0;

    while(i < mode.size() && mode[i] == ' ')
        i++;
    if (mode[i] != '+' && mode[i] != '-')
        return false;
    i++;
    for(int j = 0; j < NB_OPTIONS; j++){
        if(mode[i] == options[j])
            break;
        if(j == NB_OPTIONS - 1)
            return false;
    }
    while(++i < mode.size() && mode[i] == ' ')
        ;
    if(mode[i])
        return false;
    return true;
}

bool CommandParse::validCommand(string line){
    const string cmds[] = CMD_LIST;
    const e_cmd ecmds[] = ECMD_LIST;
    const size_t lsize = line.size();
    size_t start_pos = 0;
    size_t end_pos = 0;
    
    if(lsize == 0 || line.empty())
        return false;
    while(start_pos < lsize && isspace(line[start_pos]))
        start_pos++;
    currentCommand = INVALID;
    //Loops through available commands to identify the command called
    for(int i = 0; i < NB_CMD; i++){
        if(!strncmp(line.c_str() + start_pos, cmds[i].c_str(), cmds[i].size())){
            currentCommand = ecmds[i];
            end_pos = cmds[i].size() + start_pos;
        }
    }

    //Finds the modifiers for each command and validates if the command was called correctly
    std::list<string> argList;
    switch(currentCommand){
        case KICK:
        {
            argList.push_back("channel");
            argList.push_back("user");
            setArgs(line, end_pos, argList);
            if(_args["channel"].empty() || _args["user"].empty())
                return false;
            return true;
        }
        case INVITE:
        {
            argList.push_back("channel");
            argList.push_back("user");
            setArgs(line, end_pos, argList);
            if(_args["channel"].empty() || _args["user"].empty())
                return false;
            return true;
        }
        case TOPIC:
        {
            argList.push_back("channel");
            argList.push_back("topic");
            setArgs(line, end_pos, argList);
            if(_args["channel"].empty())
                return false;
            return true;
        }
        case MODE:
        {
            argList.push_back("channel");
            argList.push_back("option");
            setArgs(line, end_pos, argList);
            if(_args["channel"].empty() || _args["option"].empty())
                return false;
            if(!this->validOptions())
                return false;
            return true;
        }
        default:
            return false;
    }
}
