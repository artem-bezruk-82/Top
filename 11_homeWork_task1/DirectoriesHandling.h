//
// Created by Artem Bezruk on 10.08.2022.
//

#ifndef INC_11_HOMEWORK_TASK1_DIRECTORIESHANDLING_H
#define INC_11_HOMEWORK_TASK1_DIRECTORIESHANDLING_H

#include <iostream>
#include <filesystem>
#include <fstream>
#include "Commands.h"

void listDirectoryEntries(std::filesystem::path targetEntry);
void makeDirectory(std::filesystem::path targetEntry);
void createFile(std::filesystem::path targetEntry);
void deleteEntry(std::filesystem::path targetEntry);
void copyDirectory(std::filesystem::path sourcePath, std::filesystem::path destinationPath);
void copyFile(std::filesystem::path sourcePath, std::filesystem::path destinationPath);
void copyDirectory(std::filesystem::path sourcePath, std::filesystem::path destinationPath);
void copyEntry(std::filesystem::path sourcePath);
void renameEntry(std::filesystem::path sourcePath);
void searchEntry(std::filesystem::path targetEntry);

#endif //INC_11_HOMEWORK_TASK1_DIRECTORIESHANDLING_H
