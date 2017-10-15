//
// 多线程版 echo 服务
// Created by enterprising on 17/10/15.
//

#include <cstdlib>
#include <netinet/in.h>

int main(int argc, char *argv[]) {

    int prot = atoi(argv[1]);
    int socketID;
    struct sockaddr_in servAddr;

    socketID = socket(AF_INET,SOCK_STREAM,0);
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(prot);  //将本地的无符号短整型变为 网络字节序

    //INADDR_ANY就是指定地址为0.0.0.0的地址，这个地址事实上表示不确定地址
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY); //将本地的无符号长整型变为 网络字节序；




}

