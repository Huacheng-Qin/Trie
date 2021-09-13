#ifndef TRIE_HPP
#define TRIE_HPP
#include <iostream>
#include "TrieNode.hpp"

class Trie {
    public:
    Trie();
    ~Trie();
    bool Parse(std::string input);

    private:
    void Insert(std::string word);
    void Erase(std::string word);
    void Search(std::string word) const;
    void Print(std::string prefix = "") const;
    void Empty() const;
    void Size() const;
    void Clear();

    TrieNode* m_root;
    std::size_t m_size;
};

#endif