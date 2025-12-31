#include "mySimpleComputer.h"
#include "register.h"

int sc_validateAllCommands()
{
    int hasInvalidCommand = 0;
    
    // Check all memory cells
    for (int address = 0; address < 128; address++) {
        int value;
        if (sc_memoryGet(address, &value) == 0) {
            int sign, command, operand;
            
            // Decode the command
            if (sc_commandDecode(value, &sign, &command, &operand) == 0) {
                // Check if the command is valid using the same logic as in printCommand
                // A command is invalid if command < 0 || command > 0x4c
                if (command < 0 || command > 0x4c) {
                    // Invalid command found
                    hasInvalidCommand = 1;
                    break;  // We can stop checking once we find one invalid command
                }
            }
        }
    }
    
    // Set or clear the flag based on the validation result
    if (hasInvalidCommand) {
        sc_regSet(REGISTER_INCORRECT_COMMAND, 1);
    } else {
        sc_regSet(REGISTER_INCORRECT_COMMAND, 0);
    }
    
    return 0;
}
