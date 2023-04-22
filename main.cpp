#include "trie.h"
#include <fstream>
#include <sstream>

int main(int argc, char* argv[]) {

    Trie trie_;
    std::string ifname, ofname;

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

        // Prompt user for command
        std::cout << "Enter a command: \n" <<
                    "[1] - Fetch Contact\n" <<
                    "[2] - Add a Contact\n" <<
                    "[3] - Remove Contact\n" <<
                    "[4] - Check if Contact Exists\n" <<
                    "[5] - Print Contact List\n" <<
                    "[6] - Edit Contact Information\n" <<
                    "[7] - Create trie DOT file\n" <<
                    "[0] - Quit";

        int selection = 0;
        std::string in;
        std::cin >> in;
        try {
            selection = std::stoi(in);
        } catch(...) {
            std::cout << "Please enter a number [0-7], you entered " + in + '\n';
            continue;
        }

        // Parse input
        switch(selection) {
            case 0:
                goto end;
                break;
            case 1:
                std::string name;
                std::cout << "Enter a contact name: ";
                std::cin >> name;
                if(trie_.contains(name)) {
                    std::cout << "\n" << name << ":\n" << trie_.get_information(name) << "\n";
                } else {
                    std::cout << "Contact oes not exist\n";
                }

        }

    }

end:
}