#include <iostream>
#include "Stack.hpp"

int main() {
    Stack<int> stack;

    stack.push(7);
    stack.push(66);

    std::cout << "Stack after pushes: ";
    stack.print();

    std::cout << "Top element: " << stack.top() << std::endl;

    stack.pop();
    std::cout << "Stack after pop: ";
    stack.print();

    std::cout << "Top element: " << stack.top() << std::endl;

    stack.clear();
    std::cout << "Stack after clear: ";
    stack.print();

    if (stack.empty()) 
    {
        std::cout << "Stack is empty" << std::endl;
    }

    Stack<int> stackCopy = stack;
    std::cout << "Copied stack: ";
    stackCopy.print();

    stack.push(5);
    stack.push(6);
    Stack<int> anotherStack = stack;
    std::cout << "Another stack: ";
    anotherStack.print();

    return 0;
}