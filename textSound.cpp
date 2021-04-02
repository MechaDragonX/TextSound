#include <fstream>
#include <iostream>
#include <vector>

// Convert CRLF line endings to LF
void dos2Unix(std::vector<int>& fileContents) {
    for(int i = 0; i < fileContents.size(); i++) {
        if(fileContents[i] == 13 && fileContents[i + 1] == 10)
            /*
                Remove the current element from the vector.
                Since the size has decreased by 1, i will now point to the index of the next character.
                When incremented, it will then skip the next character.
                This is not a big deal since we are looking for pairs of "\r\n", thus skipping '\n' is not a big deal.
            */
            fileContents.erase(fileContents.begin() + i);
    }
}

int main() {
    std::ifstream inStream("tests/test_text.txt");
    std::ofstream outStream;

    if(!inStream.good()) {
        inStream.close();
        std::cerr << "File does not exist." << std::endl;
        return 1;
    }

    outStream.open("tests/test_text.txt", std::ios::app);

    std::vector<int> characterCodes;
    char current;
    int currentNum;
    while(!inStream.eof()) {
        current = inStream.get();
        if(current != EOF) {
            currentNum = (int)current;
            characterCodes.push_back(currentNum);
        }
    }

    dos2Unix(characterCodes);
    outStream << std::endl;
    for(int num : characterCodes)
        outStream << num << std::endl;
    
    return 0;
}
