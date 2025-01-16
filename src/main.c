//  ┏━━━━━━━━━━━━┓   ┏━━━━━━━━━━━━┓   ┏━━━━━━━━━━━━┓   ┏━━━━━━━━━━━━┓   ┏━━━━━━━━━━━━━━┓
//  ┃   SOCKET   ┃ ▶ ┃    BIND    ┃ ▶ ┃   LISTEN   ┃ ▶ ┃   ACCEPT   ┃ ▶ ┃  READ/WRITE  ┃
//  ┗━━━━━━━━━━━━┛   ┗━━━━━━━━━━━━┛   ┗━━━━━━━━━━━━┛   ┗━━━━━━━━━━━━┛   ┗━━━━━━━━━━━━━━┛

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../include/conn.h"


#define BUFFER_SIZE 1024

//**************************************************

int main(int argc, char *argv[]){
    int port = (argc > 1) ? atoi(argv[1]) : 8080;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0); // socket file descriptor, access point to the socket
    char buffer[BUFFER_SIZE];
    char resp[] = "HTTP/1.0 200 OK\r\n"
                    "Server: webserver-c\r\n"
                    "Content-type: text/html\r\n\r\n"
                    "<html> Hello world! </html>\r\n";
    
    // host and client
    struct sockaddr_in client_addr;
    struct sockaddr_in host_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr.s_addr = htonl(INADDR_ANY)
    };
    unsigned int host_addrlen = sizeof(host_addr);
    unsigned int client_addrlen = sizeof(client_addr);

    signal(SIGINT, closeSocket); // handle SIGNINT
    initialize(port, sockfd, &host_addr, host_addrlen);

    while(1){
        memset(&client_addr, 0, sizeof(client_addr));
        memset(buffer, 0, BUFFER_SIZE);
        
        int newsockfd = acceptConnection(sockfd, &host_addr, client_addr, host_addrlen);
        int sockn = getsockname(newsockfd, (struct sockaddr *)&client_addr, (socklen_t *)&client_addrlen);
        if (sockn < 0) continue;

        readRequest(newsockfd, buffer, BUFFER_SIZE);
        sendResponse(newsockfd, resp);
        close(newsockfd);
    }


    return 0;
}