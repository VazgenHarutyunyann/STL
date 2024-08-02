#include <iostream>

#include "Multimap.hpp"

int main() {

    Multimap<int, std::string> multimap;
    
    multimap.insert(1, "one");
    multimap.insert(1, "mek");
    multimap.insert(2, "two");
    multimap.insert(3, "three");
    multimap.insert(3, "ereq");

    std::cout << "Multimap contents:" << std::endl;
    multimap.print();

    std::cout << "Values at key 1: ";
    std::vector<std::string> values1 = multimap.at(1);
    for (const auto& value : values1) 
    {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    std::cout << "Removing key 1" << std::endl;
    multimap.erase(1);
    multimap.print();

    try 
    {
        std::cout << "Values at key 1: ";
        std::vector<std::string> values1 = multimap.at(1);
        for (const auto& value : values1) 
        {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    } 
    catch (const std::out_of_range& e) 
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}