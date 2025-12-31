#pragma once
#include "BinaryTree.h"

class AVLTree : public BinaryTree
{
private:
    struct AVLNode : public BinaryTree::Node
    {
        int height;
        AVLNode(const std::string &k, const std::string &v) : BinaryTree::Node(k, v), height(1) {}
    };
    
    void deleteTree(Node* node);
    AVLNode* insertNode(AVLNode* node, const std::string& k, const std::string& v);
    AVLNode* removeNode(AVLNode* node, const std::string& k);
    int getBalance(AVLNode* node) const;
    AVLNode* rightRotate(AVLNode* y);
    AVLNode* leftRotate(AVLNode* x);
    int getNodeHeight(AVLNode* node) const;
    void updateHeight(AVLNode* node);

public:
    AVLTree();
    ~AVLTree() override;

    void insert(const std::string &key, const std::string &value) override;
    bool remove(const std::string &key) override;
    std::string* find(const std::string &key) override;
    int getHeight() const override;
    
    friend void inOrderTraversal(AVLNode* node);
    friend void printTree(AVLTree &tree);
};
