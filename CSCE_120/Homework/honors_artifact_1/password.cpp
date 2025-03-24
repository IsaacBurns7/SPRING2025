#include <iostream>
#include <string>
#include <fstream>
#include "password_functions.h"




int main(){
    setNewPassword("passwords.txt");

    while (true){
        try{
            char answer; 
            if (authenticate("passwords.txt")) {
                std::cout << "Password accepted!\n";
                std::cout << "Would you like to set a new password y/n: "; 
                std::cin >> answer;
                std::cin.ignore(); 
                if (answer == 'y'){
                    setNewPassword("passwords.txt"); 
                }
                else if (answer == 'n'){
                    break; 
                }
                else {
                    std::cout << "Error, ending program" << std::endl;  
                }
            }
            else {
                std::cout << "Password denied!\n";
                std::cout << "Would you like to set a new password y/n or try again t: "; 
                std::cin >> answer;  
                std::cin.ignore();
                if (answer == 'y'){
                    setNewPassword("passwords.txt"); 
                }
                else if (answer == 'n'){
                    break; 
                }
                else if (answer == 't'){
                    continue; 
                }
                else {
                    std::cout << "Error, ending program" << std::endl;  
                }
            }
        } catch(std::invalid_argument e){
            std::cout << e.what() << std::endl;
            break;
        }
    } 
    return 0;
}