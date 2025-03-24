#include <iostream>

int main(){
    double num1;
    double num2;
    char ch;
    std::cout << "Enter a double value: ";
    std::cin >> num1;
    std::cout << "Enter a double value: ";
    std::cin >> num2;
    std::cout << "Enter a /, *, -, or +: ";
    std::cin >> ch;
    std::cout << num1 << " " << ch << " " << num2 << " is ";
    switch(ch){
        case '+':
            std::cout << num1+num2;
            break;
        case '-':
            std::cout << num1-num2;
            break;
        case '*':
            std::cout << num1*num2;
            break;
        case '/':
            std::cout << num1/num2;
            break;
    }
    std::cout << '\n';
}