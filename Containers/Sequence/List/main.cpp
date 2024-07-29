#include <iostream>
#include "List.hpp"

int main() {
    List<int> list;

    list.push_back(10);
    list.push_back(37);
    list.push_back(6);
    list.push_back(7);

    std::cout << "List after push_back: ";
    list.print();

    list.push_front(0);
    std::cout << "List after push_front: ";
    list.print();

    std::cout << "Front element: " << list.front() << std::endl;
    std::cout << "Back element: " << list.back() << std::endl;

    try 
    {
        list.pop_back();
        std::cout << "List after pop_back: ";
        list.print();
    } 
    catch (const std::out_of_range& e) 
    {
        std::cout << e.what() << std::endl;
    }

    try 
    {
        list.pop_front();
        std::cout << "List after pop_front: ";
        list.print();
    } 
    catch (const std::out_of_range& e) 
    {
        std::cout << e.what() << std::endl;
    }

    list.clear();
    std::cout << "List after clear: ";
    list.print();

    if (list.empty()) 
    {
        std::cout << "List is empty" << std::endl;
    }

    List<int> listCopy = list;
    std::cout << "Copied list: ";
    listCopy.print();

    list.push_back(23);
    list.push_back(66);
    List<int> anotherList = list;
    std::cout << "Another list: ";
    anotherList.print();

    return 0;
}