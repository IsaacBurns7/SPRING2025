#include <limits>
#include <iostream>

int main(){
    int64_t mx = INT32_MAX;
    int32_t a, b, c;
    std::cout << "Enter two numbers to add them: ";
    std::cin >> a >> b;
    if(1ll*a + 1ll*b > mx){
        throw std::out_of_range("a + b is out of int32 range");
    } 
    c = a+b;
    std::cout << a << " + " << b << " = " << c << '\n';


    std::cout << "Enter two numbers to subtract them: ";
    std::cin >> a >> b;
    if(1ll*a - 1ll*b > mx){
        throw std::out_of_range("a - b is out of int32 range");
    } 
    c = a-b;
    std::cout << a << " - " << b << " = " << c << '\n';

    std::cout << "Enter two numbers to multiply them: ";
    std::cin >> a >> b;
    if(1ll*a * 1ll*b > mx){
        throw std::out_of_range("a * b is out of int32 range");
    } 
    c = a*b;
    std::cout << a << " * " << b << " = " << c << '\n';

    std::cout << "Enter two numbers to divide them: ";
    std::cin >> a >> b;
    if((1ll*a) / (1ll*b) > mx){
        throw std::out_of_range("a / b is out of int32 range");
    } 
    c = a/b;
    std::cout << a << " / " << b << " = " << c << '\n';
}