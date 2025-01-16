#include "../include/conn.h"


int initialize(int port, int sockfd, struct sockaddr_in *host_addr, unsigned int host_addrlen){
    if(sockfd != -1) printf("socket file descriptor: %d\n", sockfd);

    if(bind(sockfd, (struct sockaddr *)host_addr, (socklen_t)host_addrlen) != 0) return 1;
    printf("socket bound\n");

    if(listen(sockfd, SOMAXCONN) != 0) return 1;
    printf("server listening: %s:%d\n", inet_ntoa(host_addr->sin_addr), port);
    return 0;
}

int acceptConnection(int sockfd, struct sockaddr_in *host_addr, struct sockaddr_in client_addr, unsigned int host_addrlen){
    return accept(sockfd, (struct sockaddr *)host_addr, (socklen_t *)&host_addrlen);
}

int readRequest(int newsockfd, char *buffer, size_t buffer_size){
    return read(newsockfd, buffer, buffer_size-1);
}

int sendResponse(int newsockfd, char *resp){
    return write(newsockfd, resp, strlen(resp));
}

void closeSocket(int sig){
    if(sockfd >= 0) close(sockfd);
    if(newsockfd >= 0) close(newsockfd);
    printf("\nKilling the webserver...\n");
    exit(0);
}