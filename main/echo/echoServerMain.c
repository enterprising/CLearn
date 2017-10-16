//
// 单线程版 echo 服务
// Created by peng.tan on 17/10/15.
//
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024 //缓冲区长度
#define backlog 5  // 排队等待Socket连接的最大数目


/**
 * 读取客户端Socket发来的信息，并处理、最后返回
 * @param client
 */
void echo(int client_sockfd) {
    char senBuff[BUFFER_SIZE];
    char receiveBuff[BUFFER_SIZE];
    memset(senBuff, 0, sizeof(senBuff));
    memset(receiveBuff, 0, sizeof(receiveBuff));
    while (recv(client_sockfd, receiveBuff, sizeof(receiveBuff), 0) > 0) {
        printf("received: %s", receiveBuff);
        strcpy(senBuff, receiveBuff);
        send(client_sockfd, senBuff, strlen(senBuff), 0);
    }
    close(client_sockfd);
}

int main(int argc, char *argv[]) {
    int sockfd = 0;
    int client_sockfd = 0;
    int ref = 0;
    int port = 1234;
    struct sockaddr_in serverAddress;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket() error!");
        exit(-1);
    }

    if (argv[1] != NULL) {
        port = atoi(argv[1]);
    }
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(port);

    ref = bind(sockfd, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
    if (ref < 0) {
        perror("bind() error!");
        exit(-1);
    }
    ref = listen(sockfd, backlog);
    if (ref < 0) {
        perror("listen() error!");
        exit(-1);
    }

    struct sockaddr_in clientAddress;
    memset(&clientAddress, '0', sizeof(clientAddress));
    socklen_t cli_len;
    cli_len = sizeof(clientAddress);
    while (1) {
        client_sockfd = accept(sockfd, (struct sockaddr *) &clientAddress, &cli_len);
        if (client_sockfd < 0) {
            perror("accept() error!");
            exit(-1);
        }
        printf("client id:%s, port:%d\n", inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port));
        echo(client_sockfd);
    }

}