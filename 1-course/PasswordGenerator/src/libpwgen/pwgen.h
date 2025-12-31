#include <ctime>
#include <string>
#include <vector>
#define HELP 1
#define GENERATED 2
void CheckingFlags(std::vector<std::string>& flags);
void GeneratePassword(
        std::vector<std::string>& flags,
        int& passwords_len,
        int& num_passwords);
