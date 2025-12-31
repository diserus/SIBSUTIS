#include "../src/libpwgen/generate.h"
#include "../src/libpwgen/parser.h"
#include "../src/libpwgen/pwgen.h"
#include "../thirdparty/ctest.h"
#include <stdio.h>

CTEST(parser, correct_parse1)
{
    std::string input = "pwgen -f 1 5";

    std::stringstream ss;
    std::streambuf* orig = std::cin.rdbuf();
    std::cin.rdbuf(ss.rdbuf());
    ss.str(input);

    std::vector<std::string> flags;
    int passwords_len = DEFAULT_PW_LEN;
    int num_passwords = DEFAUL_PW_NUM;
    parse(flags, passwords_len, num_passwords);

    std::cin.rdbuf(orig);

    int exp_len = 1;
    int exp_num = 5;
    std::string exp_flag = "-f";
    ASSERT_EQUAL(exp_len, passwords_len);
    ASSERT_EQUAL(exp_num, num_passwords);
    for (auto flag : flags)
        ASSERT_STR(exp_flag.c_str(), flag.c_str());
}

CTEST(parser, correct_parse2)
{
    std::string input = "pwgen";

    std::stringstream ss;
    std::streambuf* orig = std::cin.rdbuf();
    std::cin.rdbuf(ss.rdbuf());
    ss.str(input);

    std::vector<std::string> flags;
    int passwords_len = DEFAULT_PW_LEN;
    int num_passwords = DEFAUL_PW_NUM;
    parse(flags, passwords_len, num_passwords);

    std::cin.rdbuf(orig);

    int exp_len = DEFAULT_PW_LEN;
    int exp_num = DEFAUL_PW_NUM;
    std::string exp_flag = "";
    ASSERT_EQUAL(exp_len, passwords_len);
    ASSERT_EQUAL(exp_num, num_passwords);
    for (auto flag : flags)
        ASSERT_STR(exp_flag.c_str(), flag.c_str());
}

CTEST(parser, correct_parse3)
{
    std::string input = "pwgen -f";

    std::stringstream ss;
    std::streambuf* orig = std::cin.rdbuf();
    std::cin.rdbuf(ss.rdbuf());
    ss.str(input);

    std::vector<std::string> flags;
    int passwords_len = DEFAULT_PW_LEN;
    int num_passwords = DEFAUL_PW_NUM;
    parse(flags, passwords_len, num_passwords);

    std::cin.rdbuf(orig);

    int exp_len = DEFAULT_PW_LEN;
    int exp_num = DEFAUL_PW_NUM;
    std::string exp_flag = "-f";
    ASSERT_EQUAL(exp_len, passwords_len);
    ASSERT_EQUAL(exp_num, num_passwords);
    for (auto flag : flags)
        ASSERT_STR(exp_flag.c_str(), flag.c_str());
}

CTEST(parser, incorrect_parse1)
{
    std::string input = "pwg -f";

    std::stringstream ss;
    std::streambuf* orig = std::cin.rdbuf();
    std::cin.rdbuf(ss.rdbuf());
    ss.str(input);

    std::vector<std::string> flags;
    int passwords_len = DEFAULT_PW_LEN;
    int num_passwords = DEFAUL_PW_NUM;

    int exp = ERR_NAME;
    int res = parse(flags, passwords_len, num_passwords);

    std::cin.rdbuf(orig);
    ASSERT_EQUAL(exp, res);
}

CTEST(parser, incorrect_parse2)
{
    std::string input = "pwgen --";

    std::stringstream ss;
    std::streambuf* orig = std::cin.rdbuf();
    std::cin.rdbuf(ss.rdbuf());
    ss.str(input);

    std::vector<std::string> flags;
    int passwords_len = DEFAULT_PW_LEN;
    int num_passwords = DEFAUL_PW_NUM;

    int exp = ERR_FLAG;
    int res = parse(flags, passwords_len, num_passwords);

    std::cin.rdbuf(orig);
    ASSERT_EQUAL(exp, res);
}

CTEST(parser, incorrect_parse3)
{
    std::string input = "pwgen -f 1 2 1";

    std::stringstream ss;
    std::streambuf* orig = std::cin.rdbuf();
    std::cin.rdbuf(ss.rdbuf());
    ss.str(input);

    std::vector<std::string> flags;
    int passwords_len = DEFAULT_PW_LEN;
    int num_passwords = DEFAUL_PW_NUM;

    int exp = ERR_UNEXP_TOKEN;
    int res = parse(flags, passwords_len, num_passwords);

    std::cin.rdbuf(orig);
    ASSERT_EQUAL(exp, res);
}

