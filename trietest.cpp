#include <iostream>
#include <string>
#include "Trie.hpp"

int main() {
    Trie trie;
    std::string input;

    do {
        std::getline(std::cin, input);
    } while (trie.Parse(std::move(input)));

    return 0;
}
