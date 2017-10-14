//
// Created by enterprising on 17/10/14.
//

#include <sys/socket.h>  // socket
#include <sys/types.h>   // socket 类型
#include <arpa/inet.h>  // inet(3) 函数
#include <unistd.h>  // misc. Unix函数
#import "helper.h"
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#define ECHO_PORT   (2007)
#define MAX_LINE    (1000)

// 说明： argc代表参数的个数，也就是 argv[]里面的大小
int main(int argc, char *argv[]) {
    int list_s; // listening socket
    int conn_s; // connection socket
    short int port; //端口号
    struct sockaddr_in servaddr;  //Socket地址结构体
    char buffer[MAX_LINE];  //字符缓冲区
    char *endptr;  //   for strtol

    // 获取端口号，如果没有那就设置默认值
    if (argc == 2) {
        //把参数0所指向的字符串根据参数2（就是进制）转换为一个长整数。0 代表十进制
        port = (short) strtol(argv[1], &endptr, 0);   // 这里的第二个参数，可以理解成 argv[1]经过数字过滤，还剩下的东西
        if (*endptr) { //如果还剩东西，就表示出了数字还有其他值。
            fprintf(stderr, "ECHOSERVER: Invalid port number.\n");
            exit(EXIT_FAILURE);
        }
    } else if (argc < 2) {
        port = ECHO_PORT;
    } else {
        fprintf(stderr, "ECHOSERVER: Invalid arguments. \n");
    }

    // 创建 listening socket
    if ((list_s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        fprintf(stderr, "ECHOSERV: Error creating listening socket.\n");
        exit(EXIT_FAILURE);
    }

    /*  Set all bytes in socket address structure to
        zero, and fill in the relevant data members   */
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);


    // 绑定我们的 Socket 地址 到listening socket，然后调用listen()
    if (bind(list_s, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
        fprintf(stderr, "ECHOSERV: Error calling bind()\n");
        exit(EXIT_FAILURE);
    }
    if (listen(list_s, LISTENQ) < 0) {
        fprintf(stderr, "ECHOSERV: Error calling listen()\n");
        exit(EXIT_FAILURE);
    }

    // 准备工作完成，现在开始监听
    while (1) {
        fprintf(stderr, "正在监听Socket连接..\n");
        // 等待一个连接，然后Accept它
        if ((conn_s = accept(list_s, NULL, NULL)) < 0) {
            fprintf(stderr, "ECHOSERV: Error calling accept()\n");
            exit(EXIT_FAILURE);
        }
        fprintf(stderr, "听到了\n");
        // 从connected socket里面取出一个输入行，然后再简单的写回到同一个socket里面
        Readline(conn_s, buffer, MAX_LINE - 1);
        Writeline(conn_s, buffer, strlen(buffer));

        // 关闭这个 socket 连接
//        if (close(conn_s) < 0) {
//            fprintf(stderr, "ECHOSERV: Error calling close()\n");
//            exit(EXIT_FAILURE);
//        }
    }
}