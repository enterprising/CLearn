//
// vfork()： fork()的一种改进版本
// 主要特点：1. 无需为子进程复制虚拟页或页表，子进程共享父进程的内存，直至其成功执行了 exec()或是调用 _exit()退出
//         2. 在子进程调用 exec()或是调用 _exit()之前，将暂停执行父进程
//

#include <zconf.h>
#include <stdlib.h>
#include <printf.h>

int main(int argc, char *argv[]) {
    int istack = 222;

    switch (vfork()) {
        case -1:
            perror("vfork");

        case 0:             /* Child executes first, in parent's memory space */
            sleep(3);                   /* Even if we sleep for a while,
                                       parent still is not scheduled */
            write(STDOUT_FILENO, "Child executing\n", 16);
            istack *= 3;                /* This change will be seen by parent */
            _exit(EXIT_SUCCESS);

        default:            /* Parent is blocked until child exits */
            write(STDOUT_FILENO, "Parent executing\n", 17);
            printf("istack=%d\n", istack);
            exit(EXIT_SUCCESS);
    }
}