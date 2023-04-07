#include <string>
#include <iostream>

struct TrieNode {
    public:
        TrieNode(char n, bool end);
    private:
        char data;
        bool endpoint;
        TrieNode* children[128];
    friend class Trie;
};

class Trie {
    private:
        TrieNode* root; // A pointer to the root of the trie
        TrieNode* insert(TrieNode root, std::string s); // Recursive insert
        void dictionary(TrieNode* root, std::ostream os, std::string delim);
        void remove(TrieNode* node, std::string s);
        bool hasChildren(TrieNode* node); //helper function; returns true if a node has children

    public:
        Trie(); // Default constructor
        void insert(std::string); // Add a word to the set
        void remove(std::string s); // Remove a word from the set
        bool contains(std::string s); // Check if s is a word in the set
        void dictionary(std::ostream &os = std::cout, std::string delim = "\n"); // Send entire dictionary to stream separate all words by delim

};