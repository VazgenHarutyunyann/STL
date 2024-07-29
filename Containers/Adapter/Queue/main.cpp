#include <iostream>
#include "Queue.hpp"

int main() {
    Queue<int> queue;

    queue.enqueue(76);
    queue.enqueue(23);
    queue.enqueue(32);

    std::cout << "Queue after enqueue operations: ";
    queue.print();

    std::cout << "Front element: " << queue.front() << std::endl;
    std::cout << "Back element: " << queue.back() << std::endl;

    queue.dequeue();
    std::cout << "Queue after dequeue operation: ";
    queue.print();

    std::cout << "Front element: " << queue.front() << std::endl;
    std::cout << "Back element: " << queue.back() << std::endl;

    queue.clear();
    std::cout << "Queue after clear operation: ";
    queue.print();

    if (queue.empty()) 
    {
        std::cout << "Queue is empty" << std::endl;
    }

    Queue<int> queueCopy = queue;
    std::cout << "Copied queue: ";
    queueCopy.print();

    queue.enqueue(66);
    queue.enqueue(7);
    Queue<int> anotherQueue = queue;
    std::cout << "Another queue: ";
    anotherQueue.print();

    return 0;
}