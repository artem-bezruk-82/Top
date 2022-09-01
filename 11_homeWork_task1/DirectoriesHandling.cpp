//
// Created by Artem Bezruk on 10.08.2022.
//

#include "DirectoriesHandling.h"

std::string demoStatus(std::filesystem::file_status s)
{
    switch(s.type())
    {
        case std::filesystem::file_type::none: return " has `not-evaluated-yet` type"; break;
        case std::filesystem::file_type::not_found: return " does not exist"; break;
        case std::filesystem::file_type::regular: return " regular file"; break;
        case std::filesystem::file_type::directory: return " directory"; break;
        case std::filesystem::file_type::symlink: return " symlink"; break;
        case std::filesystem::file_type::block: return " block device"; break;
        case std::filesystem::file_type::character: return " character device"; break;
        case std::filesystem::file_type::fifo: return " named IPC pipe"; break;
        case std::filesystem::file_type::socket: return " named IPC socket"; break;
        case std::filesystem::file_type::unknown: return " `unknown` type"; break;
        default: return " `implementation-defined` type"; break;
    }
}

size_t getDirectorySize(std::filesystem::directory_entry &directoryEntry){
    size_t entrySize{0};
    for (auto const& dirEntry : std::filesystem::recursive_directory_iterator{directoryEntry})
    {
        if (dirEntry.is_regular_file()) {
            entrySize += dirEntry.file_size();
        }
    }
    return entrySize;
}

std::string getSizeString(std::filesystem::directory_entry directoryEntry){
    size_t entrySize{0};
    std::string sizeUnit{"B"};
    if (std::filesystem::is_regular_file(directoryEntry)) {
        entrySize = directoryEntry.file_size();
    }
    if (std::filesystem::is_directory(directoryEntry)) {
        entrySize = getDirectorySize(directoryEntry);
    }
    if (entrySize > 1073741824) {
        entrySize /= 1073741824;
        sizeUnit = "GiB";
    }
    if (entrySize > 1048576) {
        entrySize /= 1048576;
        sizeUnit = "MiB";
    }
    if (entrySize > 1024) {
        entrySize /= 1024;
        sizeUnit = "KiB";
    }
    return std::to_string(entrySize) + sizeUnit;
}

void listDirectoryEntries(std::filesystem::path targetEntry) {
    if (std::filesystem::exists(targetEntry)) {
        std::filesystem::directory_entry directoryEntry{targetEntry};
        if (directoryEntry.is_directory()) {
            for (auto const& dirEntry : std::filesystem::directory_iterator{directoryEntry})
            {
                std::cout << dirEntry.path().filename().string() << " " << "\t"
                << demoStatus(std::filesystem::status(dirEntry)) << " " << "\t"
                << getSizeString(dirEntry) << std::endl;
            }
        } else {
            std::cout << "Error - Navigation issue: Requested path is not a directory" << std::endl;
        }
    } else {
        std::cout << "Error - Navigation issue: Requested path does not exist" << std::endl;
    }
}

void makeDirectory(std::filesystem::path targetEntry) {
    std::filesystem::create_directories(targetEntry);
    std::cout << (std::filesystem::exists(targetEntry) ? "directory has been created" : "directory creation failed") << std::endl;
}

void createFile(std::filesystem::path targetEntry) {
        std::ofstream file(targetEntry);
        std::cout << (std::filesystem::exists(targetEntry) ? "file has been created" : "file creation failed") << std::endl;
}

void deleteEntry(std::filesystem::path targetEntry) {
    if (targetEntry != std::filesystem::current_path()) {
        if (std::filesystem::exists(targetEntry)) {
            try {
                std::filesystem::remove(targetEntry);
            }
            catch (std::filesystem::filesystem_error const& exception) {
                std::cout << exception.what() << std::endl;
            }
            std::cout << (!std::filesystem::exists(targetEntry) ? "Object has been deleted" : "Object deletion failed") << std::endl;
        } else {
            std::cout << "Object does not exist" << std::endl;
        }
    }
}

