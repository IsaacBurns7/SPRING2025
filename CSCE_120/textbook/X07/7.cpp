#include <iostream>

int main(){
    for(char ch = 'a'; ch <= 'z'; ch++){
        int ch_num{ch};

        //so hex flag doesnt remain 
        std::ios oldState(nullptr);
        oldState.copyfmt(std::cout);

        std::cout << "value of " << ch << " in decimal: " << ch_num << std::endl;
        std::cout << "value of " << ch << " in hexidecimal: " << std::hex << ch_num << std::endl;

        std::cout.copyfmt(oldState);
    }
}