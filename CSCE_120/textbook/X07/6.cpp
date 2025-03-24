#include <iostream>

int main(){
    int num;
    char ch;

    char* ch2; 
    unsigned char* ch3;

    enum e{
        e1,
        e2,
        e3,
        e4,
        e5,
    };

    std::cout << "size of int: " << sizeof(num) << '\n';
    std::cout << "size of char: " << sizeof(ch) << '\n';
    std::cout << "size of char pointer: " << sizeof(ch2) << '\n';
    std::cout << "size of unsigned char pointer: " << sizeof(ch3) << '\n';
    std::cout << "size of enum w 5 elements: " << sizeof(e) << '\n';
}