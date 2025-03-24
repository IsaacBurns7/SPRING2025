#include <iostream>
#include <string>

using std::string, std::cout, std::cin;

/*
    [7] (∗1) Write a function that swaps (exchanges the values of) two integers. 
    Use int∗ as the argument type. Write another swap function using int& as the argument type.
*/
void swap(int* num1, int* num2){
    int tmp = *num1;
    *num1 = *num2;
    *num2 = tmp;
}
void swap(int& num1, int& num2){
    int tmp = num1; 
    num1 = num2; 
    num2 = tmp;
}
/*
[9] (∗1) Define functions f(char), g(char&), and h(const char&). Call them with the arguments 'a',
49, 3300, c, uc, and sc, where c is a char, uc is an unsigned char, and sc is a signed char.
Which calls are legal? Which calls cause the compiler to introduce a temporary variable?
*/
void f(char);
void g(char&);
void h(const char&);

int main(){
    /*
    [1] (∗1) Write declarations for the following: a pointer to a character, an array of 10 integers, a
reference to an array of 10 integers, a pointer to an array of character strings, a pointer to a
pointer to a character, a constant integer, a pointer to a constant integer, and a constant
pointer to an integer. Initialize each one.
    */

    // char ch = 'a';
    // char* cp = &ch;
    // int arr1[10] {1,2,3};
    // int (&arr2)[10] = arr1;
    // string string_array[3]{"uwu"};
    // string* pointer_to_string_array = string_array;
    // char** cpp = &cp;
    // const int cx = 3;
    // const int cx2 = 18;
    // int x = 5;
    // int x2 = 7;
    // const int* cxp = &cx; //pointer to constant integer
    // int *const cpx = &x; //constant point to integer
    //cpx = &x2; error bc pointer is constant
    //*cxp = 12; error bc pointer points to constant

    // cout << *cp << '\n';
    // cout << cp << '\n'; //implicit deference
    // cout << pointer_to_string_array << '\n';
    // cout << &cp << '\n';
    // cout << cpp << '\n'; //implicit dereference (when cout)

    /*
    [2] (∗1.5) What, on your system, are the restrictions on the pointer types char∗, int∗, and void∗?
For example, may an int∗ have an odd value? Hint: alignment.

    char* can point to any byte of memory
    For any other type T, it must be placed in a memory location divisible by its alignment, so that it can align
    */

    // cout << alignof(char) << '\n';
    // cout << alignof(int) << '\n';
    // cout << alignof(void*) << '\n';

    /*
    [3] (∗1) Use an alias (using) to define the types unsigned char, const unsigned char, pointer to
integer, pointer to pointer to char, pointer to array of char, array of 7 pointers to int, pointer to
an array of 7 pointers to int, and array of 8 arrays of 7 pointers to int.
    */
    using Uchar = unsigned char;
    using CUchar = const unsigned int;
    using Pint = int*;
    using PPchar = char**;
    using PArrchar = char(*)[7];
    using ArrPint = int* [7];
    using PArrPint = int* (*)[7];
    using ArrArrPint = int* [8][7];

    Uchar s = 'a';
    char letters[7] {'a', 'b', 'c', 'd'};
    PArrchar pointer_to_letters = &letters;

    // cout << (*pointer_to_letters)[0]++ << '\n';
    // cout << (*pointer_to_letters)[0]++ << '\n';
    // cout << (*pointer_to_letters)[0] << '\n';
    // cout << ++(*pointer_to_letters)[0] << '\n';

    int salary1 = 1;
    int salary2 = 2;
    int salary3 = 3;
    int* p1 = &salary1;
    int* p2 = &salary2;
    int* p3 = &salary3;
    ArrPint salaries_pointers {p1, p2, p3};

    // cout << salaries_pointers[0] << '\n';
    // cout << *salaries_pointers[0] << '\n';

    PArrPint pointer_to_salaries_pointers = &salaries_pointers;
    
    // cout << (pointer_to_salaries_pointers)[0] << '\n';
    // cout << (*pointer_to_salaries_pointers)[0] << '\n'; //dereference, now p1
    // cout << *(*pointer_to_salaries_pointers)[0] << '\n'; //dereference p1, now salary1

    /*
    [4] (∗1) Given two char∗s pointing into an array, find and output the number of characters
between the two pointed-to characters (zero if they point to the same element).
    */

    char word[] {"abcdefghijklmnopqrstuvwxyz"};
    char* pch1{&word[25]};
    char* pch2{&word[1]};

    char* start = std::min(pch1, pch2);
    char* end = std::max(pch2, pch1);
    int count = 0;
    while(start < end){
        count++;
        start++;
    }
    // cout << count << '\n';

    /*
    [6] (∗2) What happens when you read and write beyond the bounds of an array. Do a few experiments involving 
a global array of ints , a local array of ints, an array of ints allocated by new,
and a member array of ints. Try reading and writing just beyond the end and far beyond the
end. Try the same for just before and far before the beginning. See what happens for different optimizer levels. 
Then try hard never to do out-of-range access by mistake.
    */
    int global_arr[] {1,2,3,4,5};
    {
        int local_arr[] {4,5,6};
        // cout << local_arr[5] << '\n';
        // cout << local_arr[124215215] << '\n';
        // cout << local_arr[-5] << '\n';
        // cout << local_arr[-521651236] << '\n';
    }
    int* arr_new { new int[5]{10,11,12,13,14} };
    class arr_handler{
        public:
            arr_handler(int* arr, int len)
            {
                member_arr = new int[len];
                for(int i = 0;i<len;i++){
                    member_arr[i] = arr[i];
                }
            };
            

        private:
            int* member_arr;
            // std::initializer_list<int> intarray_to_initializerlist(const int* arr, int size){
            //     constexpr int n = 1000;
            //     static int temp[n];
            //     for(size_t i = 0;i<n;i++){
            //         temp[i] = arr[i];
            //     }
            //     return {temp, temp + size};
            // }
            // note: initializer list constructor is not helpful :( 

    };
    arr_handler handler1 {global_arr, sizeof(global_arr)};
    // cout << global_arr[5] << '\n';
    // cout << global_arr[-1] << '\n';
    // cout << arr_new[125] << '\n';
    // cout << arr_new[-2141245] << '\n';
    //cout << handler1.member_arr[-1] << '\n';
   
    /*
    7 test
    */
    // int* ptr1 = new int(6);
    // int* ptr2 = new int(5);
    
    // cout << "BEFORE SWAP\n";
    // cout << ptr1 << "," << ptr2 << '\n';
    // cout << *ptr1 << ',' << *ptr2 << '\n';
    // swap(ptr1, ptr2);
    // cout << "AFTER SWAP\n";
    // cout << ptr1 << "," << ptr2 << '\n'; //these dont change
    // cout << *ptr1 << ',' << *ptr2 << '\n'; //but these do!
    // cout << '\n';

    // int x1_7 = 5;
    // int x2_7 = 7;
    
    // cout << "BEFORE SWAP\n";
    // cout << x1_7 << "," << x2_7 << '\n';
    // swap(x1_7, x2_7);
    // cout << "AFTER SWAP\n";
    // cout << x1_7 << "," << x2_7 << '\n'; //these change

    /*
    9 test
    */

    //'a', 49, 3300, c, uc, and sc
    //Which calls are legal? Which calls cause the compiler to introduce a temporary variable?
    char c = 'a';
    unsigned char uc = 'a';
    signed char sc = 'a';
    f('a');
    g('a'); //invalid - initial value of reference to non-const must be lvalue - true for 'a', 49,
    h('a'); //creates a temporary variable - true for 'a', 49, 3300
    f(49);
    g(49);
    h(49);
    f(3300);
    g(3300);
    h(3300);
    f(c);
    g(c);
    h(c);
    f(uc);
    g(uc);
    h(uc);
    f(sc);
    g(sc);
    h(sc);
}

