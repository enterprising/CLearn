//
// 系统调用 之 文件I/O操作
//

#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {

    int inputFd, outputFd, openFlags;
    mode_t filePerms;
    ssize_t numRead, numWrite;  //read和write这两个系统调用返回的是读/写的字节数
    char buf[BUF_SIZE];

    // 文件地址
    char *pathname = "/Users/enterprising/Desktop/a.txt";
    char *pathname_write = "/Users/enterprising/Desktop/b.txt";

    inputFd = open(pathname, O_RDONLY);
    if (inputFd == -1) {
        perror("open files error!");
        exit(-1);
    }

    // 这是 open 的第二个参数，代表访问模式，有只读、只写、读写三种
    openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    // 这是 open 的第三个参数，只有当上面是 O_CREATE 的时候才需要加上，代表文件的访问权限
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;  //rw-rw-rw-

    outputFd = open(pathname_write, openFlags, filePerms);
    if (outputFd == -1) {
        perror("open files error!");
        exit(-1);
    }

    // 将上面读到的内容，写到下面那个文件里
    numRead = read(inputFd, buf, BUF_SIZE);
    if (numRead == -1) {
        perror("read files error!");
        exit(-1);
    }
    numWrite = write(outputFd, buf, numRead);

    if (numWrite != numRead) {
        perror("can not write whole buffer.");
        exit(-1);
    }
    if (numWrite == -1) {
        perror("write files error!");
        exit(-1);
    }

    //最后需要关闭两个文件
    if (close(inputFd) == -1) {
        perror("close input error!");
        exit(-1);
    }
    if (close(outputFd) == -1) {
        perror("close output error!");
        exit(-1);
    }
}

