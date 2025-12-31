#pragma once
#include <iostream>
#include <stdexcept>
#include "list.hpp"

template <typename T>
class Queue : public List<T> {
private:
    Node<T>* rear;

public:
    Queue() : List<T>(), rear(nullptr) {}
    ~Queue() override {
        this->clear();
    }

    void add(const T value) override {
        enqueue(value);
    }

    void remove(const T value) override {
        if (this->isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }

        Node<T>* current = this->head;
        Node<T>* prev = nullptr;

        while (current != nullptr) {
            if (current->data == value) {
                if (prev == nullptr) {
                    this->head = current->next;
                    if (current == rear) {
                        rear = nullptr;
                    }
                } else {
                    prev->next = current->next;
                    if (current == rear) {
                        rear = prev;
                    }
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
        rear = nullptr;
    }

    void print() override {
        Node<T>* current = this->head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    void enqueue(const T value) {
        Node<T>* newNode = new Node<T>(value);
        if (this->isEmpty()) {
            this->head = newNode;
            rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    T dequeue() {
        if (this->isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }

        Node<T>* temp = this->head;
        T value = temp->data;
        this->head = this->head->next;

        if (this->head == nullptr) {
            rear = nullptr;
        }

        delete temp;
        return value;
    }

    T front() const {
        if (this->isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }

        return this->head->data;
    }

    bool isEmpty() const override { 
        return this->head == nullptr; 
    }
};
