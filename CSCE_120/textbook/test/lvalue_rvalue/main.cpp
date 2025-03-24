#include <iostream>

void foo(int& x) { std::cout << "Lvalue reference\n"; }
void foo(int&& x) { std::cout << "Rvalue reference\n"; }

int main() {
    int a = 5;
    foo(a);     // Lvalue reference
    foo(10);    // Rvalue reference
    foo(std::move(a)); // Rvalue reference
}
