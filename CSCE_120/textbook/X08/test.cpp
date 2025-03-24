#include <vector>
#include <iostream>
#include <string>

using std::string; 
using std::vector;

// template <class T>
// swap(T& a, T& b){
//     T tmp {a}; //copy constructor
//     a = b;
//     b = tmp;
// }

// template <class T>
// swap2(T& a, T& b){
//     T tmp {static_cast<T&&>(a)};
//     a = static_cast<T&&> b;
//     b = static_cast<T&&> tmp;
// }

class toyString{
    public:
        toyString(string str = ""){
            s = str;
        }
        toyString(const toyString& r){
            s = r.s;
        }
        toyString(toyString&& rr){
            s = rr.s;
        } 
        //so if i modify new does it modify old
        toyString operator+(toyString other){
            toyString res;
            res.s = s + other.s;
            return res;
        }
        toyString operator+(string other){
            toyString res;
            res.s = s + other;
            return res;
        }
        toyString add(string other){
            toyString res;
            res.s = s + other;
            return res;
        }
        string s;
    private:
        //string s;
};

int main(){
    toyString s {"test"};
    toyString s2 {s};
    toyString s4 {"found!"};
    toyString s3 {s + "tail"};
    toyString s5 {s2+s4};
    //s2 = s2 + s4;
    s.s = "qwe";
    s4.s = "ewr"; 

    char f = 12;
    char* p = &f;
    char& r = f;
    while (r){
        std::cout << ++r;
    }
    return *p;
}