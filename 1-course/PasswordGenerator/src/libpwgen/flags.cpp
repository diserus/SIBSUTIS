#include "flags.h"

void NoNumerals(std::string& chars)
{
    std::string numerals = "0123456789";
    for (size_t i = 0; i < chars.size(); i++) {
        for (auto j : numerals) {
            if (chars[i] == j)
                chars.erase(i, 1);
        }
    }
}

// -A
void NoCapitalize(std::string& chars)
{
    std::string capitalize = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (size_t i = 0; i < chars.size(); i++) {
        for (auto j : capitalize) {
            if (chars[i] == j)
                chars.erase(i, 1);
        }
    }
}

// -z
void includeSpec(std::string& chars)
{
    chars += "!@#$%&*?";
}

// -B
void Ambiguous(std::string& chars)
{
    std::string ambiguous = "BDGIOQSZl012568";
    for (size_t i = 0; i < chars.size(); i++) {
        for (auto j : ambiguous) {
            if (chars[i] == j)
                chars.erase(i, 1);
        }
    }
}
void NoVowels(std::string& chars)
{
    std::string vowels = "aeiouyAEIOUY";
    for (size_t i = 0; i < chars.size(); i++) {
        for (auto j : vowels) {
            if (chars[i] == j)
                chars.erase(i, 1);
        }
    }
}
// -e
void PrintEnter()
{
    std::cout << "\n";
}

// -h
void PrintHelp()
{
    std::cout
            << "-0, does not include numbers in the generated passwords.\n-A "
               "does not include capital letters in the password.\n-z, enables "
               "special. characters in password generation\n-v does not "
               "include vowels in the password.\n-B, do not use characters "
               "that the user might confuse when typing, such as 'l' and '1' "
               "or '0' or 'O'.\n-e prints the generated passwords, one per "
               "line.\n-h, displays information for review.\n";
}

// По дефолту
void PrintDef(int& i)
{
    int passwords_per_row = 8;
    int rows = 20;
    if ((i + 1) % passwords_per_row == 0) {
        std::cout << std::endl;
        if ((i + 1) % (passwords_per_row * rows) == 0) {
            std::cout << std::endl;
        }
    }
}
