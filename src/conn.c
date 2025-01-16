#include "../include/conn.h"


int initialize(int port, int sockfd, struct sockaddr_in *host_addr){
    if(sockfd != -1) printf("socket file descriptor: %d\n", sockfd);

    if(bind(sockfd, (struct sockaddr *)host_addr, (socklen_t)sizeof(*host_addr)) != 0) return 1;
    printf("socket bound\n");

    if(listen(sockfd, SOMAXCONN) != 0) return 1;
    printf("server listening: %s:%d\n", inet_ntoa(host_addr->sin_addr), port);
}

int acceptConnection(int sockfd, struct sockaddr_in *host_addr, struct sockaddr_in client_addr){
    return accept(sockfd, (struct sockaddr *)host_addr, (socklen_t *)(sizeof(*host_addr)));
}

int readRequest(int newsockfd, char *buffer, size_t buffer_size){
    return read(newsockfd, buffer, buffer_size-1);
}

int sendResponse(int newsockfd, char *resp){
    return write(newsockfd, resp, strlen(resp));
}