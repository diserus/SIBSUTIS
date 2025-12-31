#include "pwgen.h"
#include "flags.h"
#include "generate.h"

void GeneratePassword(
        std::vector<std::string>& flags, int& passwords_len, int& num_passwords)
{
    bool flag_e = false;
    bool flag_z = false;
    std::string special_characters;

    std::vector<std::string> Flags = {"-0", "-A", "-z", "-v", "-B", "-e"};
    for (std::string flag : flags) {
        int count = 0;
        for (std::string Flag : Flags) {
            if (flag == Flag)
                count++;
        }
        if (count == 0) {
            PrintHelp();
            return;
        }
    }
    
    for (std::string flag : flags) {
        if (flag == "-e") {
            flag_e = true;
        } else if (flag == "-z") {
            flag_z = true;
            special_characters = "!@#$%^&";
        }
    }

    std::string charset = generate_charset(flags);
    srand(time(0));
    for (int i = 0; i < num_passwords; i++) {
        std::string password = "";

        for (int j = 0; j < passwords_len; j++) {
            char letter = charset[rand() % charset.size()];
            password += letter;
        }

        while (flag_z
               && password.find_first_of(special_characters)
                       == std::string::npos) {
            password.clear();
            for (int j = 0; j < passwords_len; j++) {
                char letter = charset[rand() % charset.size()];
                password += letter;
            }
        }

        std::cout << password << " ";

        if (flag_e) {
            PrintEnter();
        } else
            PrintDef(i);
    }
}
