//
// Created by enterprising on 17/12/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

    char *string;
    int dec = 1, sign;
    int ndig = 100000;

    int n = 7;
//    scanf("%d", &n);

    double result = 1.0 / n;

    string = ecvt(result, ndig, &dec, &sign);

    for (int i = 0; i < strlen(string); ++i) {

        char temp[10000];

        strncpy(temp, string, i + 1);
        temp[i + 1] = '\0';

        char other[10000];
        strncpy(other, string + i + 1, i + 1);
        other[i + 1] = '\0';

        printf("%s\n", temp);

        if (strcmp(temp, other) == 0) {
            printf("%d.%s", 0, temp);
            break;
        }

    }

}