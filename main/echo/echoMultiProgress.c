#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024 //缓冲区长度
#define PORT 54321      //端口号
#define MAX_CONN_SIZE 5  //最大连接数

// 服务端代码，实现 echo server。单进程版

/**
 * 读取客户端Socket发来的信息，并处理、最后返回
 * @param client
 */
void echo(int socketID_Client) {
    char receiveBuff[BUFFER_SIZE];
    memset(receiveBuff, 0, sizeof(receiveBuff));
    while (recv(socketID_Client, receiveBuff, sizeof(receiveBuff), 0) > 0) {
        printf("received: %s", receiveBuff);
        send(socketID_Client, receiveBuff, strlen(receiveBuff), 0);
        memset(receiveBuff, 0, sizeof(receiveBuff));
    }
    close(socketID_Client);
}

int main() {
    int socketID, clientSocketID;
    struct sockaddr_in socketAddr;

    pid_t child_pid;

    printf("starting server..\n");

    socketID = socket(AF_INET, SOCK_STREAM, 0);
    memset(&socketAddr, 0, sizeof(socketAddr));

    socketAddr.sin_family = AF_INET;
    socketAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    socketAddr.sin_port = htons(PORT);

    bind(socketID, (struct sockaddr *) &socketAddr, sizeof(socketAddr));
    listen(socketID, MAX_CONN_SIZE);
    struct sockaddr_in clientAddress; //保存用户Socket信息
    memset(&clientAddress, '0', sizeof(clientAddress));
    socklen_t cli_len;

    if (socketID > 0)
        printf("Socket建立成功，正在监听...\n");

    cli_len = sizeof(clientAddress);
    while (1) {
        clientSocketID = accept(socketID, (struct sockaddr *) &clientAddress, &cli_len);

        child_pid = fork();  // fork()出一个子进程
        printf("child_pid = %d\n", child_pid);
        if (child_pid < 0) {
            perror("fork() 出问题了！");
            exit(-1);
        }
        // 这里表示，父进程 继续监听连接。continue后面的由子进程处理
        if (child_pid != 0) {
            close(clientSocketID);
            continue;
        }
        if (clientSocketID < 0) {
            fprintf(stderr, "ECHOSERV: Error calling accept()\n");
            exit(EXIT_FAILURE);
        }
        printf("client id:%s, port:%d\n", inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port));
        echo(clientSocketID);
        exit(0);
    }

}
