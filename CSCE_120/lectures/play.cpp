#include <iostream>
using std::cout; 

int main(){
    long long* ptr = new long long(10);
    long long mx = std::numeric_limits<int>::max();
    cout << mx << '\n';
    for(int i = 0; i<1e9; i++){
        cout << ptr << '\n';
        ptr = new long long[1000000];
    }
}