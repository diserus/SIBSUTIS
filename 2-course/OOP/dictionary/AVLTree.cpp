#include "AVLTree.h"

AVLTree::AVLTree() : BinaryTree() {}

void AVLTree::deleteTree(Node* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

AVLTree::~AVLTree() {
    deleteTree(root);
}

int AVLTree::getNodeHeight(AVLNode* node) const {
    if (!node) return 0;
    return node->height;
}

void AVLTree::updateHeight(AVLNode* node) {
    if (node) {
        node->height = 1 + std::max(getNodeHeight(static_cast<AVLNode*>(node->left)),
                                  getNodeHeight(static_cast<AVLNode*>(node->right)));
    }
}

int AVLTree::getBalance(AVLNode* node) const {
    if (!node)
        return 0;
    return getNodeHeight(static_cast<AVLNode*>(node->left)) -
           getNodeHeight(static_cast<AVLNode*>(node->right));
}

AVLTree::AVLNode* AVLTree::rightRotate(AVLNode* y) {
    if (!y || !y->left) return y;
    
    AVLNode* x = static_cast<AVLNode*>(y->left);
    AVLNode* T2 = static_cast<AVLNode*>(x->right);

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

AVLTree::AVLNode* AVLTree::leftRotate(AVLNode* x) {
    if (!x || !x->right) return x;
    
    AVLNode* y = static_cast<AVLNode*>(x->right);
    AVLNode* T2 = static_cast<AVLNode*>(y->left);

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

AVLTree::AVLNode* AVLTree::insertNode(AVLNode* node, const std::string& k, const std::string& v) {
    if (!node)
        return new AVLNode(k, v);

    if (k < node->key)
        node->left = insertNode(static_cast<AVLNode*>(node->left), k, v);
    else if (k > node->key)
        node->right = insertNode(static_cast<AVLNode*>(node->right), k, v);
    else {
        node->value = v;
        return node;
    }

    updateHeight(node);

    int balance = getBalance(node);

    if (balance > 1 && k < static_cast<AVLNode*>(node->left)->key)
        return rightRotate(node);

    if (balance < -1 && k > static_cast<AVLNode*>(node->right)->key)
        return leftRotate(node);

    if (balance > 1 && k > static_cast<AVLNode*>(node->left)->key) {
        node->left = leftRotate(static_cast<AVLNode*>(node->left));
        return rightRotate(node);
    }

    if (balance < -1 && k < static_cast<AVLNode*>(node->right)->key) {
        node->right = rightRotate(static_cast<AVLNode*>(node->right));
        return leftRotate(node);
    }

    return node;
}

void AVLTree::insert(const std::string& key, const std::string& value) {
    root = static_cast<Node*>(insertNode(static_cast<AVLNode*>(root), key, value));
}

std::string* AVLTree::find(const std::string& key) {
    AVLNode* current = static_cast<AVLNode*>(root);
    while (current) {
        if (key < current->key)
            current = static_cast<AVLNode*>(current->left);
        else if (key > current->key)
            current = static_cast<AVLNode*>(current->right);
        else
            return &(current->value);
    }
    return nullptr;
}

AVLTree::AVLNode* AVLTree::removeNode(AVLNode* node, const std::string& k) {
    if (!node)
        return nullptr;

    if (k < node->key)
        node->left = removeNode(static_cast<AVLNode*>(node->left), k);
    else if (k > node->key)
        node->right = removeNode(static_cast<AVLNode*>(node->right), k);
    else {
        if (!node->left || !node->right) {
            AVLNode* temp = static_cast<AVLNode*>(node->left ? node->left : node->right);
            if (!temp) {
                temp = node;
                node = nullptr;
            } else
                *node = *temp;
            delete temp;
        } else {
            AVLNode* temp = static_cast<AVLNode*>(node->right);
            while (temp->left)
                temp = static_cast<AVLNode*>(temp->left);
            node->key = temp->key;
            node->value = temp->value;
            node->right = removeNode(static_cast<AVLNode*>(node->right), temp->key);
        }
    }

    if (!node)
        return nullptr;

    updateHeight(node);
    int balance = getBalance(node);

    if (balance > 1 && getBalance(static_cast<AVLNode*>(node->left)) >= 0)
        return rightRotate(node);

    if (balance > 1 && getBalance(static_cast<AVLNode*>(node->left)) < 0) {
        node->left = leftRotate(static_cast<AVLNode*>(node->left));
        return rightRotate(node);
    }

    if (balance < -1 && getBalance(static_cast<AVLNode*>(node->right)) <= 0)
        return leftRotate(node);

    if (balance < -1 && getBalance(static_cast<AVLNode*>(node->right)) > 0) {
        node->right = rightRotate(static_cast<AVLNode*>(node->right));
        return leftRotate(node);
    }

    return node;
}

bool AVLTree::remove(const std::string& key) {
    bool existed = find(key) != nullptr;
    if (existed)
        root = static_cast<Node*>(removeNode(static_cast<AVLNode*>(root), key));
    return existed;
}

int AVLTree::getHeight() const {
    return getNodeHeight(static_cast<AVLNode*>(root));
}

void inOrderTraversal(AVLTree::AVLNode* node) {
    if (node == nullptr) return;
    inOrderTraversal(static_cast<AVLTree::AVLNode*>(node->left));
    std::cout << "Ключ: " << node->key << ", Значение: " << node->value << std::endl;
    inOrderTraversal(static_cast<AVLTree::AVLNode*>(node->right));
}

void printTree(AVLTree &tree) {
    AVLTree::AVLNode* avlRoot = static_cast<AVLTree::AVLNode*>(tree.root);
    if (avlRoot == nullptr) return;
    inOrderTraversal(avlRoot);
}
