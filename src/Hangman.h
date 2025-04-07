#pragma once

#include <string>
#include <iostream>

class Hangman {
public:
    Hangman();
    ~Hangman();

    void play();
private:
    char get_letter();
    bool check_used_letter(bool* used_letters, char& letter);
    void check_letter(char letter, int& attempt);
    bool is_word_guessed();

    std::string word;
    std::string hidden_word;
};