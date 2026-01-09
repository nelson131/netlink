#include "utils.h"

#include "net.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    char* input = NULL;
    char* arg1 = NULL;
    char* arg2 = NULL;
    net network;
    network.sockfd = 0;
    network.connfd = 0;

    send_welcome();

    while((input = readline("> "))){
        char* command = NULL;
        get_arg(0, input, &command);
        if(!strcmp(command, "open") || !strcmp(command, "connect")){
            if(get_args(input) == 3){
                get_arg(1, input, &arg1);
                get_arg(2, input, &arg2);

                char* port = (!strcmp(arg1, "def")) ? "8080" : arg1;
                char* ip = (!strcmp(arg2, "def")) ? "127.0.0.1" : arg2;
        
                if(!strcmp(command, "open")){
                    if(serv_init(&network, ip, port) != 0 || serv_conn(&network) != 0){
                        nlog(1, "Something went wrong in server setup");
                        free(command);
                        break;
                    }

                    chat(network.connfd);
                    free(command);
                    free(port);
                    free(ip);
                    break;
                } else {
                    if(cli_init(&network, ip, port) != 0 || cli_conn(&network) != 0){
                        nlog(1, "Something went wrong in client side");
                        free(command);
                        break;
                    }

                    chat(network.sockfd);
                    free(command);
                    free(port);
                    free(ip);
                    break;
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
    if(arg1) free(arg1);
    if(arg2) free(arg2);

    return 0;
}