#pragma once
#include "AVLTree.h"

class Dictionary
{
private:
    AVLTree tree;
    static int wordCount;

public:
    Dictionary();
    Dictionary(const Dictionary &other);
    void fillDictionary(const std::string &filename);
    void addWord(const std::string &english, const std::string &russian);
    bool removeWord(const std::string &english);
    std::string *translate(const std::string &english);
    AVLTree &getTree();
    static int getWordCount();
};
