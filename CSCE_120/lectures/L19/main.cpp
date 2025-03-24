#include<iostream>
void swap(double& a, double* b){ //reference to a pointer, same pointer as b
    //note: double*& b and double* b do the exact fucking same thing.
    double* temp = new double(a);
    a = *b;
    b = temp;
}
int main(){
    double x = 3.5;
    double* y = new double(35);
    swap(x, y);
    std::cout << x << ',' << y << '\n';

    int* p = nullptr;
    if(p == nullptr){
        int x = 7;
        p = &x; //both p and x point to same address on the stack
    
    }
    //x goes out of scope, and it's address on the stack no longer exists
    std::cout << *p << '\n'; //this is undefined behavior
    if(p == nullptr){
        int* x = new int(7);
        p = x; //both p and x point to same address on the heap
    }
    //x goes out of scope, but that address on the heap still exists
    std::cout << *p << '\n'; //7

    for(int i = 0; i < 1000000000; i++){
        int* p = new int(7);
        std::cout << p << '\n';
    }
    std::cout << "Done";

}
