#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

bool openFiles();
void createWordsArray(string line, int &numWords, int charNum, string word, string words[]);
void checkLength(int &numWords, string words[]);
void checkDupes(int numWords, string words[]);
void writeToFile(int numWords, string words[]);

ifstream IN_FILE;
ofstream OUT_FILE;
//There will always be one word smaller than 16 characters
//We want to preserve the lines 

int main() {
    string *words = new string[100];
    string line;
    int wordLength;
    int charNum;
    bool good;

    good = openFiles();

    if (good == 0)
        return 1;

    //Where the work happens
    while(!IN_FILE.eof()) {
        //get next line and reset vars
        getline(IN_FILE, line);
        string word = "";
        int numWords = 0;

        //remove commas
        line.erase(remove(line.begin(), line.end(), ','), line.end());

        createWordsArray(line, numWords, 0, word, words);
        checkLength(numWords, words); 
        checkDupes(numWords, words);
        writeToFile(numWords, words); 

        //goto next line of document
    }
    IN_FILE.close();
    OUT_FILE.close();

    return 0;
}

bool openFiles() {
    string filename;

    //open ifstream file
    cout << "\n\nWhat is the name of the file (ex: filename.txt)\n" << endl << "FILENAME: ";
    cin >> filename;
	IN_FILE.open(filename);

    //open ofstream file
    cout << "\nWhat is the name of the file you want to save to?\n" << endl << "FILENAME: ";
	cin >> filename;
    OUT_FILE.open(filename);

    //check if valid
    if(!IN_FILE){
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
    words[numWords] = word;
}

void checkLength(int &numWords, string words[]) {
    int wordLength;

    //Right now skips next element if detects bad
    for (int i = 0; i <= numWords; i++) {
        wordLength = words[i].size();
        //if too big remove from array
        if (wordLength > 15) {
            //If last element
            if (i == numWords)  {
                numWords--;
                break;
            }
            //shift the array the one less word
            for (int j = i; j < numWords; j++) 
                words[j] = words[j+1];
                    
            numWords--;
            i--;
        }
    }
}

void checkDupes(int numWords, string words[]){
    for (int i = 0; i < numWords; i++) {
        if (words[i] == words[i+1]){
            for (int j = i; j < numWords; j++) 
                words[j] = words[j+1];

            numWords--;
            i--;
        }
    }
}

void writeToFile(int numWords, string words[]) {
    //Write to file
    for (int i = 0; i < numWords; i++) {
        OUT_FILE << words[i] << ", ";
    }
    OUT_FILE << words[numWords] << endl;
}