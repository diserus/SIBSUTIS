#include <stdio.h>
#include <stdlib.h>
#include "list.h"

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

Node* append(Node* head, int data) {
    Node* new_node = create_node(data);
    
    if (head == NULL) {
        return new_node;
    }
    
    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
    
    return head;
}

Node* prepend(Node* head, int data) {
    Node* new_node = create_node(data);
    new_node->next = head;
    return new_node;
}

Node* delete_node(Node* head, int data) {
    if (head == NULL) {
        return NULL;
    }
    
    if (head->data == data) {
        Node* temp = head->next;
        free(head);
        return temp;
    }
    
    Node* current = head;
    while (current->next != NULL && current->next->data != data) {
        current = current->next;
    }
    
    if (current->next != NULL) {
        Node* temp = current->next;
        current->next = current->next->next;
        free(temp);
    }
    
    return head;
}

Node* reverse(Node* head) {
    Node* prev = NULL;
    Node* current = head;
    Node* next = NULL;
    
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    
    return prev;
}

void print_list(Node* head) {
    Node* current = head;
    printf("Список: ");
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void free_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int list_length(Node* head) {
    if (head == NULL) {
        return 0;
    }
    return 1 + list_length(head->next);
}

int search(Node* head, int data) {
    if (head == NULL) {
        return 0;
    }
    if (head->data == data) {
        return 1;
    }
    return search(head->next, data);
}
