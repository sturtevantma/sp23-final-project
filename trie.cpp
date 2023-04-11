#include "trie.h"

TrieNode::TrieNode(char n, bool end, std::string info) {
    this->data = n;
    this->endpoint = end;
    this->information = info;
    for(int i = 0; i < 128; i++) {
        this->children[i] = nullptr;
    }
}

Trie::Trie() {
    this->root = new TrieNode(0, 0);
}

// Write set to output stream (defaults to cout)
void Trie::dictionary(std::ostream &os, std::string delim) {
    this->dictionary(this->root, os, delim);
}

// Checks if a string s is in the set
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

// Private method to recursively send contents of the set to an output stream
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

// Private function removes nodes recursively
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

// Returns true|false based on whether a node has at least one child.
bool Trie::hasChildren(TrieNode* node) {
    for (int i = 0; i < 128; i++) {
        if (node->children[i] != nullptr) {
            return true;
        }
    }
    return false;
}

// Add a string to the set
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

// Remove a string from the set
void Trie::remove(std::string s) {
    remove(root, s);
}

// A public function for the user to generate a dot file of their trie
void Trie::generate_dot_file(std::string fname) {
    std::ofstream file;
    file.open(fname);
    if(!file.is_open()) {
        return;
    }

    file << "digraph Trie {\n";

    generate_dot_file(this->root, file);

    file << "\n}";

}

// A recursive function that creates most of the DOT file
void Trie::generate_dot_file(TrieNode* node, std::ostream &os) {
    // If null do not append to file
    if(node == nullptr) {
        return;
    }
    // root_key = memory address of the node, used as a key to identify nodes in the dot file
    std::string root_key = std::to_string((long long)node);

    // create node label and color
    os << root_key << "[label=";
    if(node == this->root) {
        os << "root";
    } else {
        os << '"' << node->data << '"';
    }

    os << ",color=";
    if(node->endpoint) {
        os << "red";
    } else {
        os << "black";
    }
    os << "]\n\n";

    // Add graphic for pointing at child nodes
    for(int i = 0; i < 128; i++) {
        if(node->children[i] != nullptr) {
            os << root_key << "->" << std::to_string((long long)node->children[i]) << "\n";
        }
    }

    // Call for all children
    for(int i = 0; i < 128; i++) {
        generate_dot_file(node->children[i], os);
    }
    return;
}

std::string Trie::get_information(std::string s) {
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
            throw "Contact not found";
            return "\0";
        }
    }
    //If we looped over the entire word then we check if the node is an endpoint to return the information
    if (temp->endpoint) {
        return temp->information;
    }
    throw "Contact not found";
    return "\0";
}   