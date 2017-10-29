//
// Created by enterprising on 17/10/28.
//

#include <printf.h>
#include <stdlib.h>

extern char **environ;

int main(int argc, char *argv[]) {
    char **ep;
    char x = getenv("JAVA_HOME");
    printf("%s", x);
}