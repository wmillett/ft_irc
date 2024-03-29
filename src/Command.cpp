#include "Command.hpp"

// void Command::setQuit(string line, size_t startPos){
//     if(!line[startPos])
//         return ;
//     while(line[startPos])
//         _args[0].push_back(line[startPos++]);
// }

Command::Command(): _valid(false), _currentCommand("INVALID"), _enumCommand(INVALID), _commandReturn(false){
}

Command::~Command(){
}

bool Command::getValid(void) const{
    return _valid;
}

string Command::getCommand(void) const{
    return _currentCommand;
}

std::vector<string> Command::getArgs(void) const{
    return _args;
}

int Command::getReturn(void) const{
    return _commandReturn;
}

void Command::setReturn(int value){
    _commandReturn = value;
}

void Command::commandReset(void){
    _valid = false;
    _commandReturn = false;
    _currentCommand = "INVALID";
    _enumCommand = INVALID;
    _args.clear();
}

bool Command::allowedCommand(Registration access){
    if(access == AUTHENTICATION){
        if (_enumCommand != PASS)
            return false;
        return true;
    }
    if(access == IDENTIFICATION){
        if(_enumCommand != NICK && _enumCommand != USER)
            return false;
        return true;
    }
    return true;
}

void Command::setArgs(string line, size_t startPos){
    string currentString;
    string buffer;

    while (line[startPos]){
        while(isspace(line[startPos]))
            startPos++;
        while(line[startPos] && !isspace(line[startPos]))
            buffer.push_back(line[startPos++]);
        if(!buffer.empty())
            this->_args.push_back(buffer);
        
        buffer.clear();
    }
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
    
    //Loops through available commands to identify the command called
    for(int i = 0; i < NB_CMD; i++){
        if(!strncmp(line.c_str() + start_pos, cmds[i].c_str(), cmds[i].size())){
            _currentCommand = cmds[i];
            _valid = true;
            _enumCommand = ecmds[i];
            end_pos = cmds[i].size() + start_pos;
            break;
        }
    }
    if(line[end_pos] && !isspace(line[end_pos]))
        return this->commandReset(), false;
    if(_valid == false)
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
