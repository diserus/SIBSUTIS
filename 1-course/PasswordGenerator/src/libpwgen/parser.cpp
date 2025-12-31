#include "parser.h"

int parse(
        std::vector<std::string>& flags, int& passwords_len, int& num_passwords)
{
    std::string input;
    std::getline(std::cin, input);

    std::stringstream ss(input);
    std::vector<std::string> tokens;
    std::string token;
    while (ss >> token) {
        tokens.push_back(token);
    }
    if (tokens.size() == 1 && tokens[0] == "pwgen")
        return 0;
    if (tokens[0] != "pwgen") {
        return ERR_NAME;
    }
    for (size_t i = 1; i < tokens.size(); i++) {
        if (tokens[i].length() == 2 && tokens[i].find("-") == 0
            && tokens[i][1] != '-') {
            flags.push_back(tokens[i]);
        } else {
            for (auto symbol : tokens[i]) {
                if (!std::isdigit(symbol)) {
                    return ERR_FLAG;
                }
            }
        }
    }

    if ((tokens.size() - flags.size() - 1) == 2) {
        for (auto symbol : tokens[tokens.size() - 1]) {
            if (!std::isdigit(symbol)) {
                return ERR_NUM;
            }
            num_passwords = std::stoi(tokens[tokens.size() - 1]);
        }
        for (auto symbol : tokens[tokens.size() - 2]) {
            if (!std::isdigit(symbol)) {
                return ERR_LEN;
            }
            passwords_len = std::stoi(tokens[tokens.size() - 2]);
        }
    }

    else if ((tokens.size() - flags.size() - 1) == 1) {
        for (auto symbol : tokens[tokens.size() - 1]) {
            if (std::isdigit(symbol)) {
                passwords_len = std::stoi(tokens[tokens.size() - 1]);
            } else {
                return ERR_NUM;
            }
        }

    } else {
        if (!((tokens.size() - flags.size()) == 1)) {
            return ERR_UNEXP_TOKEN;
        }
    }
    return 0;
}
