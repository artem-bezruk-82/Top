//
// Created by Artem Bezruk on 08.08.2022.
//

#include "Navigation.h"

void changeDirectory(std::filesystem::path targetEntry) {
    if (std::filesystem::exists(targetEntry)) {
        std::filesystem::current_path(targetEntry);
    } else {
        std::cout << "Error - Navigation issue: Requested path does not exist" << std::endl;
    }
}

