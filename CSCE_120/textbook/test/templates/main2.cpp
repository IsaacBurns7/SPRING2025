#include <vector>
#include <list>
#include <iostream>

template<typename C>
using Element_type = typename C::value_type;

template<typename Container>
void algo(Container& c)
{
    std::vector<Element_type<Container>> vec; // Use std::vector instead of Vector
    // Process the container and store results in vec
    for (const auto& elem : c) {
        vec.push_back(elem); // Example: Copy elements to vec
    }

    // Print the results
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

int main()
{
    std::vector<int> v = {1, 2, 3, 4};
    algo(v); // Output: 1 2 3 4

    std::list<std::string> l = {"hello", "world"};
    algo(l); // Output: hello world

    return 0;
}