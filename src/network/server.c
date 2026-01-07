#include "server.h"
#include <stdio.h>

#define DEFAULT_PORT 8080

int init(server* server){
    server->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(server->sockfd == -1){
        nlog(1, "Failed to create a server socket");
        return -1;
    }

    server->servaddr.sin_family = AF_INET;
    server->servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    server->servaddr.sin_port = htons(DEFAULT_PORT);

    if(bind(server->sockfd, &server->servaddr, sizeof(server->servaddr)) != 0){
        nlog(1, "Failed to bind the server socket");
        return -1;
    }

    return 0;
}

int conn(server* server){
    if((listen(server->sockfd, 5)) != 0){
        nlog(1, "Failed to listen to connection");
        return -1;
    } else {
        nlog(2, "Server listening to connection...");
    }

    server->connfd = accept(server->sockfd, &server->cli, sizeof(server->cli));
    if(server->connfd < 0){
        nlog(1, "Failed to server accept");
        return -1;
    }

    nlog(0, "Client has been connected!");
}