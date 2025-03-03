#include "global.h"

extern int sockfd, newsockfd;

int initialize(int port, int sockfd, struct sockaddr_in *host_addr, unsigned int host_addrlen, unsigned int sock_option){
    if(sockfd != -1) printf("socket file descriptor: %d\n", sockfd);
    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &sock_option, sizeof(sock_option)) < 0) return 1;

    if(bind(sockfd, (struct sockaddr *)host_addr, (socklen_t)host_addrlen) != 0) return 1;
    printf("socket bound\n");

    if(listen(sockfd, SOMAXCONN) != 0) return 1;
    printf("server listening: %s:%d\n", inet_ntoa(host_addr->sin_addr), port);
    return 0;
}

int acceptConnection(int sockfd, struct sockaddr_in *host_addr, struct sockaddr_in client_addr, unsigned int host_addrlen){
    return accept(sockfd, (struct sockaddr *)host_addr, (socklen_t *)&host_addrlen);
}

int readRequest(int newsockfd, char *buffer, unsigned int buffer_size){
    return read(newsockfd, buffer, buffer_size-1);
}

int sendResponse(int newsockfd, char *headers, char *page){
    int total_length = strlen(headers) + strlen(page);
    char *resp = malloc(total_length + 1);

    strcpy(resp, headers);
    strcat(resp, page);

    return write(newsockfd, resp, total_length);
}

void closeSocket(int sig){
    if(sockfd >= 0) close(sockfd);
    if(newsockfd >= 0) close(newsockfd);
    printf("\nKilling the webserver...\n");
    exit(0);
}
