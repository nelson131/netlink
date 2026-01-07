#include "utils.h"

#include "net.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    char* input = NULL;
    net network;

    while((input = readline("> "))){
        char* command = NULL;
        get_arg(0, input, &command);
        if(!strcmp(command, "open")){
            if(get_args(input) == 3){
                char* port = NULL;
                get_arg(1, input, &command);
                if(strcmp(command, "def") != 0){
                    port = command;
                } else {
                    port = "8080";
                }

                if(serv_init(&network, port) != 0 || serv_conn(&network) != 0){
                    nlog(1, "Something went wrong in server setup");
                    free(command);
                    break;
                }

                size_t close_it = 0;
                chat(network.connfd, &close_it);
                if(close_it){
                    free(command);
                    break;
                }
                
            } else {
                log(1, "Usage: open <port:def/8080...>");
            }
        } else if(!strcmp(command, "connect")){
            if(cli_init(&network) != 0 || cli_conn(&network) != 0){
                nlog(1, "Something went wrong in client setup");
                quit(&network);
                free(command);
                break;
            }
        } else {
            nlog(1, "Usage: <command:open/connect>");
        }

        quit(&network);
        free(input);
        free(command);
    }
    
    if(input) free(input);
    quit(&network);

    return 0;
}