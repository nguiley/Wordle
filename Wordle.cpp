#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <algorithm>

using namespace std;

string getWord(int NUMWORDS, ifstream& in_file) {
    string word;
    int random = 1 + (rand() % NUMWORDS);
    for (int i = 0; i < random; i++) {
        in_file >> word;
    }
    in_file.seekg(0);
    return word;
}

void inWord(string guess, string word) {
    string newWord;
    for (int i = 0; i < 5; i++) {
        if (guess[i] == word[i]) {
            cout << "\033[32m" << guess[i] << "\033[0m"; // green
        } else if (guess[i] == word[0] || guess[i] == word[1] || guess[i] == word[2] || guess[i] == word[3] || guess[i] == word[4]) {
            cout << "\033[33m" << guess[i] << "\033[0m"; // yellow
        } else {
            cout << "\033[0m" << guess[i]; // default
        }
    }
}

bool inFile(string guess, ifstream & in_file) {
    int numWords = 5757;
    string word;
    transform(guess.begin(), guess.end(), guess.begin(), ::toupper);
    in_file.seekg(0);
    for (int i = 0; i < numWords; i++) {
        in_file >> word;
        transform(word.begin(), word.end(), word.begin(), ::toupper);
        if (guess == word) {
            return true;
        }
    }
    return false;
}

int main() {
    srand(time(nullptr));
    ifstream in_file;
    in_file.open("words.txt");
    const int NUMWORDS = 5757;
    string word = getWord(NUMWORDS, in_file);
    transform(word.begin(), word.end(), word.begin(), ::toupper);
    cout << "Word: " << word << endl;
    for (int i = 0; i < 5; i++) {
        string guess;
        do {
            cout << "Guess " << i + 1 << " (must be 5 letters and a real word): ";
            cin >> guess;
            transform(guess.begin(), guess.end(), guess.begin(), ::toupper);
        } while (guess.length() != 5 || !inFile(guess, in_file));
        inWord(guess, word);
        cout << "" << endl;
        if (guess == word) {
            cout << "Cool ig" << endl;
            return 0;
        }
    }
    cout << "Holy shit you suck" << endl;
    return 0;
}