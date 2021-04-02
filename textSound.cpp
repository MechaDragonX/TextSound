#include <fstream>
#include <iostream>
#include <vector>
#include <Windows.h>

/*
    Maximum frequency possibly 44.1kHz encoded audio  (such as CD's)
    Roughly half because of how the Nyquist-Shannon Theorem works
    20kHz is the maximum that most humans can hear
    Doubling and listening for more frequencies allows the sound to be converted to digital, passed through a low pass filter, and come out with the original sound exactly.
    More information can be found online.
*/
const double BAND_LIMIT_FREQ = 20000.0;
const double AMOUNT_OF_ASCII_CHARS = 177.0;

// Get a vector<int> of ASCII characers for each character in the file
std::vector<int> getCharacterCodes(std::ifstream& inStream) {
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
    return characterCodes;
}
// Get a vector<int> of ASCII characers for each character in the file
std::vector<int> getCharacterCodes(std::string input) {
    std::vector<int> characterCodes;
    int current;
    for(char chr : input) {
        if(chr != EOF) {
            current = (int)chr;
            characterCodes.push_back(current);
        }
    }
    return characterCodes;
}
// Convert CRLF line endings to LF
void dos2Unix(std::vector<int>& fileContents) {
    for(int i = 0; i < fileContents.size(); i++) {
        // 13 = \r; 10 = \n
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

    if(!inStream.good()) {
        inStream.close();
        std::cerr << "File does not exist." << std::endl;
        return 1;
    }

    std::vector<int> characterCodes = getCharacterCodes("0123456789");
    // std::ofstream outStream;

    // outStream.open("tests/test_text.txt", std::ios::app);
    dos2Unix(characterCodes);
    // outStream << std::endl;
    double ratio;
    double freq;
    for(int num : characterCodes) {
        // outStream << num << std::endl;
        std::cout << "ASCII Code: " << num << "; ";
        ratio = num / AMOUNT_OF_ASCII_CHARS;
        std::cout << "Ratio of Code to Amount of Characters in ASCII: " << ratio << "; ";
        freq = BAND_LIMIT_FREQ * (ratio);
        std::cout << "Frequency: " << freq << std::endl;
        Beep(freq, 500);
    }
    
    return 0;
}
