#include <iostream>
#include "vector.hpp"

int main() {
    Vector<int> vec;
    
    vec.push_back(3);
    vec.push_back(9);
    vec.push_back(4);

    std::cout << "Vector after push_back: ";
    vec.print();

    std::cout << "Element at index 0: " << vec[0] << std::endl;

    try 
    {
        std::cout << "Element at index 2: " << vec.at(2) << std::endl;
    } 
    catch (const std::out_of_range& e) 
    {
        std::cerr << e.what() << std::endl;
    }

    vec.resize(5, 10);
    std::cout << "Vector after resize to 5 with default value 10: ";
    vec.print();

    vec.reserve(10);
    std::cout << "Vector capacity after reserve: " << vec.getCapacity() << std::endl;

    std::cout << "Front element: " << vec.front() << std::endl;
    std::cout << "Back element: " << vec.back() << std::endl;

    vec.pop_back();
    std::cout << "Vector after pop_back: ";
    vec.print();

    vec.clear();
    std::cout << "Vector after clear: ";
    vec.print();

    if (vec.empty()) 
    {
        std::cout << "Vector is empty" << std::endl;
    }
    else
    {
        std::cout << "Vector is not empty" << std::endl;
    }

    Vector<int> vec2(3);
    std::cout << "Vector with initial size 3: ";
    vec2.print();

    return 0;
}