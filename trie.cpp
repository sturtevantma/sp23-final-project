#include "trie.h"

TrieNode::TrieNode(char n, bool end) {
    this->data = n;
    this->endpoint = end;
    for(int i = 0; i < 128; i++) {
        this->children[i] = nullptr;
    }
}

Trie::Trie() {
    this->root = new TrieNode(0, 0);
}

void Trie::dictionary(std::ostream &os, std::string delim) {
    this->dictionary(this->root, os, delim);
}

void Trie::dictionary(TrieNode* root, std::ostream &os, std::string delim) {
    if(root == nullptr) {
        return;
    }
    // If root is not NULL add it to the delimiter
    if(root->data != '\0') {
        delim += root->data;
    }
    // If root is an endpoint push delim to the stream
    if(root->endpoint) {
        os << delim;
    }
    // Loop through all children and recursively call this method
    for(int i = 0; i < 128; i++) {
        dictionary(root->children[i], os, delim);
    }
}