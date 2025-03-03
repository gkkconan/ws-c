//  ┏━━━━━━━━━━━━┓   ┏━━━━━━━━━━━━┓   ┏━━━━━━━━━━━━┓   ┏━━━━━━━━━━━━┓   ┏━━━━━━━━━━━━━━┓
//  ┃   SOCKET   ┃ ▶ ┃    BIND    ┃ ▶ ┃   LISTEN   ┃ ▶ ┃   ACCEPT   ┃ ▶ ┃  READ/WRITE  ┃
//  ┗━━━━━━━━━━━━┛   ┗━━━━━━━━━━━━┛   ┗━━━━━━━━━━━━┛   ┗━━━━━━━━━━━━┛   ┗━━━━━━━━━━━━━━┛

#include "global.h"

int sockfd;
int newsockfd;

#define BUFFER_SIZE 1024
#define REUSE_ADDR_OPTION 1

//**************************************************

int main(int argc, char *argv[]){
    int port = (argc > 1) ? atoi(argv[1]) : 8080;
    sockfd = socket(AF_INET, SOCK_STREAM, 0); // socket file descriptor, access point to the socket
    char buffer[BUFFER_SIZE];
    char headers[] = "HTTP/1.0 200 OK\r\n"
                    "Server: webserver-c\r\n"
                    "Content-type: text/html\r\n\r\n";

    // host and client
    struct sockaddr_in client_addr;
    struct sockaddr_in host_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr.s_addr = htonl(INADDR_ANY)
    };
    unsigned int host_addrlen = sizeof(host_addr);
    unsigned int client_addrlen = sizeof(client_addr);



    signal(SIGINT, closeSocket); // handle SIGNINT if the user aborts the ws
    initialize(port, sockfd, &host_addr, host_addrlen, REUSE_ADDR_OPTION);

    while(1){
        memset(&client_addr, 0, sizeof(client_addr));
        memset(buffer, 0, BUFFER_SIZE);

        newsockfd = acceptConnection(sockfd, &host_addr, client_addr, host_addrlen);
        int sockn = getsockname(newsockfd, (struct sockaddr *)&client_addr, (socklen_t *)&client_addrlen);
        if (sockn < 0) continue;

        readRequest(newsockfd, buffer, BUFFER_SIZE);

        // check route
        FILE *page;
        char *absolutePath;
        char *route = buffer;
        char path[100];
        int i = 0;

        while(*route != '\0' && *route != '/'){ route++; }
        while((*route != ' ' && *route != '\0') && i < sizeof(path) - 1){ path[i++] = *route++; }
        path[i] = '\0';

        // retrieve path
        if(strcmp(path, "/") == 0){
            page = fopen("public/index.html", "r");
            if(page == NULL){ printf("Can't retrieve the index page!"); }
        }
        else{
            absolutePath = malloc(strlen("public/") + strlen(path) + strlen(".html") + 1);
            strcpy(absolutePath, "public");
            strcat(absolutePath, path);
            strcat(absolutePath, ".html");
            page = fopen(absolutePath, "r");
            printf("\n[FILE]: %s", absolutePath);
            free(absolutePath);
            if(page == NULL){ page = fopen("public/index.html", "r"); }
        }

        // open file
        fseek(page, 0, SEEK_END);
        long fileSize = ftell(page);
        rewind(page);
        char *file_buffer = malloc(fileSize + 1);
        fread(file_buffer, 1, fileSize, page);
        file_buffer[fileSize] = '\0';
        fclose(page);

        sendResponse(newsockfd, headers, file_buffer);
        
        free(file_buffer);
        close(newsockfd);
    }

    
    return 0;
}
