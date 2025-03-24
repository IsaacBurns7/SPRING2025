#include <iostream>
int main(){
    signed char sch = 'a';
    unsigned char usch = 'a';
    char ch = 'a';
    std::cout << (ch == sch ? "signed" : "unsigned") << '\n';
}