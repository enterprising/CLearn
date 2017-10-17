
#include <stdlib.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <strings.h>
#include <pthread.h>
#include <zconf.h>

#define MAXLINE 100
#define LISTENQ 10
#define SERV_PORT 1234

void *str_echo(void *argv) {
    int *pcommu = (int *) argv;
    int client_sockfd = *pcommu;

    char buf[MAXLINE];

    while (recv(client_sockfd, buf, MAXLINE, 0) > 0) {
        printf("receive:%s", buf);
        send(client_sockfd, buf, strlen(buf), 0);
    }
    close(client_sockfd);
    return NULL;
}

int main() {
    int socktID;
    struct sockaddr_in servaddr;

    socktID = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    bind(socktID, (struct sockaddr *) &servaddr, sizeof(servaddr));

    listen(socktID, LISTENQ);

    while (1) {
        int client_sockfd = accept(socktID, NULL, NULL);
        pthread_t communication; //通信线程
        pthread_create(&communication, NULL, &str_echo, &client_sockfd);
    }

}