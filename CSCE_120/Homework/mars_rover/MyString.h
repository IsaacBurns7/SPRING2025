// TODO: Implement this header file

#ifndef MYSTRING
#define MYSTRING

#include <fstream>

using std::istream, std::ostream;

class MyString{
    private:
        char* str; 
        size_t len;
        size_t cap;
    public:
        MyString();
        MyString(const char* c_arr);
        MyString(const MyString& other);
        bool empty();
        bool empty() const;
        void clear();
        size_t find(const MyString& target, size_t pos = 0) const;
        size_t length() const;
        size_t size() const;
        size_t capacity() const;
        char& at(size_t index);
        const char& at(size_t index) const;
        char& front();
        const char& front() const;
        const char* data() const; 

        MyString& operator+=(const MyString& other);
        MyString& operator=(const MyString& other);
        friend istream& operator>>(istream& in, MyString& obj); //may need to be friend
        friend ostream& operator<<(ostream& out, const MyString& obj);
        

        ~MyString();

};

#endif 