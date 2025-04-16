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

MyString::MyString():str(new char('\0')), len(0){

}
MyString::MyString(const char* c_arr){
    len = strlen(c_arr);
    str = new char[len+1];
    strcpy(str, str);
}
MyString::MyString(MyString& other){
    len = other.len;
    str = new char[len + 1];
    strcpy(str, other.str);
}

bool MyString::empty(){
    return len == 0;
}
void MyString::clear(){
    len = 0;
    delete[] str;
    str = new char('\0');
}
size_t MyString::find(MyString& target){
    if(!str || target.empty()) return -1;

    int i = 0;
    while(str[i] != '\0'){
        int j = 0;
        while(target.at(j) != '\0' && str[i+j] == target.at(j)){
        }
        if(target.at(j) == '\0'){
            return i;
        }
        i++;
    }
    return -1;
}
size_t MyString::length() const{
    return len;
}
size_t MyString::size() const{
    return len;
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
const char* MyString::data(){
    return str;
}

MyString& MyString::operator+=(const MyString& other){
    int newLength = other.length() + len;
    char* tmp = new char[len+1];
    strcpy(tmp, str);
    delete[] str;

    str = new char[newLength+1];

    for(int i = 0;i<len;i++){
        str[i] = tmp[i];
    }
    for(int i = len;i<newLength;i++){
        str[i] = other.at(len-i);
    }
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


