#include <iostream>
#include "Trie.hpp"
#include "illegal_exception.hpp"

static void Scan(const std::string& word) {
    for (std::size_t i = 0; i < word.length(); i++) {
        if (word[i] < 'a' || word[i] > 'z') {
            throw illegal_exception("illegal argument");
        }
    }
}

static void Reverse(std::string& word) {
    std::size_t front = 0, back = word.length() - 1;
    while (front < back) {
        char hold = word[front];
        word[front] = word[back];
        word[back] = hold;
        front++;
        back--;
    }
}

Trie::Trie():
    m_root(new TrieNode()), m_size(0) {}

Trie::~Trie() {
    if (m_root) {
        delete m_root;
    }
}

bool Trie::Parse(std::string input) {
    std::string command = input.substr(0, input.find_first_of(" "));
    input.erase(0, input.find_first_of(" ") + 1);

    try {
        if (command == "i") {
            Scan(input);
            Reverse(input);
            Insert(std::move(input));
        } else if (command == "e") {
            Scan(input);
            Reverse(input);
            Erase(std::move(input));
        } else if (command == "s") {
            Scan(input);
            Search(std::move(input));
        } else if (command == "print") {
            Print();
        } else if (command == "autocomplete") {
            input.pop_back();
            Scan(input);
            Print(std::move(input));
        } else if (command == "empty") {
            Empty();
        } else if (command == "clear") {
            Clear();
        } else if (command == "size") {
            Size();
        } else if (command == "exit") {
            return false;
        } else if (std::cin.eof()) {
            return false;
        }
    } catch(illegal_exception& e) {
        if (command != "autocomplete") {
            std::cout << e.what() << std::endl;
        }
    }
    return true;
}

void Trie::Insert(std::string word) {
    if (m_root->Insert(std::move(word))) {
        std::cout << "success" << std::endl;
        m_size++;
    } else {
        std::cout << "failure" << std::endl;
    }
}

void Trie::Erase(std::string word) {
    if (m_root->Erase(std::move(word))) {
        std::cout << "success" << std::endl;
        m_size--;
    } else {
        std::cout << "failure" << std::endl;
    }
}

void Trie::Search(std::string word) const {
    std::string target = word;
    Reverse(target);
    if (m_root->Find(std::move(target))) {
        std::cout << "found " << word << std::endl;
    } else {
        std::cout << "not found" << std::endl;
    }
}

void Trie::Print(std::string prefix) const {
    m_root->Print(std::move(prefix));
}

void Trie::Empty() const {
    std::cout << "empty " << (m_size == 0) << std::endl;
}

void Trie::Size() const {
    std::cout << "number of words is " << m_size << std::endl;
}

void Trie::Clear() {
    if (m_root) {
        m_root->Clear();
        m_size = 0;
    }
    std::cout << "success" << std::endl;
}
