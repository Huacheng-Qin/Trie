#ifndef TRIENODE_HPP
#define TRIENODE_HPP
#include <iostream>

class TrieNode {
    public:
    TrieNode();
    ~TrieNode();
    bool Insert(std::string key);
    bool Erase(std::string key);
    bool Find(std::string key) const;
    void Print(std::string prefix = "", int i = 0) const;
    void Clear();
    
    private:
    std::string PrintChildren(std::string word) const;

    TrieNode* m_children[26];
    bool m_end;
    bool m_empty;
};

#endif
