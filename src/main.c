#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

int main(){
    char* input = NULL;

    while(input = readline("> ")){

        char* command = NULL;
        get_arg(0, input, &command);
        if(!strcmp(command, "open")){
            
        } else if(!strcmp(command, "connect")){

        } else {
            nlog(2, "Usage: <command:open/connect>");
        }

        free(input);
        free(command);
    }
    
    return 0;
}