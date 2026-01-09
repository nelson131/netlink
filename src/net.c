#include "net.h"
#include <stdio.h>

#define DEFAULT_PORT 8080
#define MAX_CAPACITY 80

int serv_init(net* server, char* ip, char* port){
    memset(&server->servaddr, 0, sizeof(server->servaddr));
    server->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(server->sockfd == -1){
        nlog(1, "Failed to create a socket");
        return -1;
    }

    int p = DEFAULT_PORT;
    if(port){
        p = atoi(port);
    }

    server->servaddr.sin_family = AF_INET;
    server->servaddr.sin_addr.s_addr = INADDR_ANY;
    server->servaddr.sin_port = htons(p);

    if(bind(server->sockfd, (struct sockaddr*) &server->servaddr, sizeof(server->servaddr)) != 0){
        perror("bind");
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

    socklen_t len = sizeof(server->cli);
    server->connfd = accept(server->sockfd, (struct sockaddr*) &server->cli, &len);
    if(server->connfd < 0){
        nlog(1, "Failed to server accept");
        return -1;
    }

    nlog(0, "Client has been connected!");
    return 0;
}

int cli_init(net* client, char* ip, char* port){
    nlog(2, "Trying to connect by: ");
    nlog(2, ip);
    nlog(2, port);

    memset(&client->servaddr, 0, sizeof(client->servaddr));
    client->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(client->sockfd == -1){
        nlog(1, "Failed to create a socket in client side");
        return -1;
    }

    int p = DEFAULT_PORT;
    if(port){
        p = atoi(port);
    }

    client->servaddr.sin_family = AF_INET;
    client->servaddr.sin_port = htons(p);

    int ret = inet_pton(AF_INET, ip, &client->servaddr.sin_addr);
    if(ret == 0){
        nlog(1, "Invalid ip address format");
        return -1;
    } else if(ret < 0){
        perror("inet_pton");
        return -1;
    }

    return 0;
}

int cli_conn(net* client){
    if(connect(client->sockfd, (struct sockaddr*) &client->servaddr, sizeof(client->servaddr)) != 0){
        perror("connect");
        nlog(1, "Failed to connect client side");
        return -1;
    } else {
        nlog(0, "Connected to server side");
    }

    return 0;
}

void quit(net* net){
    if(net->sockfd > 0){
        close(net->sockfd);
        nlog(0, "Server socket has been closed");
    }
    if(net->connfd > 0){
        close(net->connfd);
        nlog(0, "Client socket has been closed");
    }
}

void chat(int socket){
    char buff[MAX_CAPACITY];
    int n;
    while(1){
        bzero(buff, MAX_CAPACITY);
        read(socket, buff, MAX_CAPACITY - 1);
        printf("\n%s", buff);
        bzero(buff, MAX_CAPACITY);
        n = 0;

        while((buff[n++] = getchar()) != '\n');

        write(socket, buff, strlen(buff));

        if(strncmp("exit", buff, 4) == 0){
            nlog(2, "Connection closed.");
            break;
        }
    }
}