//
// Created by Artem Bezruk on 08.08.2022.
//

#ifndef INC_11_HOMEWORK_TASK1_COMMANDS_H
#define INC_11_HOMEWORK_TASK1_COMMANDS_H

#include <iostream>
#include <map>
#include <filesystem>
#include <string>

std::string getCommandString(std::string &userInputConsole);
int getCommandCode(std::string commandString);
std::filesystem::path getAbsolutePath(std::string userInputConsole);

#endif //INC_11_HOMEWORK_TASK1_COMMANDS_H
