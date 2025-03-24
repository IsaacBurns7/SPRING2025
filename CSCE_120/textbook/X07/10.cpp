#include <iostream>

int main() {
    std::cout << "Type\t\tSize (bytes)\tAlignment (bytes)\n";
    std::cout << "-------------------------------------------------\n";
    std::cout << "bool\t\t" << sizeof(bool) << "\t\t" << alignof(bool) << "\n";
    std::cout << "char\t\t" << sizeof(char) << "\t\t" << alignof(char) << "\n";
    std::cout << "short\t\t" << sizeof(short) << "\t\t" << alignof(short) << "\n";
    std::cout << "int\t\t" << sizeof(int) << "\t\t" << alignof(int) << "\n";
    std::cout << "long\t\t" << sizeof(long) << "\t\t" << alignof(long) << "\n";
    std::cout << "long long\t" << sizeof(long long) << "\t\t" << alignof(long long) << "\n";
    std::cout << "float\t\t" << sizeof(float) << "\t\t" << alignof(float) << "\n";
    std::cout << "double\t\t" << sizeof(double) << "\t\t" << alignof(double) << "\n";
    std::cout << "long double\t" << sizeof(long double) << "\t\t" << alignof(long double) << "\n";
    std::cout << "unsigned\t" << sizeof(unsigned) << "\t\t" << alignof(unsigned) << "\n";
    std::cout << "unsigned long\t" << sizeof(unsigned long) << "\t\t" << alignof(unsigned long) << "\n";

    return 0;
}
