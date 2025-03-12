#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stdio.h>

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

std::string get_random_word(std::string*& words, int& size) {
    std::srand(std::time(0));
    int randomIndex = std::rand() % size;
    return words[randomIndex];
}

char get_letter() {
    while (true) {
        char letter = 'p';
        // std::cout << "Address of letter: " << *(char*)(void*)&letter << std::endl;
        std::cout << "Enter letter: ";
        scanf("%c", &letter); // \n in file - how will it be read?
        // std::cout << "Address of letter: " << &letter << std::endl;
        // printf("Character entered is: %p\n", &letter);
        while ((getchar()) != '\n');
        if (letter < 65 || letter > 122 || letter > 90 && letter < 97) {
            std::cout << "Invalid input! Try again.\n"; 
            // continue; ?
        }
        else {
            if (letter >= 65 && letter <= 90) {
                letter += 32;
            }
            return letter;
        }
    }
}

bool check_used_letter(bool* used_letters, char& letter) {
    if (!used_letters[letter - 97]) {
        used_letters[letter - 97] = true;
        // used_letters[letter - 97] = !used_letters[letter - 97]; 
        //this is possible but not as obvious as 120
        return true;
    }
    return false;
}

void check_letter(std::string& initial_word, char* hidden_word, char letter, int& attempt) { //why is copy better
    bool is_exists = false;
    for (int i = 0; i < initial_word.size(); i++) {
        if (initial_word[i] == letter) {
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

bool is_word_guessed(char* hidden_word) {
    for (int i = 0; i < hidden_word[i] != '\0'; i++) {
        if (hidden_word[i] == '_')
            return false;
    }
    return true;
}

void init_hidden_word(std::string& initial_word, char*& hidden_word) {
    hidden_word = new char[initial_word.size() + 1];
    for (int i = 0; i < initial_word.size(); i++) {
        hidden_word[i] = '_';
    }
    hidden_word[initial_word.size()] = '\0';
    //bc string is printed at once not symbol by symbol
}

void play(std::string& riddle_word) {
    bool used_letters[26]{}; //hashset
    char* hidden_word;
    int attempt = 0;
    init_hidden_word(riddle_word, hidden_word);
    while (!is_word_guessed(hidden_word)) {
        std::cout << "Guess the word: " << hidden_word << "\n";
        char letter = get_letter();
        if (check_used_letter(used_letters, letter)) {
            check_letter(riddle_word, hidden_word, letter, attempt);
            if(attempt == 10) {
            std::cout << "You lose!\nThe word is: " << riddle_word << "\n";
            return;
            }
        }
        else {
            std::cout <<"This letter is already used! Try again!\n";
        }
    }
    std::cout << "Congratulations! You won, the word is: " << hidden_word << "\n";
}

int main() {
    FILE* vocab;
    vocab = fopen("vocab.txt", "w");
    fprintf(vocab, "cherry\npotato\nmustard\nfood\ndelicious\n");
    fclose(vocab);
    vocab = fopen("vocab.txt", "r");
    char readerString[100];
    int count = 0;
    while(fgets(readerString, 100, vocab)) {
        printf("%s", readerString);
        count++;
    }
    printf("count: %d\n", count);
    fclose(vocab);
    int size = 5;
    std::string* words2 = new std::string[size]{"cherry", "potato", "mustard", "food", "delicious"};
    std::string word = get_random_word(words2, size);
    play(word);
}