//
// fork系统调用
//

#include <zconf.h>
#include <stdio.h>

static int idata = 111; //允许的数据段大小

int main(int argc, char *argv[]) {
    int istack = 222; //允许的栈帧大小
    pid_t childPid;

    switch (childPid = fork()) {
        case -1:
            perror("error hen use fork");
        case 0:
            idata = idata * 3;
            istack = istack * 3;
            break;
        default:
            sleep(3); //给子进程执行的机会
            break;
    }

    printf("PID=%ld %s idata=%d istack=%d\n", getpid(), childPid == 0 ? "(child)" : "(parent)", idata, istack);

}