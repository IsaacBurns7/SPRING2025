// [7] (∗2.5) Write a program that strips comments out of a C++ program. That is, read from cin,
// remove both // comments and /∗ ∗/ comments, and write the result to cout. Do not worry
// about making the layout of the output look nice (that would be another, and much harder,
// exercise). Do not worry about incorrect programs. Beware of //, /∗, and ∗/ in comments,
// strings, and character constants.

//
/*
//
*/
/**/

#include <iostream>
#include <fstream>
#include <string>
using std::string, std::ifstream, std::cout;

int main(){
    string file = "./main.cpp";
    std::ifstream ifs(file);
    string line;
    while(std::getline(ifs, line)){
        cout << line << '\n';
        for(const auto& ch : line){
            
        }
    }
}