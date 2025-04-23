// TODO: Implement this source file
#include "MyString.h"

size_t strlen(const char* str){
    size_t n = 0;
    while(str[n] != '\0') n++;
    return n;
}

char* strcpy(char* destination, const char* source){
    char* dest = destination;

    while(*source != '\0'){
        *destination = *source;
        ++destination;
        ++source;
    }

    *destination = '\0';
    return dest;
}

MyString::MyString():str(new char[1]{'\0'}), len(0), cap(0){

}
MyString::MyString(const char* c_arr): len(strlen(c_arr)), cap(len){
    str = new char[cap + 1];
    strcpy(str, c_arr);
}
MyString::MyString(const MyString& other): len(other.len), cap(len){
    str = new char[cap + 1];
    strcpy(str, other.str);
}

bool MyString::empty(){
    return len == 0;
}
bool MyString::empty() const {
    return len == 0;
}
void MyString::clear(){
    len = 0;
    if(str) str[0] = '\0';
}

size_t MyString::find(const MyString& target, size_t pos) const {
    if(empty() || target.empty() || pos > len || (len - pos) < target.length()) return -1;

    while(str[pos] != '\0'){
        int j = 0;
        char ch = target.str[j];
        char ch2 = str[pos+j];
        while(ch != '\0' && ch == ch2){
            j++;
            ch = target.str[j];
            ch2 = str[pos+j];
        }
        if(target.str[j] == '\0'){
            return pos;
        }
        pos++;
    }
    return -1;
}

size_t MyString::length() const{
    return len;
}
size_t MyString::size() const{
    return len;
}
size_t MyString::capacity() const {
    return cap;
}
char& MyString::at(size_t index){
    if(index >= len){
        throw std::out_of_range("");
    }
    return str[index];
}
const char& MyString::at(size_t index) const{
    if(index >= len){
        throw std::out_of_range("");
    }
    return str[index];
}
char& MyString::front(){
    return str[0];
}
const char& MyString::front() const{
    return str[0];
}
const char* MyString::data() const{
    return str;
}

MyString& MyString::operator=(const MyString& other){
    if(this != &other){
        delete[] str;
        len = other.length();
        cap = other.cap;
        str = new char[cap+1];
        strcpy(str, other.str);
    }
    return *this;
}

MyString& MyString::operator+=(const MyString& other){
    size_t newLength = other.length() + len;

    if(newLength > cap){
        size_t newCap = newLength * 2;
        char* newStr = new char[newCap+1];
        strcpy(newStr, str);
        delete[] str;
        str = newStr;
        cap = newCap;
    }

    for(size_t i = 0;i < other.len;i++){
        str[len + i] = other.str[i]; 
    }
    len = newLength;
    str[len] = '\0';

    return *this;
}
// istream& operator>>(istream& is, MyString& obj){
//     char temp[1000];
//     is.getline(temp, 1000);
//     obj.str = new char[strlen(temp)+1];
//     obj.len = strlen(temp);
//     strcpy(obj.str, temp);

//     return is;
// } 
ostream& operator<<(ostream& os, const MyString& obj){
    if(obj.str){
        os << obj.str;
    }else {
        os << "null";
    }
    return os;
}


MyString::~MyString() {
    delete[] str;
}