void copyFile(std::filesystem::path sourcePath, std::filesystem::path destinationPath){
    if (sourcePath.parent_path().string() == destinationPath.string()) {
        destinationPath = destinationPath/("Copy_" + sourcePath.filename().string());
        if (std::filesystem::exists(destinationPath)) {
            destinationPath.replace_filename("Copy_" + destinationPath.filename().string());
        }
    } else {
        destinationPath = destinationPath/(sourcePath.filename().string());
    }
    std::filesystem::copy(sourcePath, destinationPath, std::filesystem::copy_options::update_existing);
}

void copyDirectory(std::filesystem::path sourcePath, std::filesystem::path destinationPath){
    destinationPath = destinationPath/(sourcePath.string().substr(sourcePath.string().rfind("/") + 1));
    const auto copyOptions = std::filesystem::copy_options::update_existing
                             | std::filesystem::copy_options::recursive;
    std::filesystem::copy(sourcePath,destinationPath,copyOptions);
}

void copyEntry(std::filesystem::path sourcePath){
    if (std::filesystem::exists(sourcePath)) {
        std::string destination;
        std::cout << "Please enter destination folder" << std::endl;
        getline(std::cin,destination);
        std::filesystem::path destinationPath{getAbsolutePath(destination)};
        if (std::filesystem::exists(destinationPath) && std::filesystem::is_directory(destinationPath)) {
            try {
                if (std::filesystem::is_directory(sourcePath)) {
                    copyDirectory(sourcePath, destinationPath);
                } else {
                    copyFile(sourcePath,destinationPath);
                }
            }
            catch (std::filesystem::filesystem_error const& exception) {
                std::cout << exception.what() << std::endl;
            }
        } else {
            std::cout << "Destination object does not exist" << std::endl;
        }
    } else {
        std::cout << "Source object does not exist" << std::endl;
    }
}

void renameEntry(std::filesystem::path sourcePath) {
    if (std::filesystem::exists(sourcePath)) {
        std::string destination;
        std::cout << "Please enter destination folder to remove/rename entry " << std::endl;
        getline(std::cin,destination);
        std::filesystem::path destinationPath{getAbsolutePath(destination)};
        if (std::filesystem::is_directory(sourcePath)) {
            destinationPath = destinationPath/(sourcePath.filename());
        }
        if (std::filesystem::exists(destinationPath)) {
            destinationPath.replace_filename("Copy_" + destinationPath.filename().string());
        }
        try {
            std::filesystem::rename(sourcePath, destinationPath);
        }
        catch (std::filesystem::filesystem_error const& exception) {
            std::cout << exception.what() << std::endl;
        }
    } else {
        std::cout << "Source object does not exist" << std::endl;
    }
}

void searchEntry(std::filesystem::path targetEntry) {
    if (std::filesystem::exists(targetEntry)) {
        std::filesystem::directory_entry directoryEntry{targetEntry};
        if (directoryEntry.is_directory()) {
            std::cout << "Please enter searching mask" << std::endl;
            std::string searchingMask;
            getline(std::cin, searchingMask);
            if (searchingMask.length() > 0) {
                for (auto const& dirEntry : std::filesystem::recursive_directory_iterator{directoryEntry})
                {
                    if (dirEntry.path().filename().string().find(searchingMask) != std::string::npos) {
                        std::cout << dirEntry.path().filename().string() << " " << "\t"
                                  << demoStatus(std::filesystem::status(dirEntry)) << " " << "\t"
                                  << getSizeString(dirEntry) << " " << "\t"
                                  << dirEntry.path().string() << std::endl;
                    }
                }
            } else {
                std::cout << "Error - Searching issue: Searching criteria not defined" << std::endl;
            }

        } else {
            std::cout << "Error - Navigation issue: Requested path is not a directory" << std::endl;
        }
    } else {
        std::cout << "Error - Navigation issue: Requested path does not exist" << std::endl;
    }
}