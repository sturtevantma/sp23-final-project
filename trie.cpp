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

void Trie::remove(TrieNode* node, std::string s) {
    if (s.empty()) { // base case: end of string
        node->endpoint = false;
        if (!hasChildren(node)) { // node has no children
            delete node;
            node = nullptr;
        }
        return;
    }

    char c = s[0];
    if (node->children[c] != nullptr) { // character found
        remove(node->children[c], s.substr(1));
        if (!hasChildren(node->children[c]) && !node->children[c]->endpoint) { // child has no children and is not an endpoint
            delete node->children[c];
            node->children[c] = nullptr;
        }
    }

    if (!hasChildren(node) && !node->endpoint) { // node has no children and is not an endpoint
        delete node;
        node = nullptr;
    }
}

bool Trie::hasChildren(TrieNode* node) {
    for (int i = 0; i < 128; i++) {
        if (node->children[i] != nullptr) {
            return true;
        }
    }
    return false;
}

void Trie::insert(std::string s){
    // Take in string as s
    TrieNode* temp = this->root;
    // Loop through s
    for(int i = 0; i < s.length(); i++){
        char x = s.at(i);
        // if child is not NULL:
        if(temp->children[x]){
            temp = temp->children[x];
            // if child IS NULL,
        }else{
            // Create a new node with letter
            TrieNode* newNode = new TrieNode(x, false);
            // Make new node a child of temp
            temp->children[x] = newNode;
            // Set temp to the ^new Node^ and continue
            temp = newNode;
        }
    }

    // Set the final node as an endpoint
    temp->endpoint = true;
}

void Trie::remove(std::string s) {
    remove(root, s);
}