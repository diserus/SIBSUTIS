#include "mySimpleComputer.h"
#include "myTerm.h"
#include <stdio.h>

void printCounters()
{
    int value = 0;
    sc_icounterGet(&value); // Это decimal адрес

    char str_ic[10]; // "IC: +000A"
    char str_t[10];  // "T: 010"
    
    // Calculate T counter (10 to 1 countdown)
    int t_value = 10 - (value % 10);
    if (t_value == 0) t_value = 10;  // Ensure it stays in 10-1 range
    
    snprintf(str_ic, sizeof(str_ic), "IC: +%04X", value); // HEX
    snprintf(str_t, sizeof(str_t), "T: %02d", t_value);      // DEC (countdown from 10 to 1)

    mt_gotoXY(65, 5);
    write(1, str_ic, strlen(str_ic));

    mt_gotoXY(75, 5);
    write(1, str_t, strlen(str_t));
}
