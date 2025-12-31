#include "mem.h"
#include "mySimpleComputer.h"

int sc_memoryControllerSet(int address, int value)
{
    return sc_memorySet(address, value);
}
