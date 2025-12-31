#pragma once

template <typename T>
struct Node
{
    T data;
    Node *next;
    Node(const T &value) : data(value), next(nullptr) {}
};

template <typename T>
class List
{
protected:
    Node<T> *head;

public:
    List() : head(nullptr) {}
    virtual ~List() {}

    virtual void add(const T value) = 0;
    virtual void remove(const T value) = 0;
    virtual void clear() = 0;
    virtual void print() = 0;

    virtual bool isEmpty() const { 
        return head == nullptr; 
    }
};
