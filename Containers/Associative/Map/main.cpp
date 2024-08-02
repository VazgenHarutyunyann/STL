#include <iostream>

#include "Map.hpp"

int main() {

    Map<int, std::string> map;
    map.insert(1, "one");
    map.insert(2, "two");
    map.insert(3, "three");

    std::cout << "Map contents:" << std::endl;
    map.print();

    std::cout << "Value at key 2: " << map.at(2) << std::endl;

    std::cout << "Removing key 2" << std::endl;
    map.erase(2);
    map.print();

    try 
    {
        std::cout << "Value at key 2: " << map.at(2) << std::endl;
    } 
    catch (const std::out_of_range& e) 
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}