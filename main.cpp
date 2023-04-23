#include "trie.h"
#include <fstream>
#include <sstream>

std::string get_name(std::string &s) {
    std::string temp = "";
    while(std::cin >> temp) {
        s += temp;
    }
}

int main(int argc, char* argv[]) {

    Trie trie_;
    std::string ifname = "", ofname = "";

    if(argc > 1)
        ifname = argv[1];
    if(argc > 2)
        ofname = argv[2];


    std::ifstream in_file;
    in_file.open(ifname);

    std::string line;
    while(std::getline(in_file, line)) {

        // Seperate name from contact info
        std::string name, info;
        std::stringstream line_stream(line);
        std::getline(line_stream, name, '"');
        std::getline(line_stream, name, '"');
        std::getline(line_stream, info, '"');
        std::getline(line_stream, info, '"');

        // Insert contact into trie
        trie_.insert(name, info);
    }

    // Let user interact with contacts
    while(true) {
        std::cout << "\nPress any key to continue...\n";
        char cont;
        std::cin >> cont;
        // Prompt user for command
        std::cout << "\nEnter a command: \n" <<
                    "[1] - Fetch Contact\n" <<
                    "[2] - Add a Contact\n" <<
                    "[3] - Remove Contact\n" <<
                    "[4] - Check if Contact Exists\n" <<
                    "[5] - Print Contact List\n" <<
                    "[6] - Edit Contact Information\n" <<
                    "[7] - Create trie DOT file\n" <<
                    "[0] - Quit\n" <<
                    "Selection: ";

        int selection = 0;
        std::string in;
        std::cin >> in;
        try {
            selection = std::stoi(in);
        } catch(...) {
            std::cout << "Please enter a number [0-7], you entered " + in + '\n';
            continue;
        }
        std::cin.clear();
        while (std::cin.get() != '\n')
        {
            continue;
        }
        // Parse input
        std::string name;
        std::string info;
        switch(selection) {
//            default:
//                std::cout << "\nInvalid option please choose a number [0-7]\n";
//                break;
            case 0:
                goto end;
                break;
            case 1:
                std::cout << "Enter a contact name: ";
                std::getline(std::cin, name);
                if(trie_.contains(name)) {
                    std::cout << "\n" << name << ":\n" << trie_.get_information(name) << "\n";
                } else {
                    std::cout << "\nContact does not exist\n";
                }
                continue;
            case 2:
                std::cout << "Enter a contact name: ";
                std::getline(std::cin, name);
                if(trie_.contains(name)) {
                    std::cout << "\nContact already exists\n";
                } else {
                    std::cout << "\nEnter contact info: ";
                    std::getline(std::cin, info);
                    trie_.insert(name, info);
                    std::cout << "Contact Added\n";
                }
                break;
            case 3:
                std::cout << "Enter a contact name: ";
                std::getline(std::cin, name);
                if(trie_.contains(name)) {
                    trie_.remove(name);
                    std::cout << "\nContact Removed\n";
                } else {
                    std::cout << "\nContact does not exist\n";
                }
                break;
            case 4:
                std::cout << "Enter a contact name: ";
                std::getline(std::cin, name);
                if(trie_.contains(name)) {
                    std::cout << "\nContact exists\n";
                } else {
                    std::cout << "\nContact does not exist\n";
                }
                break;
            case 5:
                trie_.dictionary();
                break;
            case 6:
                std::cout << "Enter a contact name: ";
                std::getline(std::cin, name);
                if(trie_.contains(name)) {
                    std::cout << "\nEnter contact info: ";
                    std::getline(std::cin, info);
                    trie_.store_information(name, info);
                    std::cout << "\nContact updated\n";
                } else {
                    std::cout << "\nContact does not exist\n";
                }
                break;
            case 7:
                if(ofname == "") {
                    std::cout << "\nNo output file provided, generating...";
                    ofname = ifname + ".DOT";
                }
                trie_.generate_dot_file(ofname);
                std::cout << "\n File created: " << ofname << "\n";
                break;

        }

    }

    end:
    return 0;
}