// TODO: Implement this header file

#ifndef MYSTRING
#define MYSTRING

#include <fstream>

using std::istream, std::ostream;

class MyString{
    private:
        char* str; 
        size_t len;
    public:
        MyString();
        MyString(const char* c_arr);
        MyString(MyString& other);
        bool empty();
        void clear();
        size_t find(MyString& target);
        size_t length() const;
        size_t size() const;
        char& at(size_t index);
        const char& at(size_t index) const;
        char& front();
        const char& front() const;
        const char* data(); 

        MyString& operator+=(const MyString& other);
        friend istream& operator>>(istream& in, MyString& obj); //may need to be friend
        friend ostream& operator<<(ostream& out, const MyString& obj);
        

        ~MyString();

};

#endif 