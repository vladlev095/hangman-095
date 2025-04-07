#include "WordGenerator.h"

#include <ctime>
#include <fstream>
#include <unordered_set>
#include <exception>

std::vector<std::string> WordGenerator::create_wordlist() {
    std::unordered_set<std::string> dictionary;
    std::ifstream file("..\\words.txt");

    std::string word;
    while (file >> word) {
        dictionary.insert(word);
    }
    file.close();

    if (dictionary.empty()) {
        throw std::exception();
    }
    std::vector<std::string> wordList(dictionary.begin(), dictionary.end());
    return wordList;
    // std::cout << "Wordlist size: " << wordList.size() << "\n";
}

std::string WordGenerator::get_random_word() {
    std::vector<std::string> wordList = create_wordlist();
    std::srand(std::time(0));
    int randomIndex = std::rand() % wordList.size();
    return wordList[randomIndex];
}