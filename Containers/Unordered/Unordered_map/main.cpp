#include <iostream>
#include "Unordered_map.hpp"

int main() {
    UnorderedMap<int, std::string> unorderedMap;

    unorderedMap.insert(1, "one");
    unorderedMap.insert(2, "two");
    unorderedMap.insert(3, "three");
    unorderedMap.insert(4, "four");

    std::cout << "UnorderedMap contents:" << std::endl;
    unorderedMap.print();

    std::cout << "Value at key 3: " << unorderedMap.at(3) << std::endl;

    std::cout << "Removing key 2" << std::endl;
    unorderedMap.erase(2);
    unorderedMap.print();

    try 
    {
        std::cout << "Value at key 2: " << unorderedMap.at(2) << std::endl;
    } 
    catch (const std::out_of_range& e) 
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}