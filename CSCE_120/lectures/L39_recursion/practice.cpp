#include<iostream>
using namespace std;
int sumDigits(int n) {
    if(n == 0){
        return 0;
    }
    return (n % 10) + sumDigits(n/10);
}
int main() {
    int n = 0;
    cout << "Enter a number: ";
    cin >> n;
    cout << "Sum digits = " << sumDigits(n) << "\n";
}
