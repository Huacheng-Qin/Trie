#include <iostream>
#include "TrieNode.hpp"

static bool s_flag = false;

TrieNode::TrieNode():
m_end(false), m_empty(true) {
    for (int i = 0; i < 26; i++) {
        m_children[i] = nullptr;
    }
}

TrieNode::~TrieNode() {
    Clear();
}

bool TrieNode::Insert(std::string key) {
    if (key.empty()) {
        if (m_end) {
            return false;
        } else {
            m_end = true;
            return true;
        }
    }

    int branch = key[key.length() - 1] - 'a';
    key.pop_back();

    TrieNode* next = m_children[branch];
    if (!next) {
        next = new TrieNode();
        m_children[branch] = next;
        if (m_empty) {
            m_empty = false;
        }
    }

    return next->Insert(std::move(key));
}

bool TrieNode::Erase(std::string key) {
    if (key.empty()) {
        return false;
    }

    int branch = key[key.length() - 1] - 'a';
    key.pop_back();

    TrieNode* next = m_children[branch];
    if (!next) {
        return false;
    }
    if (key.empty()) {
        if (next->m_end) {
            if (next->m_empty) {
                delete next;
                m_children[branch] = nullptr;

                for (int i = 0; i < 26; i++) {
                    if (m_children[i]) {
                        return true;
                    }
                }
                m_empty = true;
            } else {
                next->m_end = false;
            }
            return true;
        }
        return false;
    }

    if (next->Erase(std::move(key))) {
        if (next->m_empty && !next->m_end) {
            delete next;
            m_children[branch] = nullptr;
            
            for (int i = 0; i < 26; i++) {
                if (m_children[i]) {
                    return true;
                }
            }
            m_empty = true;
        }
        return true;
    }

    return false;
}

bool TrieNode::Find(std::string key) const {
    if (key.empty()) {
        if (m_end) {
            return true;
        }
        return false;
    }

    int branch = key[key.length() - 1] - 'a';
    key.pop_back();

    TrieNode* next = m_children[branch];

    if (next) {
        return next->Find(std::move(key));
    }

    return false;
}

void TrieNode::Print(std::string prefix, int i) const {
    if (i == prefix.length()) {
        s_flag = false;
        PrintChildren(std::move(prefix));
        if (s_flag) {
            std::cout << std::endl;
        }
    } else if (i < prefix.length()) {
        int branch = prefix[i] - 'a';
        TrieNode* next = m_children[branch];
        if (next) {
            next->Print(std::move(prefix), std::move(++i));
        }
    }
}

std::string TrieNode::PrintChildren(std::string word) const {
    if (m_end) {
        if (s_flag) {
            std::cout << " ";
        } else {
            s_flag = true;
        }
        std::cout << word;
    }

    if (!m_empty) {
        for (char c = 'a'; c <= 'z'; c++) {
            TrieNode* next = m_children[c - 'a'];
            if (next) {
                word += c;
                word = next->PrintChildren(std::move(word));
            }
        }
    }

    if (!word.empty()) {
        word.pop_back();
    }
    return word;
}

void TrieNode::Clear() {
    for (int i = 0; i < 26; i++) {
        if (m_children[i]) {
            delete m_children[i];
            m_children[i] = nullptr;
        }
    }
    m_empty = true;
}
