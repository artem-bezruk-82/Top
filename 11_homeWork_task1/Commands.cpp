//
// Created by Artem Bezruk on 09.08.2022.
//

#include "Commands.h"

std::string getCommandString(std::string &userInputConsole){
    int position{0};
    while (position < userInputConsole.length() && !isalpha(userInputConsole[position])) {
        position++;
    }
    int commandStartPosition{position};
    while (position < userInputConsole.length() && isalpha(userInputConsole[position])) {
        position++;
    }
    int commandLength{position};
    std::string commandString{userInputConsole.substr(commandStartPosition, commandLength)};
    userInputConsole.erase(userInputConsole.cbegin(),userInputConsole.cbegin() + commandLength);
    return commandString;
}

int getCommandCode(std::string commandString) {
    std::map<std::string, int> commands{
             {"end",0}
            ,{"ls",1}
            ,{"cd",2}
            ,{"mkdir",3}
            ,{"touch", 4}
            ,{"rm",5}
            ,{"cp",6}
            ,{"mv",7}
            ,{"fd",8}
    };
    std::transform(commandString.begin(), commandString.end(), commandString.begin(), ::tolower);
    auto search = commands.find(commandString);
    if (search != commands.end()) {
        return search->second;
    } else {
        return -1;
    }

}

std::filesystem::path getAbsolutePath(std::string userInputConsole) {
    int targetEntryStart{0};
    while (targetEntryStart < userInputConsole.length() && isspace(userInputConsole[targetEntryStart])) {
        targetEntryStart++;
    }
    int targetEntryEnd = userInputConsole.length() - 1;
    while (targetEntryEnd > targetEntryStart && isspace(userInputConsole[targetEntryEnd])) {
        targetEntryEnd--;
    }
    std::string targetEntry{userInputConsole.substr(targetEntryStart, targetEntryEnd - targetEntryStart + 1)};
    std::filesystem::path absolutePath{ std::filesystem::current_path().string()};
    if (targetEntry.length() > 0) {
        absolutePath = absolutePath/targetEntry;
    }
    return absolutePath;
}
