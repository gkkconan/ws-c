#ifndef CONN_H
#define CONN_H

int initialize(int port, int sockfd, struct sockaddr_in *host_addr, unsigned int host_addrlen, uint sock_option);
int acceptConnection(int sockfd, struct sockaddr_in *host_addr, struct sockaddr_in client_addr, unsigned int host_addrlen);
int readRequest(int newsockfd, char *buffer, size_t buffer_size);
int sendResponse(int newsockfd, char *resp);
void closeSocket(int sig);

#endif
