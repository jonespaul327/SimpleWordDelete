#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;



int main() {
    ifstream inFile;
    ofstream outFile;
    string filename;
    string line;
    string word;
    string words[50];
    int numWords;
    int wordLength;
    int charNum;

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
        return 1;
    }

    //Where the work happens
    while(!inFile.eof()) {
        getline(inFile, line);
        word = "";
        numWords = 0;
        charNum = 0;

        //remove commas
        line.erase(remove(line.begin(), line.end(), ','), line.end());

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
                    cout << "Successfully removed " << words[i] << endl;
                    cout << "     size: " << wordLength;
                    numWords--;
                    break;
                }

                //shift the array the one less word
                for (int j = i; j < numWords; j++) 
                    words[j] = words[j+1];
                
                cout << "Successfully removed " << words[i] << endl;
                cout << "     size: " << wordLength;
                numWords--;
            }
        }

        //Write to file
        for (string i : words) {
            outFile << i << ", ";
        }
        outFile << endl;
        
        //goto next line
    }
    inFile.close();
    outFile.close();

    cout << "done";

    return 0;
}