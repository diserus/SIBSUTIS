#include "register.h"

int sc_icounerSet(int value)
{
    if (value < 0 || value >= 128)
        return 0; /* Return success but don't change the value */
    commandCounter.var = value;
    return 0;
}
