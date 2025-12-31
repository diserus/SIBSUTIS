#include "stack.hpp"
#include "queue.hpp"
#include <iostream>
#include <windows.h>

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    system("chcp 65001");
    
    Stack<double> stackk;
    stackk.add(1);
    stackk.add(2);
    List<double> *stack= &stackk;
    List<double> *queue= new Queue<double>();
    stackk.pop();
    stack->add(1);
    stack->add(2);
    queue->add(3);
    queue->add(4);

    stack->print();
    queue->print();
    return 0;
}
