#include "Dictionary.h"
#include <iostream>
#include <windows.h>
#include <conio.h>

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    system("chcp 65001");
    
    Dictionary dict;
    try {
        dict.fillDictionary("ENRUS.TXT");
        std::cout << "Словарь загружен. Всего слов: " << dict.getWordCount() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    std::string word;
    
    while (true)
    {
        std::cout << "\nВведите слово для перевода (ничего не вводить для выхода): ";
        std::getline(std::cin, word);
        
        if (word.empty() || word[0] == 27)
            break;
        
        try {
            std::string* translation = dict.translate(word);
            if (translation) {
                std::cout << "Перевод: " << *translation << std::endl;
            }
            else {
                std::cout << "Слово не найдено в словаре" << std::endl;
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Ошибка при переводе: " << e.what() << std::endl;
        }
    }
    
    std::cout << "Программа завершена" << std::endl;
    return 0;
}