#include "../libpwgen/flags.h"
#include "../libpwgen/parser.h"
#include "../libpwgen/pwgen.h"
int main()
{
    std::vector<std::string> flags;
    int passwords_len = DEFAULT_PW_LEN;
    int num_passwords = DEFAUL_PW_NUM;
    switch (parse(flags, passwords_len, num_passwords)) {
    case ERR_NAME:
        std::cout << "Error: expected 'pwgen'\n";
        exit(EXIT_FAILURE);
        break;
    case ERR_FLAG:
        std::cout << "Error: invalid flag\n";
        exit(EXIT_FAILURE);
        break;
    case ERR_LEN:
        std::cout << "Error: invalid length of passwords\n";
        exit(EXIT_FAILURE);
        break;
    case ERR_NUM:
        std::cout << "Error: invalid number of passwords\n";
        exit(EXIT_FAILURE);
        break;
    case ERR_UNEXP_TOKEN:
        std::cout << "Error: unexpected token after <num_password>\n";
        exit(EXIT_FAILURE);
        break;
    default:
        break;
    }
    GeneratePassword(flags, passwords_len, num_passwords);
    return 0;
}
