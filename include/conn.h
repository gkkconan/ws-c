#ifndef CONN_H
#define CONN_H

int initialize(int port, int sockfd, struct sockaddr_in *host_addr, unsigned int host_addrlen, unsigned int sock_option);
int acceptConnection(int sockfd, struct sockaddr_in *host_addr, struct sockaddr_in client_addr, unsigned int host_addrlen);
int readRequest(int newsockfd, char *buffer, unsigned int buffer_size);
int sendResponse(int newsockfd, char *headers, char *page);
void closeSocket(int sig);

#endif
