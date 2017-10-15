//
// Created by enterprising on 17/10/15.
// 回顾 echoServer
//

#include <stdlib.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <strings.h>
#include <zconf.h>


int main(int argc, char *argv[]) {

    int port = atoi(argv[1]);

    int socketId, clientSocktId;
    pid_t childId;
    char buf[1024];

    struct sockaddr_in sockAddr;

    socketId = socket(AF_INET, SOCK_STREAM, 0);
    if (socketId < 0) {
        perror("socket()");
        exit(-1);
    }

    // 帮地址三元组赋值
    sockAddr.sin_port = htons(port);
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    int b = bind(socketId, (struct sockaddr *) &sockAddr, sizeof(sockAddr));
    if (b < 0) {
        perror("bind()");
        exit(-1);
    }

    int l = listen(socketId, 6);
    if (l < 0) {
        perror("listen()");
        exit(-1);
    }

    while (1) {
        clientSocktId = accept(socketId, NULL, NULL);
        if (clientSocktId != 0) {
            //创建子进程来处理这个连接上的信息
            childId = fork();
        }
        if (childId != 0) { //对于父进程来说，这个值是0.
            close(clientSocktId); //关闭父进程上的这个客户端Socket，因为已经交给子进程去处理了
            continue;
        }
        memset(buf, 0, sizeof(buf));
        while (recv(clientSocktId, buf, sizeof(buf), 0) > 0) {
            printf("receive: %s", buf);
            send(clientSocktId, buf, strlen(buf), 0);
            memset(buf, 0, sizeof(buf));
        }
        close(clientSocktId);
        exit(0);
    }

}

