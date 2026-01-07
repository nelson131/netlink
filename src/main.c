#include "utils.h"

#include "net.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    char* input = NULL;

    while(input = readline("> ")){
        char* command = NULL;
        net network;

        get_arg(0, input, &command);
        if(!strcmp(command, "open")){
            if(serv_init(&network) != 0 || serv_conn(&network) != 0){
                nlog(1, "Something went wrong in server setup");
                quit(&network);
                free(command);
                break;
            }
        } else if(!strcmp(command, "connect")){
            if(cli_init(&network) != 0 || cli_conn(&network) != 0){
                nlog(1, "Something went wrong in client setup");
                quit(&network);
                free(command);
                break;
            }
        } else {
            nlog(2, "Usage: <command:open/connect>");
        }

        quit(&network);
        free(input);
        free(command);
    }
    
    if(input) free(input);

    return 0;
}