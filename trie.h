#include <string>
#include <iostream>
#include <fstream>

struct TrieNode {
    public:
        TrieNode(char n, bool end, std::string info = "");
    private:
        char data;
        bool endpoint;
        std::string information;
        TrieNode* children[128];
    friend class Trie;
};

class Trie {
    private:
        TrieNode* root; // A pointer to the root of the trie
        TrieNode* insert(TrieNode root, std::string s); // Recursive insert
        void dictionary(TrieNode* root, std::ostream &os, std::string delim);
        void remove(TrieNode* node, std::string s); // Recursive remove
        bool hasChildren(TrieNode* node); // helper function; returns true if a node has children
        void generate_dot_file(TrieNode* node, std::ostream &os); // Recursive generate
        TrieNode* find_terminal(std::string s); // Find's terminal node if it exists

    public:
        Trie(); // Default constructor
        void insert(std::string); // Add a word to the set
        void remove(std::string s); // Remove a word from the set
        bool contains(std::string s); // Check if s is a word in the set
        void dictionary(std::ostream &os = std::cout, std::string delim = "\n"); // Send entire dictionary to stream separate all words by delim
        void generate_dot_file(std::string fname); // Generates the DOT file used for representing the trie
        std::string get_information(std::string s); // Retrieves information about a string
        bool store_information(std::string s, std::string information); // Stores information in contact
};