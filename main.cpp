#include <stdio.h>
#include <stdint.h>
#include "nbo.h"

void printHex(uint32_t num);
int check(int argc);

int main(int argc, char *argv[]) {
    if(check(argc)){
        return 1;
    }

    uint32_t sum = 0;
    bool first = true;

    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "rb");
        if (fp == 0) {
            fprintf(stderr, "Error: cannot open file %s\n", argv[i]);
            return 1;
        }

        uint32_t nv;
        size_t bytesRead = fread(&nv, 1, 4, fp);
        fclose(fp);

        if (bytesRead != 4) {
            fprintf(stderr, "Error: file %s is too small\n", argv[i]);
            return 1;
        }

        uint32_t hv = nboToHbo(nv);

        if (first == 0){
            printf(" + ");
        }
        printHex(hv);

        sum += host_val;
        first = false;
    }

    printf(" = ");
    printNumber(sum);
    printf("\n");

    return 0;
}

void printHex(uint32_t num) {
    // 값이 16비트 이하인 경우 4자리 헥스(앞에 0 채움), 그 이상이면 기본 헥스 출력
    if (num < 0x10000){
        printf("%u(0x%04x)", num, num);
    }
    else{
        printf("%u(0x%x)", num, num);
    }
}

int check(int argc){
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> [<file2>...]\n", argv[0]);
        return 1;
    }
}
