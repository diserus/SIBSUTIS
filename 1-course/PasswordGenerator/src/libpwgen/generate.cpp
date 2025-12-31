#include "generate.h"
#include "flags.h"
std::string generate_charset(std::vector<std::string>& flags)
{
    std::string charset
            = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    for (std::string flag : flags) {
        if (flag == "-0")
            NoNumerals(charset);
        else if (flag == "-A")
            NoCapitalize(charset);
        else if (flag == "-z")
            includeSpec(charset);
        else if (flag == "-v")
            NoVowels(charset);
        else if (flag == "-B")
            Ambiguous(charset);
    }
    return charset;
}
