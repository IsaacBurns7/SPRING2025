#include <iostream>

int main(){
    char ch;
    std::cout << "Enter a single character: ";
    std::cin >> ch;
    int i = ch;
    std::cout << "You have entered '" << ch << "', which has ASCII code " << i << ".\n";
}