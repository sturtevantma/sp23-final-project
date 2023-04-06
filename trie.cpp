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

bool Trie::contains(std::string s) {

    TrieNode* temp = this->root;
    //Loop over string 
    for (int i = 0; i < s.length(); i++) {
        //If the node has the child
        if (temp->children[s.at(i)]) {
            //Assign temp to the child and continue to next iteration
            temp = temp->children[s.at(i)];
            continue;
        }
        //Else if the child is never found then return false
        else if (!temp->children[s.at(i)]) {
            return false;
        }
    }
    //If we looped over the entire word then we check if the node is an endpoint to signal a valid word
    if (temp->endpoint) {
        return true;
    }
    return false;
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