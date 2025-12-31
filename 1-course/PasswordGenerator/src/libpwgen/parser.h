#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#define DEFAULT_PW_LEN 8
#define DEFAUL_PW_NUM 160
#define ERR_NAME 1
#define ERR_FLAG 2
#define ERR_LEN 3
#define ERR_NUM 4
#define ERR_UNEXP_TOKEN 5
int parse(
        std::vector<std::string>& flags,
        int& passwords_len,
        int& num_passwords);
