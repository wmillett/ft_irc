#include "CommandParse.hpp"

void CommandParse::setArgs(string line, size_t startPos, std::list<string> listArgs){
    for (std::list<string>::iterator it = listArgs.begin(); it != listArgs.end(); ++it){
        string currentString = *it;
        string buffer = NULL;
        while(line[startPos] == ' ')
            startPos++;
        while(line[startPos] && line[startPos] != ' ')
            buffer.push_back(line[startPos++]);
        this->_args[currentString] = buffer;
    }
}

bool CommandParse::validCommand(string line){
    const string cmds[] = CMD_LIST;
    const e_cmd ecmds[] = ECMD_LIST;
    const char options[] = MODE_OPTIONS;
    const size_t lsize = line.size();
    size_t start_pos = 0;
    size_t end_pos = 0;
    
    if(lsize == 0 || line.empty())
        return 0;
    while(start_pos < lsize && isspace(line[start_pos]))
        start_pos++;

    //Loops through available commands to identify the command called
    for(int i = 0; i < NB_CMD; i++){
        if(strncmp(line.c_str() + start_pos, cmds[i].c_str(), cmds[i].size())){
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
                return 0;
            return 1;
        }
        case INVITE:
        {
            argList.push_back("channel");
            argList.push_back("user");
            setArgs(line, end_pos, argList);
            if(_args["channel"].empty() || _args["user"].empty())
                return 0;
            return 1;
        }
        case TOPIC:
        {
            argList.push_back("channel");
            argList.push_back("topic");
            setArgs(line, end_pos, argList);
            if(_args["channel"].empty() || _args["topic"].empty())
                return 0;
            return 1;
        }
        case MODE:
        {
            argList.push_back("channel");
            argList.push_back("option");
            setArgs(line, end_pos, argList);
            if(_args["channel"].empty() || _args["option"].empty())
                return 0;
            return 1;
        }
        default:
            return 0;
    }
}
