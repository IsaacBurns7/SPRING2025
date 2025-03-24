#include <iostream>
#include <string>
#include <fstream>
#include "password_functions.h"

bool isValidPassword(const std::string& password){
    if(password.length() < 8){
        return false;
    }
    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;

    for(const char ch: password){
        if (std::isupper(ch)) hasUpper = true;
        if (std::islower(ch)) hasLower = true;
        if (std::isdigit(ch)) hasDigit = true;
        if (std::ispunct(ch)) hasSpecial = true;
    }

    return hasUpper && hasLower && hasDigit && hasSpecial;
}

void setNewPassword(const std::string& fileString){
    std::ofstream outFile(fileString, std::ios::app);

    if(!outFile){
        throw std::invalid_argument("Error opening file!\n");
    }
    std::string password;
    std::cout << "Enter your permanent password: ";
    std::getline(std::cin, password);

    while(!isValidPassword(password)){
        std::cout << "Invalid password! It must be at least 8 characters long and contain "
                     "an uppercase letter, a lowercase letter, a number, and a special character.\n";
        std::cout << "Enter your permanent password: ";
        std::getline(std::cin, password);
    }
    outFile << password << '\n';
}


bool authenticate(const std::string& passwordFileString){
    std::ifstream passwordFile(passwordFileString);

    if(!passwordFile){
        throw std::invalid_argument("Error opening file!\n");
        return false; 
    }
    
    std::string currentPassword, enteredPassword;
    std::cout << "Input password: "; 
    std::getline(std::cin, enteredPassword); 
    while(std::getline(passwordFile, currentPassword)){
        if(enteredPassword == currentPassword){
            return true;
        }
    }
    return false;
}
