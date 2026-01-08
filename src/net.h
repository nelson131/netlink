#ifndef NET_H
#define NET_H

#include "utils.h"
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>

struct net {
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
} typedef net;

int serv_init(net* server, char* ip, char* port);
int serv_conn(net* server);

int cli_init(net* client, char* ip, char* port);
int cli_conn(net* client);

void quit(net* net);

void chat(int socket, size_t* close_it);

#endif