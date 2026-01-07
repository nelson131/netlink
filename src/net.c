#include "net.h"
#include <stdio.h>

#define DEFAULT_PORT 8080

int serv_init(net* server){
    server->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(server->sockfd == -1){
        nlog(1, "Failed to create a socket");
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

int serv_conn(net* server){
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

int cli_init(net* client){
    if(serv_init(client) != 0){
        nlog(1, "Something went wrong in client init");
        return -1;
    }

    client->servaddr.sin_addr.s_addr = inet_addr("");
}

int cli_conn(net* client){
    if(connect(client->sockfd, &client->servaddr, sizeof(client->servaddr)) != 0){
        nlog(1, "Failed to connect client side");
        return -1;
    } else {
        nlog(0, "Connected to server side");
    }
}

void quit(net* net){
    close(net->sockfd);
    nlog(0, "Server socket has been closed");
}