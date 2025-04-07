#pragma once

#include <string>
#include <vector>

class WordGenerator {
public:
    static std::string get_random_word();
private:
    static std::vector<std::string> create_wordlist();
};