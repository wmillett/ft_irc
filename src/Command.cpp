#include "Command.hpp"



// void Command::setQuit(string line, size_t startPos){
//     if(!line[startPos])
//         return ;
//     while(line[startPos])
//         _args[0].push_back(line[startPos++]);
// }

void Command::setArgs(string line, size_t startPos){
    string currentString;
    string buffer;
    size_t posString = 0;

    while (line[startPos]){
        while(isspace(line[startPos]))
            startPos++;
        while(line[startPos] && !isspace(line[startPos]))
            buffer.push_back(line[startPos++]);
        this->_args[posString++] = buffer;
        //cout << buffer << endl;
        buffer.clear();
    }
}

bool Command::validOptions(void){
    const char options[] = MODE_OPTIONS;
    const string mode = _args[0];
    size_t i = 0;

    while(i < mode.size() && mode[i] == ' ')
        i++;
    if (mode[i] != '+' && mode[i] != '-')
        return false;
    i++;
    while(mode[i] && mode[i] != ' '){
        for(int j = 0; j < NB_OPTIONS; j++){
            if(mode[i] == options[j])
                break;
            if(j == NB_OPTIONS - 1)
                return false;
        }
        i++;
    }
    while(++i < mode.size() && mode[i] == ' ')
        ;
    if(mode[i])
        return false;
    return true;
}

bool Command::validCommand(string line){
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
            break;
        }
    }
    if(line[end_pos] && !isspace(line[end_pos]))
        return false;
    if(currentCommand == INVALID)
        return false;

    //Place arguments in a vector
    setArgs(line, end_pos);
    return true;




    // //Finds the modifiers for each command and validates if the command was called correctly
    // switch(currentCommand){
    //     case KICK:
    //     {
    //         setArgs(line, end_pos);
    //         if(_args[0].empty() || _args[1].empty())
    //             return false;
    //         return true;
    //     }
    //     case INVITE:
    //     {
    //         setArgs(line, end_pos);
    //         if(_args[0].empty() || _args[1].empty())
    //             return false;
    //         return true;
    //     }
    //     case TOPIC:
    //     {
    //         setArgs(line, end_pos);
    //         if(_args[0].empty())
    //             return false;
    //         return true;
    //     }
    //     case MODE:
    //     {
    //         //can take multiple modes and takes optional arguments for each parameter in modestring
    //         setArgs(line, end_pos);
    //         if(_args[0].empty() || _args[1].empty())
    //             return false;
    //         if(!this->validOptions())
    //             return false;
    //         return true;
    //     }
    //     case NICK:
    //     {
    //         setArgs(line, end_pos);
    //         return true;
    //     }
    //     case USER:
    //     {
    //         setArgs(line, end_pos);
    //         if(_args[0].empty())
    //             return false;
    //         return true;
    //     }
    //     case PASS:
    //     {
    //         setArgs(line, end_pos);
    //         if(_args[0].empty())
    //             return false;
    //         return true;
    //     }
    //     case QUIT:
    //     {
    //         //cannot parse arg using spaces
    //         setArgs(line, end_pos);
    //         return true;
    //     }
    //     case JOIN:
    //     {
    //         //can take multiple channels, need to fix
    //         setArgs(line, end_pos);
    //         if(_args[0].empty())
    //             return false;
    //         return true;
    //     }
    //     case NAMES:
    //     {
    //         return true;
    //     }
    //     default:
    //         return false;
    // }
}
