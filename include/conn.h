#ifndef CONN_H
#define CONN_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int sockfd, newsockfd;

int initialize(int port, int sockfd, struct sockaddr_in *host_addr, unsigned int host_addrlen);
int acceptConnection(int sockfd, struct sockaddr_in *host_addr, struct sockaddr_in client_addr, unsigned int host_addrlen);
int readRequest(int newsockfd, char *buffer, size_t buffer_size);
int sendResponse(int newsockfd, char *resp);
void closeSocket(int sig);

#endif