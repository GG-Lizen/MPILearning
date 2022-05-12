#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("xxx");
        return 0;
    }
    char* s = argv[1];
    int m, n;
    FILE *infileptr, *outfileptr;
    infileptr = fopen(s, "r");
    // outfileptr = fopen(s, "a");

    // m = 5;
    // n = 5;
    // fwrite(&m, sizeof(int), 1, outfileptr);
    // fwrite(&n, sizeof(int), 1, outfileptr);
    // for (size_t i = 0; i < 5; i++) {
    //     for (size_t j = 0; j < 5; j++) {
    //         int temp = i + j;
    //         fwrite(&temp, sizeof(int), 1, outfileptr);
    //     }
    // }
    if (infileptr == NULL)
        m = 0;
    else {
        fread(&m, sizeof(int), 1, infileptr);
        fread(&n, sizeof(int), 1, infileptr);
        printf("%d %d", m, n);

        for (size_t i = 0; i < 5; i++) {
            for (size_t j = 0; j < 5; j++) {
                int temp;
                fread(&temp, sizeof(int), 1, infileptr);
                printf("%d", temp);
            }
        }
    }

    return 0;
}