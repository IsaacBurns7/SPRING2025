#ifndef PASSWORD_FUNCTIONS_H
#define PASSWORD_FUNCTIONS_H

#include <string>

bool isValidPassword(const std::string& password);

void setNewPassword(const std::string& fileString);

bool authenticate(const std::string& passwordFileString);

#endif  // PASSWORD_FUCNTIONS_H