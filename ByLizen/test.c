
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ONE_KB 1024
#define ONE_MB 1024 * 1024
int buffer[ONE_MB];

int fwrite_MB_INT(const char* fileName, int size) {
    if (size > 1024) {
        fprintf(stderr, "too big /n");
        exit(EXIT_FAILURE);
    }
    FILE* fs;

    if ((fs = fopen(fileName, "w")) == NULL) {
        fprintf(stderr, "Cant't open data /n");
        exit(EXIT_FAILURE);
    }
    fclose(fs);

    if ((fs = fopen(fileName, "a+")) == NULL) {
        fprintf(stderr, "Cant't open data /n");
        exit(EXIT_FAILURE);
    }

    int i = 0;

    int sum_num = size * (ONE_MB / 4);
    fwrite(&sum_num, sizeof(int), 1, fs);  //写入元素个数

    srand((unsigned)time(NULL));

    while (i < sum_num) {
        int j = 0;
        for (; j < ONE_MB && j < sum_num; j++, i++) {
            buffer[j] = rand();
            // buffer[j] = i;
        }

        fwrite(buffer, sizeof(int), j, fs);
    }
    // i = 0;
    // fseek(fa, 0, SEEK_SET);
    // while (!feof(fa)) {
    //     printf("\n%d ", i);
    //     fread(buffer, sizeof(int), 1024, fa);
    //     for (int j = 0; j < 1024; j++) {
    //         printf("%d ", buffer[j]);
    //     }
    //     i++;
    // }
    return 0;
}
int main(int argc, char* argv[]) {
    fwrite_MB_INT("data_1GB", 1024);
    return 0;
}