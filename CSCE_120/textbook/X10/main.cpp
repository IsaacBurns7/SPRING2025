#include <iostream>

//[1] (*1) Rewrite the following for-statement as an equivalent while-statement:
// for (i=0; i!=max_length; i++)
//     if (input_line[i] == '?')
//         quest_count++;
// Rewrite it to use a pointer as the controlled variable, that is, so that the test is of the form
// *p=='?'. Rewrite it to use a range-for.
/*
while(i < max_length){
    if(input_line[i] == '?')
        quest_count++;
    i++;
}
for(const auto& input : input_line){
    if(input == '?')
        questcount++;
}
for (i=0; i!=max_length; i++)
    if (*(input_line+i) == '?')
        quest_count++; 
*/

//[2] (*1) See how your compiler reacts to these errors:
// void f(int a, int b)
// {
//     if (a = 3) // ...
//     if (a&(077 == 0)) // ...
//     a := b+1;
// }
//Devise more simple errors and see how the compiler reacts.

//[3] (*1.5) What does the following example do?
void send(int* to, int* from, int count)
// Duff ’s device. Helpful comment deliberately deleted.
{
    int n = (count+7)/8;
    switch (count%8) {
    case 0: do { *to++ = *from++;
    case 7: *to++ = *from++;
    case 6: *to++ = *from++;
    case 5: *to++ = *from++;
    case 4: *to++ = *from++;
    case 3: *to++ = *from++;
    case 2: *to++ = *from++;
    case 1: *to++ = *from++;
        } while (--n>0);
    }
}
//Why would anyone write something like that? No, this is not recommended as good style.
//apparently its faster?

//[4] (∗2) Write a function atoi(const char∗) that takes a C-style string containing digits and returns
// the corresponding int. For example, atoi("123") is 123. Modify atoi() to handle C++ octal and
// hexadecimal notation in addition to plain decimal numbers. Modify atoi() to handle the C++
// character constant notation.
int atoi(char* str){
    int res = 0;
    int len = 0;
    while(str[len] != '\0'){
        len++;
    }

    for(int i = 0;str[i] != '\0';i++){
        int power = std::pow(10, len-1-i);
        res += power * (str[i] - '0');
    }
    return res;
}

int atoi_hex(char* str){
    int res = 0x0;
    int len = 0;
    while(str[len] != '\0'){
        len++;
    }

    for(int i = 0;str[i] != '\0';i++){
        int power = std::pow(16, len-1-i);
        int digit = str[i] - '0';
        if(digit >= 10){
            if(islower(str[i])){
                digit = str[i] - 'a' + 10;
            }else if (isupper(str[i])){
                digit = str[i] - 'A' + 10;
            }
        }
        res += power * digit;
    }
    return res;
}
// [5] (∗2) Write a function itoa(int i, char b[]) that creates a string representation of i in b and
// returns b.
// [6] Modify iota() from the previous exercise to take an extra ‘‘string length’’ argument to make
// overflow less likely.
void itoa(int i, char b[], int length){
    int index = 0;
    while(i != 0 && index < length){
        int digit = i % 10;
        i /= 10;

        b[index] = digit + '0';

        index++;
    }
    int len2 = std::min(length, index);
    for(int j = 0;j<(len2 / 2);j++){
        //std::cout << "swapping: " << b[j] << " and " << b[len2-j-1] << '\n';
        int tmp = b[j];
        b[j] = b[len2-j-1];
        b[len2-j-1] = tmp;
    }
}

int main(){
    int from[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};  // Source array
    int to[10] = {0};  // Destination array, initialized to 0
    
    int count = 10;  // Number of elements to copy

    // Call Duff's Device function
    send(to, from, count);

    // Print the copied array
    for (int i = 0; i < count; i++) {
        std::cout << to[i] << " ";
    }
    std::cout << '\n';
    char* str {"123"};
    int digits = atoi(str);
    std::cout << digits << '\n';

    char* str2 {"8FC"};
    int digits2 = atoi_hex(str2);
    std::cout << std::hex << digits2 << '\n';

    char* str3 {"8cf"};
    int digits3 = atoi_hex(str3);
    std::cout << std::hex << digits3 << '\n';

    char b[4];
    itoa(123, b, 4);
    for(int i = 0; b[i] != '\0';i++){
        std::cout << b[i];
    }
    std::cout << '\n';

    
}