//
// 练习 read()、write()、lseek()(改变文件偏移量)的使用
//

#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include <memory.h>
#include "../lib/get_num.h"


int main(int argc, char *argv[]) {
    size_t len;
    off_t offset;
    int fd, ap, j;
    char *buf;
    ssize_t numRead, numWritten;


    // 这是 open 的第二个参数，代表访问模式，有只读、只写、读写三种
    int openFlags = O_RDWR | O_CREAT;
    // 这是 open 的第三个参数，只有当上面是 O_CREATE 的时候才需要加上，代表文件的访问权限
    int filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;  //rw-rw-rw-

    fd = open(argv[1], openFlags, filePerms);
    if (fd == -1) {
        perror("open file error!");
    }

    for (ap = 2; ap < argc; ap++) {
        switch (argv[ap][0]) {
            case 'r':   /* Display bytes at current offset, as text */
            case 'R':   /* Display bytes at current offset, in hex */
                len = getLong(&argv[ap][1], GN_ANY_BASE, argv[ap]);

                buf = malloc(len);
                if (buf == NULL)
                    perror("malloc");

                numRead = read(fd, buf, len);
                if (numRead == -1)
                    perror("read error!");

                if (numRead == 0) {
                    printf("%s: end-of-file\n", argv[ap]);
                } else {
                    printf("%s: ", argv[ap]);
                    for (j = 0; j < numRead; j++) {
                        if (argv[ap][0] == 'r')
                            printf("%c", isprint((unsigned char) buf[j]) ?
                                         buf[j] : '?');
                        else
                            printf("%02x ", (unsigned int) buf[j]);
                    }
                    printf("\n");
                }

                free(buf);
                break;

            case 'w':   /* Write string at current offset */
                numWritten = write(fd, &argv[ap][1], strlen(&argv[ap][1]));
                if (numWritten == -1)
                    perror("write error!");
                printf("%s: wrote %ld bytes\n", argv[ap], (long) numWritten);
                break;

            case 's':   /* Change file offset */
                offset = getLong(&argv[ap][1], GN_ANY_BASE, argv[ap]);
                if (lseek(fd, offset, SEEK_SET) == -1)
                    perror("lseek error!");
                printf("%s: seek succeeded\n", argv[ap]);
                break;
        }
    }

    if (close(fd) == -1)
        perror("close error!");

    exit(EXIT_SUCCESS);

}

