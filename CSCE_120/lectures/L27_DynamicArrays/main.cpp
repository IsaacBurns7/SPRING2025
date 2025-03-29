#include<iostream>
using std::cout, std::endl;

void duplicateElements(int*& arr, int n) {
   int* dupArr = new int [2*n];
   for (unsigned int i = 0; i < n; i++) {
      dupArr[2*i] = arr[i];
      dupArr[2*i + 1] = arr[i];
   }
   delete [] arr;
   arr = dupArr; //this arr is a local pointer
}

int main() {
    const int n = 3;
    int* arr = new int [3]{1,3,5};
    duplicateElements(arr,3);
    for (unsigned int i=0; i < 2*n; i++) {
        cout << arr[i] << ",";
    }
    delete [] arr;
} 