#include "mem.h"
#include "mySimpleComputer.h"

int sc_memoryControllerGet(int address, int *value)
{
    return sc_memoryGet(address, value);
}
