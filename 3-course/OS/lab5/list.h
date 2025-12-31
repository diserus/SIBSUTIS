#ifndef LIST_H
#define LIST_H

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_node(int data);
Node* append(Node* head, int data);
Node* prepend(Node* head, int data);
Node* delete_node(Node* head, int data);
Node* reverse(Node* head);
void print_list(Node* head);
void free_list(Node* head);

int list_length(Node* head);
int search(Node* head, int data);

#endif