#include "Hangman.h"
#include "WordGenerator.h"

#include <iostream>

const std::string GALLOWS[10] {
    R"(
       |
       |
       |
       |
       |
       |
    ‾‾‾‾‾‾‾‾‾‾)",
    R"(
       |
       |
       |
       |
       |
      /|\
    ‾‾‾‾‾‾‾‾‾‾)",
    R"(
       |/‾‾‾
       |
       |
       |
       |
      /|\
    ‾‾‾‾‾‾‾‾‾‾)",
    R"(
       |/‾‾‾
       |    
       |    O
       |
       |
      /|\
    ‾‾‾‾‾‾‾‾‾‾)",
    R"(
       |/‾‾‾
       |    o
       |    O
       |
       |
      /|\
    ‾‾‾‾‾‾‾‾‾‾)",
    R"(
       |/‾‾‾
       |    o
       |   /O
       |
       |
      /|\
    ‾‾‾‾‾‾‾‾‾‾)",
    R"(
       |/‾‾‾
       |    o
       |   /O\
       |
       |
      /|\
    ‾‾‾‾‾‾‾‾‾‾)",
    R"(
       |/‾‾‾
       |    o
       |   /O\
       |   / 
       |
      /|\
    ‾‾‾‾‾‾‾‾‾‾)",
    R"(
       |/‾‾‾
       |    o
       |   /O\
       |   / \
       |
      /|\
    ‾‾‾‾‾‾‾‾‾‾)",
    R"(
       |/‾‾‾|
       |    o
       |   /O\
       |   / \
       |
      /|\
    ‾‾‾‾‾‾‾‾‾‾)"
};

Hangman::Hangman() : word(WordGenerator::get_random_word()), hidden_word(word.size(), '_') {}

Hangman::~Hangman() {}

char Hangman::get_letter() {
    while (true) {
        char letter;
        std::cout << "Enter letter: ";
        scanf("%c", &letter);
        while ((getchar()) != '\n');
        if (letter < 65 || letter > 122 || letter > 90 && letter < 97) {
            std::cout << "Invalid input! Try again.\n";
        }
        else {
            if (letter >= 65 && letter <= 90) {
                letter += 32;
            }
            return letter;
        }
    }
}

bool Hangman::check_used_letter(bool* used_letters, char& letter) {
    if (!used_letters[letter - 97]) {
        used_letters[letter - 97] = true;
        return true;
    }
    return false;
}

void Hangman::check_letter(char letter, int& attempt) {
    bool is_exists = false;
    for (int i = 0; i < word.size(); i++) {
        if (word[i] == letter) {
            hidden_word[i] = letter;
            is_exists = true;
        }
    }
    if(!is_exists) { // finish
        std::cout << GALLOWS[attempt] << "\n" << "This letter is not in the word. Try another one.\n";
        attempt++;
    }
    else {
        std::cout << "That's right! Open letter: " << letter << '\n';
    }
}

bool Hangman::is_word_guessed() {
    for (int i = 0; i < hidden_word[i]; i++) {
        if (hidden_word[i] == '_')
            return false;
    }
    return true;
}

void Hangman::play() {
    bool used_letters[26]{};
    int attempt = 0;
    std::cout << "word = " << word << "\n";
    while (!is_word_guessed()) {
        std::cout << "Guess the word: " << hidden_word << "\n";
        char letter = get_letter();
        if (check_used_letter(used_letters, letter)) {
            check_letter(letter, attempt);
            if(attempt == 10) {
                std::cout << "You lose!\nThe word is: " << word << "\n";
                return;
            }
        }
        else {
            std::cout <<"This letter is already used! Try again!\n";
        }
    }
    std::cout << "Congratulations! You won, the word is: " << hidden_word << "\n";
}