//
// Created by enterprising on 17/12/22.
//

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char str[10000];
    scanf("%s", str);

    int length = strlen(str);


    for (int i = 1; i <= length; ++i) {
        int count = 1;
        while (str[i] == str[i - 1]) {
            count++;
            i++;
        }
        printf("%d%c", count, str[i - 1]);
        count = 0;
    }

}