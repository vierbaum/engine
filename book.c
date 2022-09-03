#include "book.h"

char* enc256(int num) {
    char* b256 = (char*) malloc(5 * sizeof(char));
    printf("%d\n", num);
    b256[4] = '\0';
    b256[3] = num / 2097152;
    num -= b256[3] * 2097152;
    b256[2] = num / 16384;
    num -= b256[2] * 16384;
    b256[1] = num / 128;
    num -= b256[1] * 128;
    b256[0] = num;
    return b256;
}

int readMove(Board*);

void writeToBook(int* moves, char* name, int prio, int length) {
    FILE* fp;
    fp = fopen(BOOKFILE, "a");
    fprintf(fp, "%s: %c\n", name, prio);
    for(int i = 0; i < length; i++)
        fprintf(fp, "%s", enc256(*(moves + i)));
    fprintf(fp, "\n");
    //char* b256 = enc256(int num)
}
