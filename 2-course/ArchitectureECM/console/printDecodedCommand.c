#include "myTerm.h"
#include "mytype.h"
#include <stdio.h>

void printDecodedCommand(int value)
{
    mt_gotoXY(2, 17);
    printf("dec: ");
    fflush(stdout);
    if (value < 0) {
        mt_gotoXY(6, 17);
        printf("-");
        fflush(stdout);
    }
    char result[19] = {0};
    char bin[16] = {0};
    unsigned int unsigned_val = (unsigned int)value & 0x7FFF;

    for (int i = 0; i < 15; ++i) {
        bin[14 - i] = ((unsigned_val >> i) & 1) + '0';
    }

    result[0] = bin[0];
    result[1] = ' ';
    for (int i = 0; i < 7; i++) {
        result[2 + i] = bin[1 + i];
    }
    result[9] = ' ';
    for (int i = 0; i < 7; i++) {
        result[10 + i] = bin[8 + i];
    }
    result[17] = '\0';
    printf("%0*d | oct: %0*o | hex: %0*X| bin:%s",
           5,
           (value < 0) ? -1 * value : value,
           5,
           value & 0x7FFF,
           4,
           value & 0x7FFF,
           result);
    fflush(stdout);
}
