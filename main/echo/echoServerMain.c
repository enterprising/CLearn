#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024 //缓冲区长度
#define PORT 54329      //端口号
#define MAX_CONN_SIZE 5  //最大连接数

// 服务端代码，实现 echo server。单进程版

/**
 * 创建 Socket，绑定地址三元组，并开始监听
 * @return SocketID
 */
int setupSocket() {
    int socketID;
    struct sockaddr_in serverAddress;

    socketID = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serverAddress, 0, sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(PORT);

    bind(socketID, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
    listen(socketID, MAX_CONN_SIZE);

    return socketID;
}

/**
 * 读取客户端Socket发来的信息，并处理、最后返回
 * @param client
 */
void echo(int socketID_Client) {
    char senBuff[BUFFER_SIZE];
    char receiveBuff[BUFFER_SIZE];
    memset(senBuff, 0, sizeof(senBuff));
    memset(receiveBuff, 0, sizeof(receiveBuff));
    while (recv(socketID_Client, receiveBuff, sizeof(receiveBuff), 0) > 0) {
        printf("received: %s", receiveBuff);
        strcpy(senBuff, receiveBuff);
        send(socketID_Client, senBuff, strlen(senBuff), 0);
    }
    close(socketID_Client);
}

int main(int argc, char *argv[]) {
    int socketID = 0;
    int socketID_Client = 0;

    printf("starting server..\n");

    struct sockaddr_in clientAddress; //保存用户Socket信息
    memset(&clientAddress, '0', sizeof(clientAddress));
    socklen_t cli_len;

    // 启动Socket，并初始化监听
    socketID = setupSocket();

    if (socketID > 0)
        printf("Socket建立成功，正在监听...\n");

    cli_len = sizeof(clientAddress);
    while (1) {
        socketID_Client = accept(socketID, (struct sockaddr *) &clientAddress, &cli_len);
        if (socketID_Client < 0) {
            fprintf(stderr, "ECHOSERV: Error calling accept()\n");
            exit(EXIT_FAILURE);
        }
        printf("client id:%s, port:%d\n", inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port));
        echo(socketID_Client);
    }

}