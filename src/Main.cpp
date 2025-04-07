#include "Hangman.h"

#include <iostream>

int main() {
    system("chcp 65001 > nul");
    try {
        Hangman hangman;
        hangman.play();
    }
    catch(const std::exception& e) {
        std::cerr << "Dictionary is empty or file not found!\n";
        return 1; // open file browser
    }
    return 0;
}