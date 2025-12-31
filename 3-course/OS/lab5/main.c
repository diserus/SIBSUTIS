#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/types.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef Node* (*create_node_func)(int);
typedef Node* (*append_func)(Node*, int);
typedef Node* (*prepend_func)(Node*, int);
typedef Node* (*delete_node_func)(Node*, int);
typedef Node* (*reverse_func)(Node*);
typedef void (*print_list_func)(Node*);
typedef void (*free_list_func)(Node*);
typedef int (*list_length_func)(Node*);
typedef int (*search_func)(Node*, int);

int main() {
    void *handle;
    Node *head = NULL;
    pid_t pid = getpid();
    
    printf("PID процесса: %d\n", pid);
    
    printf("\nСодержимое /proc/%d/maps перед загрузкой библиотеки:\n", pid);
    system("cat /proc/`pidof main`/maps | grep -E '\\.so|liblist' || echo 'Библиотека еще не загружена'");
    
    handle = dlopen("./liblist.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Ошибка загрузки библиотеки: %s\n", dlerror());
        exit(1);
    }
    
    printf("\nБиблиотека успешно загружена\n");
    
    printf("\nСодержимое /proc/%d/maps после загрузки библиотеки:\n", pid);
    system("cat /proc/`pidof main`/maps | grep -E '\\.so|liblist'");
    
    create_node_func create_node = dlsym(handle, "create_node");
    append_func append = dlsym(handle, "append");
    prepend_func prepend = dlsym(handle, "prepend");
    delete_node_func delete_node = dlsym(handle, "delete_node");
    reverse_func reverse = dlsym(handle, "reverse");
    print_list_func print_list = dlsym(handle, "print_list");
    free_list_func free_list = dlsym(handle, "free_list");
    list_length_func list_length = dlsym(handle, "list_length");
    search_func search = dlsym(handle, "search");
    
    char *error;
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "Ошибка получения адреса функции: %s\n", error);
        dlclose(handle);
        exit(1);
    }
        printf("\n--- Демонстрация работы с библиотекой ---\n");
    
    head = append(head, 10);
    head = append(head, 20);
    head = append(head, 30);
    head = prepend(head, 5);
    
    printf("Исходный список:\n");
    print_list(head);
    printf("Длина списка: %d\n", list_length(head));
    
    printf("\nПоиск элемента 20: %s\n", search(head, 20) ? "найден" : "не найден");
    printf("Поиск элемента 100: %s\n", search(head, 100) ? "найден" : "не найден");
    
    printf("\nРазворот списка:\n");
    head = reverse(head);
    print_list(head);
    
    printf("\nУдаление элемента 20:\n");
    head = delete_node(head, 20);
    print_list(head);
    
    printf("\nДобавление элемента 40 в конец:\n");
    head = append(head, 40);
    print_list(head);
    
    printf("\n--- Выгрузка библиотеки ---\n");
    free_list(head);
    head = NULL;
    
    if (dlclose(handle) != 0) {
        fprintf(stderr, "Ошибка выгрузки библиотеки: %s\n", dlerror());
        exit(1);
    }
    
    printf("Библиотека успешно выгружена\n");
    
    printf("\nСодержимое /proc/%d/maps после выгрузки библиотеки:\n", pid);
    system("cat /proc/`pidof main`/maps | grep -E '\\.so|liblist' || echo 'Библиотека успешно выгружена'");
    
    printf("\nПрограмма завершена.\n");
    return 0;
}