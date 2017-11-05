//
// 在父子进程间共享文件偏移量和打开文件状态标志
//
// 这段代码说明了：fork()之后，这些属性将在父子进程共享，该程序使用mkstemp()打开一个临时文件，接着调用fork()创建子进程
// 子进程改变文件偏移量及文件状态标志，最后退出。父进程随即获得文件偏移量和标志，发现发生了变化

#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int fd, flags;
    char template[] = "/tmp/testXXXXXX";

    setbuf(stdout, NULL);                   /* Disable buffering of stdout */

    /* Open a temporary file, set its file offset to some arbitrary value,
       and change the setting of one of the open file status flags. */

    fd = mkstemp(template);
    if (fd == -1)
        perror("mkstemp");

    printf("File offset before fork(): %lld\n",
           (long long) lseek(fd, 0, SEEK_CUR));

    flags = fcntl(fd, F_GETFL);
    if (flags == -1)
        perror("fcntl - F_GETFL");
    printf("O_APPEND flag before fork() is: %s\n",
           (flags & O_APPEND) ? "on" : "off");

    switch (fork()) {
        case -1:
            perror("fork");

        case 0:     /* Child: change file offset and status flags */
            if (lseek(fd, 1000, SEEK_SET) == -1)
                perror("lseek");

            flags = fcntl(fd, F_GETFL);         /* Fetch current flags */
            if (flags == -1)
                perror("fcntl - F_GETFL");
            flags |= O_APPEND;                  /* Turn O_APPEND on */
            if (fcntl(fd, F_SETFL, flags) == -1)
                perror("fcntl - F_SETFL");
            _exit(EXIT_SUCCESS);

        default:    /* Parent: can see file changes made by child */
            if (wait(NULL) == -1)
                perror("wait");                /* Wait for child exit */
            printf("Child has exited\n");

            printf("File offset in parent: %lld\n",
                   (long long) lseek(fd, 0, SEEK_CUR));

            flags = fcntl(fd, F_GETFL);
            if (flags == -1)
                perror("fcntl - F_GETFL");
            printf("O_APPEND flag in parent is: %s\n",
                   (flags & O_APPEND) ? "on" : "off");
            exit(EXIT_SUCCESS);
    }
}