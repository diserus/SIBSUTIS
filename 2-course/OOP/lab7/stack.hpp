#pragma once
#include <iostream>
#include <stdexcept>
#include "list.hpp"

template <typename T>
class Stack : public List<T> {
public:
    Stack() : List<T>() {}
    ~Stack() override {
        this->clear();
    }

    void add(const T value) override {
        push(value);
    }

    void remove(const T value) override {
        if (this->isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }

        Node<T>* current = this->head;
        Node<T>* prev = nullptr;

        while (current != nullptr) {
            if (current->data == value) {
                if (prev == nullptr) {
                    this->head = current->next;
                } else {
                    prev->next = current->next;
                }

                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    void clear() override {
        while (this->head != nullptr) {
            Node<T>* temp = this->head;
            this->head = this->head->next;
            delete temp;
        }
    }

    void print() override {
        Node<T>* current = this->head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    void push(const T value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = this->head;
        this->head = newNode;
    }

    T pop() {
        if (this->isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }

        Node<T>* temp = this->head;
        T value = temp->data;
        this->head = this->head->next;

        delete temp;
        return value;
    }

    T top() const {
        if (this->isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }

        return this->head->data;
    }

    bool isEmpty() const override { 
        return this->head == nullptr; 
    }
};
