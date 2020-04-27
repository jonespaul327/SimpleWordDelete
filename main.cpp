#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

bool openFiles(ifstream &inFile, ofstream &outFile);
void createWordsArray(string line, int &numWords, int charNum, string word);
//There will always be one word smaller than 16 characters
//We want to preserve the lines 

int main() {
    string *words = new string[100];
    ifstream inFile;
    ofstream outFile;
    string line;
    string word;
    int numWords;
    int wordLength;
    int charNum;
    bool good;

    good = openFiles(inFile, outFile);

    if (good == 0)
        return 1;

    //Where the work happens
    while(!inFile.eof()) {
        //get next line and reset vars
        getline(inFile, line);
        word = "";
        numWords = 0;

        //remove commas
        line.erase(remove(line.begin(), line.end(), ','), line.end());

        createWordsArray(line, numWords, 0, word, words);

        //create array of words
        for (char i : line) {

            //check if end of word
            if (i == ' ' || charNum == line.size()) {
                words[numWords] = word;
                word = "";
                numWords++;
            }

            //concatanate next char
            else {
                word = word + i;
            }
            charNum++;
        }

        //check if longer than 15
        for (int i = 0; i < numWords; i++) {
            wordLength = words[i].size();

            //if too big remove from array
            if (wordLength > 15) {
                //If last element
                if (i == numWords - 1)  {
                    //cout << "Successfully removed " << words[i] << endl;
                    //cout << "     size: " << wordLength;
                    numWords--;
                    break;
                }

                //shift the array the one less word
                for (int j = i; j < numWords; j++) 
                    words[j] = words[j+1];
                
                //cout << "Successfully removed " << words[i] << endl;
                //cout << "     size: " << wordLength;
                numWords--;
            }
        }

        //Write to file
        for (int i = 0; i < numWords; i++) {
            if (i == numWords - 2 || numWords == 1) {
                outFile << words[i];
                break;
            }

            outFile << words[i] << ", ";
        }
        outFile << endl;

        //goto next line of document
    }
    inFile.close();
    outFile.close();

    cout << "done";

    return 0;
}

bool openFiles(ifstream &inFile, ofstream &outFile) {
    string filename;

    //open ifstream file
    cout << "\n\nWhat is the name of the file (ex: filename.txt)\n" << endl << "FILENAME: ";
    filename = "test.txt";
    //cin >> filename;
	inFile.open(filename);

    //open ofstream file
    cout << "What is the name of the file you want to save to?\n" << endl << "FILENAME: ";
    filename = "output.txt";
	//cin >> filename;
    outFile.open(filename);

    //check if valid
    if(!inFile){
        cout<< "Cannot open input file!" << endl;
        return false;
    }

    return true;
}

void createWordsArray(string line, int &numWords, int charNum, string word, string words[]) {
    for (char i : line) {
        //check if end of word
        if (i == ' ' || charNum == line.size()) {
            words[numWords] = word;
            word = "";
            numWords++;
        }

        //concatanate next char
        else {
            word = word + i;
        }
        charNum++;
    }
}