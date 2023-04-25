# Final-Project-SP23
A Trie algorithm for CSC 212
Group members:
Henry Czerwinski,
Matthew Sturtevant,
Andrew Bilodeau,
Dean Geraci

# Summary and Repo Address

Retrieving contact information via Tries by inputing keys that are strings.


Repo Address: https://github.com/sturtevantma/sp23-final-project

# Documentation

### TrieNode
Represent ending of keys and storing potential information on end point nodes  
`TrieNode`  
The name of the category  
`TrieNode::data`  
The category's weight for your course grade   
`TrieNode::endpoint`  
A vector of pairs containing all assignments and the achieved grades  
`TrieNode::information`  
The value that we are retrieving when we input a key
`TrieNode::children`  
128 potential children represntative of the ASCII Value Table

### Trie
Storing and retrieving information as well as inserting and removing keys.  
`Trie::root`  
A pointer to the root of the trie  
`TrieNode::insert()`  
Recursively inserts a word  
`TrieNode::dictionary()`  
All the contacts in the list  
`TrieNode::remove()`  
Recursively removes a word  
`TrieNode::hasChildren()`  
Returns a float that contains your grade/100  
`TrieNode::generate_dot_file()`  
Recursive generate  
`TrieNode::find_terminal()`  
Find grade by assignment name  
`TrieNode::contains()`  
Check if s is a word in the set  
`TrieNode::get_information()`  
Retrieves information about a string  
`TrieNode::store_information()`  
Stores information in contact

### How to Compile  
When compiling, you need to type `g++ main.cpp trie.cpp`
To execute, type `./a.exe <input file name>`
To use the program follow the on screen prompt.

### How to Operate
The on screen prompt will ask you to enter any letter and to hit the enter key afterwards.  

Then the user will be asked to one of the numbers from 1-7, 0 is also an option and will end the program.  

[1] - Fetch Contact: User will be prompted to enter a name, then the corresponding contact information will be outputted to the user.  

[2] - Add a Contact: User will be prompted to enter a name and contact information. Both the name and contact information will be stores in the text.txt file.  

[3] - Remove Contact: User will be prompted to enter a name. Both the name and the corresponding contact information will be removed from the text.txt file.  

[4] - Check if Contact Exists: User will be prompted to enter a name. If the name is in the text.txt file "Contact exists" will be outputted, if not in the file "Contact does not exist" will be outputted.  

[5] - Print Contact List: Will print all of the names and corresponding contact information.  

[6] - Edit Contact Information: User will be prompted to enter a name. If the name is in the text.txt file "Enter contact info:" will be printed, then the user can input the new contact information. After inputting the new info, "Contact updated" will be printed. If the name is not in the file "Contact does not exist" will be printed.  

[7] - Create trie DOT file: Will create a visualized Trie containing the data in your contact list  

[0] - Quit: Entering 0 ends the program.  
