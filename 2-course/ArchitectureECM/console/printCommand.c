#include "console.h"
#include "mySimpleComputer.h"
#include <stdio.h>
#include <unistd.h>
void printCommand()
{
    mt_gotoXY(91, 5);
    int value = 0;
    int sign = 0;
    int command = 0;
    int operand = 0;
    char tmp[13] = "            "; // Инициализируем пробелами

    // Get the current instruction counter value
    sc_icounterGet(&value);
    
    // Get the command from memory at the current instruction counter position
    sc_memoryControllerGet(value, &value);
    
    // Decode the command
    sc_commandDecode(value, &sign, &command, &operand);
    if (command < 0 || command > 0x4c)
    {
        snprintf(
            tmp,
            sizeof(tmp),
            "! %c %.2x : %.2x",
            (sign == 1) ? '-' : '+',
            command,
            operand);
    }
    else
    {
        snprintf(
            tmp,
            sizeof(tmp),
            "  %c %.2x : %.2x",
            (sign == 1) ? '-' : '+',
            command,
            operand);
    }
    printf("%s", tmp);
    fflush(stdout);
}
// void printCommand()
// {
//     int value = 0;
//     int sign = 0;
//     int command = 0;
//     int operand = 0;
//     char tmp[13] = "            "; // Инициализируем пробелами

//     sc_icounterGet(&value);
//     sc_commandDecode(value, &sign, &command, &operand);

//     sc_memoryGet(operand, &value);
//     sc_commandDecode(value, &sign, &command, &operand);

//     if (command < 0 || command > 0x4c) {
//         snprintf(
//                 tmp,
//                 sizeof(tmp),
//                 "! %c %.2x : %.2x",
//                 (sign == 1) ? '+' : '-',
//                 command,
//                 operand);
//     } else {
//         snprintf(
//                 tmp,
//                 sizeof(tmp),
//                 "  %c %.2x : %.2x",
//                 (sign == 1) ? '-' : '+',
//                 command,
//                 operand);
//     }

//     mt_gotoXY(91, 5);
//     write(1, tmp, 12);
// }
