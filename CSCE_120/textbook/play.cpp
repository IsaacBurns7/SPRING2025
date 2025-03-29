#include <iostream>
#include <vector>
using std::vector, std::cout, std::cin;


int recursive(const vector<int>& choices, int choices_left, int target, int n){
    if(n == target){
        return 1; 
    }
    if(n > target){
        return 0;
    }
    if(choices_left == 0){
        return 0;
    }
    for(const auto& choice: choices){
        return recursive(choices, choices_left-1, target, n+choice);
    }
}

int main(){
    //(x^1+x^2+x^3+...+x^n)^m
    //{1,2,3,4,5,...,n} for m arrays. 
    //this may be able to be solved by DP 
    vector<int> choices = {2,3,4};
    cout << recursive(choices, 4, 10, 0);
}