CTEST(generate, generate_charset1)
{
    std::vector<std::string> flags = {"-0", "-A"};
    std::string exp = "abcdefghijklmnopqrstuvwxyz";
    std::string res = generate_charset(flags);
    ASSERT_STR(exp.c_str(), res.c_str());
}

CTEST(generate, generate_charset2)
{
    std::vector<std::string> flags;
    std::string exp
            = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    std::string res = generate_charset(flags);
    ASSERT_STR(exp.c_str(), res.c_str());
}

CTEST(generate, generate_charset3)
{
    std::vector<std::string> flags = {"-z", "-B"};
    std::string exp = "ACEFHJKLMNPRTUVWXYabcdefghijkmnopqrstuvwxyz3479!@#$%&*?";
    std::string res = generate_charset(flags);
    ASSERT_STR(exp.c_str(), res.c_str());
}

CTEST(generate, generate_charset4)
{
    std::vector<std::string> flags = {"-0", "-A", "-z", "-B", "-v"};
    std::string exp = "bcdfghjkmnpqrstvwxz!@#$%&*?";
    std::string res = generate_charset(flags);
    ASSERT_STR(exp.c_str(), res.c_str());
}

CTEST(generate, generate_passwords_default)
{
    std::vector<std::string> flags;
    int passwords_len = 10;
    int num_passwords = 5;

    std::ostringstream output;
    std::streambuf* old_cout_buf = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    GeneratePassword(flags, passwords_len, num_passwords);

    std::cout.rdbuf(old_cout_buf);

    std::string generated_output = output.str();
    std::istringstream iss(generated_output);
    std::string password;
    int count = 0;
    while (iss >> password) {
        ASSERT_EQUAL(passwords_len, password.size());
        count++;
    }
    ASSERT_EQUAL(num_passwords, count);
}

CTEST(generate, generate_passwords_with_flag_z)
{
    std::vector<std::string> flags = {"-z"};
    int passwords_len = 10;
    int num_passwords = 5;

    std::ostringstream output;
    std::streambuf* old_cout_buf = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    GeneratePassword(flags, passwords_len, num_passwords);

    std::cout.rdbuf(old_cout_buf);

    std::string generated_output = output.str();
    std::istringstream iss(generated_output);
    std::string password;
    int count = 0;
    std::string special_characters = "!@#$%^&";
    while (iss >> password) {
        ASSERT_EQUAL(passwords_len, password.size());
        bool contains_special = false;
        for (char c : password) {
            if (special_characters.find(c) != std::string::npos) {
                contains_special = true;
                break;
            }
        }
        ASSERT_TRUE(contains_special);
        count++;
    }
    ASSERT_EQUAL(num_passwords, count);
}

CTEST(generate, generate_passwords_with_flag_e)
{
    std::vector<std::string> flags = {"-e"};
    int passwords_len = 10;
    int num_passwords = 5;

    std::ostringstream output;
    std::streambuf* old_cout_buf = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    GeneratePassword(flags, passwords_len, num_passwords);

    std::cout.rdbuf(old_cout_buf);

    std::string generated_output = output.str();
    std::istringstream iss(generated_output);
    std::string password;
    int count = 0;
    while (iss >> password) {
        ASSERT_EQUAL(passwords_len, password.size());
        count++;
    }
    ASSERT_EQUAL(num_passwords, count);

    std::string::size_type pos = generated_output.find("\n");
    ASSERT_TRUE(pos != std::string::npos);
}

CTEST(flags, help_flag)
{
    std::vector<std::string> flags = {"-h", "-v"};
    int len = DEFAULT_PW_LEN;
    int num = DEFAUL_PW_NUM;
    std::string expected_output
            = "-0, does not include numbers in the generated passwords.\n"
              "-A does not include capital letters in the password.\n"
              "-z, enables special. characters in password generation\n"
              "-v does not include vowels in the password.\n"
              "-B, do not use characters that the user might confuse when "
              "typing, such as 'l' and '1' or '0' or 'O'.\n"
              "-e prints the generated passwords, one per line.\n"
              "-h, displays information for review.\n";

    std::ostringstream output;
    std::streambuf* old_cout_buf = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    GeneratePassword(flags, len, num);

    std::cout.rdbuf(old_cout_buf);
    ASSERT_STR(expected_output.c_str(), output.str().c_str());
}