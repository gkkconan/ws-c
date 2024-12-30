/* 
┏━━━━━━━━━━━━┓   ┏━━━━━━━━━━━━┓   ┏━━━━━━━━━━━━┓   ┏━━━━━━━━━━━━┓   ┏━━━━━━━━━━━━━━┓
┃   SOCKET   ┃ ▶ ┃    BIND    ┃ ▶ ┃   LISTEN   ┃ ▶ ┃   ACCEPT   ┃ ▶ ┃  READ/WRITE  ┃
┗━━━━━━━━━━━━┛   ┗━━━━━━━━━━━━┛   ┗━━━━━━━━━━━━┛   ┗━━━━━━━━━━━━┛   ┗━━━━━━━━━━━━━━┛
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

//**************************************************

#define BUFFER_SIZE 1024


int acceptConnection(int sockfd, struct sockaddr_in *host_addr, socklen_t *host_addrlen, struct sockaddr_in client_addr);
int readRequest(int newsockfd, char *buffer);
int sendResponse(int newsockfd, char *resp);

//**************************************************


int main(int argc, char *argv[]){
    int port = (argc > 1) ? atoi(argv[1]) : 8080;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0); // socket file descriptor, access point to the socket
    char buffer[BUFFER_SIZE];
    char resp[] = "HTTP/1.0 200 OK\r\n"
                  "Server: webserver-c\r\n"
                  "Content-type: text/html\r\n\r\n"
                  "<html> Hello world! </html>\r\n";
    
    // host
    struct sockaddr_in host_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr.s_addr = htonl(INADDR_ANY)
    };
    int host_addrlen = sizeof(host_addr);

    // client
    struct sockaddr_in client_addr;
    int client_addrlen = sizeof(client_addr);


    if(sockfd == -1) return 1;
    else{printf("socket file descriptor: %d\n", sockfd);}

    if(bind(sockfd, (struct sockaddr *)&host_addr, host_addrlen) != 0) return 1;
    printf("socket bound\n");


    if(listen(sockfd, SOMAXCONN) != 0) return 1;
    printf("server listening: %s:%d\n", inet_ntoa(host_addr.sin_addr), port);

    while(1){
        int newsockfd = acceptConnection(sockfd, &host_addr, &host_addrlen, client_addr);

        int sockn = getsockname(newsockfd, (struct sockaddr *)&client_addr, (socklen_t *)&client_addrlen);
        if (sockn < 0) continue;

        readRequest(newsockfd, buffer);
        sendResponse(newsockfd, resp);

        close(newsockfd);
    }


    return 0;
}


//**************************************************


int acceptConnection(int sockfd, struct sockaddr_in *host_addr, socklen_t *host_addrlen, struct sockaddr_in client_addr){
    int newsockfd = accept(sockfd, (struct sockaddr *)host_addr, host_addrlen);
    if(newsockfd < 0) return -1;
    printf("request accepted from: %s:%u\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    return newsockfd;
}

int readRequest(int newsockfd, char *buffer){
    int valread = read(newsockfd, buffer, BUFFER_SIZE);
    if(valread < 0) return -1;
    return valread;
}

int sendResponse(int newsockfd, char *resp){
    int valwrite = write(newsockfd, resp, strlen(resp));
    if(valwrite < 0) return -1;
    return valwrite;
}
