#ifndef SERVER_H
#define SERVER_H

#include "../utils.h"
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

struct server {
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
} typedef server;

int init(server* server);
int conn(server* server);

#endif