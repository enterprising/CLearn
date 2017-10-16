//
// 多进程版 echo 服务
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
    char receiveBuff[BUFFER_SIZE];
    memset(receiveBuff, 0, sizeof(receiveBuff));
    while (recv(client_sockfd, receiveBuff, sizeof(receiveBuff), 0) > 0) {
        printf("received: %s", receiveBuff);
        send(client_sockfd, receiveBuff, strlen(receiveBuff), 0);
        memset(receiveBuff, 0, sizeof(receiveBuff));
    }
    close(client_sockfd);
}

int main(int argc, char *argv[]) {
    int port = 1234;
    int sockfd, client_sockfd;
    int ret = 0;
    struct sockaddr_in serv_addr;

    if (argv[1] != NULL)
        port = atoi(argv[1]);

    pid_t child_pid;

    printf("starting server..\n");

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket() error!");
        exit(-1);
    }
    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);

    ret = bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    if (ret < 0) {
        perror("bind socket error!");
        exit(-1);
    }

    ret = listen(sockfd, backlog);
    if (ret < 0) {
        perror("listen socket error");
        exit(-1);
    }

    struct sockaddr_in clientAddress; //保存用户Socket信息
    memset(&clientAddress, '0', sizeof(clientAddress));
    socklen_t cli_len;

    cli_len = sizeof(clientAddress);
    while (1) {
        client_sockfd = accept(sockfd, (struct sockaddr *) &clientAddress, &cli_len);

        if (client_sockfd < 0) {
            perror("accept error!");
            exit(-1);
        }

        child_pid = fork();  // fork()出一个子进程
        printf("child_pid = %d\n", child_pid);
        if (child_pid < 0) {
            perror("fork progress error!");
            exit(-1);
        }
        // 这里表示，父进程 继续监听连接。continue后面的由子进程处理
        if (child_pid != 0) {
            close(client_sockfd);
            continue;
        }

        printf("client id:%s, port:%d\n", inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port));
        echo(client_sockfd);
        exit(0);
    }

}
