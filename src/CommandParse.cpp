#include "CommandParse.hpp"



e_cmd validCommand(string line){
    const char* cmds[] = CMD_LIST;
    const e_cmd ecmds[] = ECMD_LIST;
    const char options[] = MODE_OPTIONS;
    const size_t lsize = line.size();
    size_t start_pos = 0;
    e_cmd current_command;
    
    if(lsize == 0 || line.empty())
        return INVALID;
    while(start_pos < lsize && isspace(line[start_pos]))
        start_pos++;

    //Loops through available command to identify the command call
    for(int i = 0; i < NB_CMD; i++){
        if(strncmp(line.c_str() + start_pos, cmds[i], strlen(cmds[i])))
            current_command = ecmds[i];
    }
    return INVALID;










    
}



