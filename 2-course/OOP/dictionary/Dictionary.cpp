#include "Dictionary.h"

int Dictionary::wordCount = 0;

Dictionary::Dictionary() {}

Dictionary::Dictionary(const Dictionary& other) : tree(other.tree) {}

void Dictionary::fillDictionary(const std::string& filename) {
    try {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Не удалось открыть файл: " + filename);
        }

        std::string english, russian;
        while (std::getline(file, english)) {
            if (english.empty()) {
                continue;
            }
            
            if (!std::getline(file, russian)) {
                throw std::runtime_error("Неправильный формат файла: отсутствует перевод для слова '" + english + "'");
            }
            
            if (!russian.empty()) {
                addWord(english, russian);
            }
        }

        if (file.bad()) {
            throw std::runtime_error("Ошибка при чтении файла");
        }

        file.close();
        
        if (getWordCount() == 0) {
            throw std::runtime_error("Словарь пуст: не найдено ни одной валидной пары слов");
        }
    }
    catch (const std::exception& e) {
        throw std::runtime_error("Ошибка при загрузке словаря: " + std::string(e.what()));
    }
}

void Dictionary::addWord(const std::string& english, const std::string& russian) {
    if (!translate(english)) {
        wordCount++;
    }
    tree.insert(english, russian);
}

bool Dictionary::removeWord(const std::string& english) {
    if (tree.remove(english)) {
        wordCount--;
        return true;
    }
    return false;
}

std::string* Dictionary::translate(const std::string& english) {
    return tree.find(english);
}

int Dictionary::getWordCount() {
    return wordCount;
}

AVLTree& Dictionary::getTree() {
    return tree;
}