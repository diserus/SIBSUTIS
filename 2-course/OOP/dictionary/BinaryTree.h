#pragma once
#include <string>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <algorithm>
#include <functional>
#include <fstream>
#include <sstream>
#include <locale>
#include <codecvt>
#include <cstdlib>
class BinaryTree {
protected:
    struct Node {
        std::string key;
        std::string value;
        Node* left;
        Node* right;
        
        Node(const std::string& k, const std::string& v) : key(k), value(v), left(nullptr), right(nullptr) {}
    };

    Node* root;

public:
    BinaryTree() : root(nullptr) {}
    virtual ~BinaryTree() = 0; 

    virtual void insert(const std::string& key, const std::string& value) = 0;
    virtual bool remove(const std::string& key) = 0;
    virtual std::string* find(const std::string& key) = 0;
    virtual int getHeight() const = 0;
};