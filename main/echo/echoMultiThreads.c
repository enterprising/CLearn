//
// 多线程版 echo 服务
// Created by peng.tan on 17/10/15.
//
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

void *echo(void *argv) {
    //获取传进来的参数
    int *clientID_Temp = (int *) argv;
    int clientID = *clientID_Temp;
    char buf[1024];
    bzero(buf, 1024);
    while (recv(clientID, buf, sizeof(buf), 0) > 0) {
        printf("receive: %s", buf);
        send(clientID, buf, strlen(buf), 0);
        bzero(buf, 1024);
    }
    close(clientID);
    return NULL;
}

int main(int argc, char *argv[]) {

    int prot = atoi(argv[1]);
    int socketID;
    struct sockaddr_in servAddr;

    socketID = socket(AF_INET, SOCK_STREAM, 0);
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(prot);  //将本地的无符号短整型变为 网络字节序

    //INADDR_ANY就是指定地址为0.0.0.0的地址，这个地址事实上表示不确定地址
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY); //将本地的无符号长整型变为 网络字节序；

    bind(socketID, (struct sockaddr *) &servAddr, sizeof(servAddr));
    listen(socketID, 10);

    while (1) {
        int clientID = accept(socketID, NULL, NULL);
        pthread_t clientThread;
        pthread_create(&clientThread, NULL, &echo, &clientID);
    }
}