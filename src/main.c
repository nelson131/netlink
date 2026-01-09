#include "utils.h"

#include "net.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    char* input = NULL;
    net network;
    network.sockfd = 0;
    network.connfd = 0;

    send_welcome();

    while((input = readline("> "))){
        char* command = NULL;
        get_arg(0, input, &command);
        if(!strcmp(command, "open") || !strcmp(command, "connect")){
            if(get_args(input) == 3){
                char* port = NULL;
                get_arg(1, input, &command);
                if(strcmp(command, "def") != 0){
                    port = command;
                } else {
                    port = "8080";
                }

                char* ip = NULL;
                get_arg(2, input, &command);
                if(strcmp(command, "def") != 0){
                    ip = command;
                } else {
                    ip = "127.0.0.1";
                }

                get_arg(0, input, &command);
                if(!strcmp(command, "open")){
                    if(serv_init(&network, ip, port) != 0 || serv_conn(&network) != 0){
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
                    if(cli_init(&network, ip, port) != 0 || cli_conn(&network) != 0){
                        nlog(1, "Something went wrong in client side");
                        free(command);
                        break;
                    }

                    size_t close_it = 0;
                    chat(network.sockfd, &close_it);
                    if(close_it){
                        free(command);
                        break;
                    }
                }
                
            } else {
                nlog(1, "Usage: open/connect <port:def/8080...> <ip:def/...>");
            }
        } else if (!strcmp(command, "exit")){
            free(command);
            break;
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