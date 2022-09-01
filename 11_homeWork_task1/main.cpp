#include <iostream>
#include <filesystem>
#include "Commands.h"
#include "Navigation.h"
#include "DirectoriesHandling.h"


int main() {

    std::string userInputConsole;
    int commandCode{-1};
    while (commandCode != 0) {
        std::cout << "\nCurrent directory: " << std::filesystem::current_path().string() << std::endl;
        std::cout << "> $ ";
        getline(std::cin,userInputConsole);
        std::string commandString = getCommandString(userInputConsole);
        std::filesystem::path targetEntry = getAbsolutePath(userInputConsole);
        commandCode = getCommandCode(commandString);
        switch (commandCode) {
            case -1:
                std::cout << "Error: Command not found" << std::endl;
                break;
            case 1:
                listDirectoryEntries(targetEntry);
                break;
            case 2:
                changeDirectory(targetEntry);
                break;
            case 3:
                makeDirectory(targetEntry);
                break;
            case 4:
                createFile(targetEntry);
                break;
            case 5:
                deleteEntry(targetEntry);
                break;
            case 6:
                copyEntry(targetEntry);
                break;
            case 7:
                renameEntry(targetEntry);
                break;
            case 8:
                searchEntry(targetEntry);
                break;
        }
    }
    return 0;
}
