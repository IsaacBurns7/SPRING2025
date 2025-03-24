#include <iostream>
#include <cmath>
#include <cassert>
using std::cout;
bool isTriProduct(int n) {
    int limit = std::ceil(std::pow(n, (1.0/3.0)));
    for(int i = 1;i<limit;i++){
        if(n == (i * (i+1) * (i+2))){
            return true;
        }
    }
    return false;
}
int main(){
    assert(isTriProduct(6) == true);
    assert(isTriProduct(24) == true);
    assert(isTriProduct(0) == false);
    assert(isTriProduct(-6) == false);
    assert(isTriProduct(60) == true);
    cout << "Passed the tests!\n";
}