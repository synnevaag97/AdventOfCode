/*
This version uses find from the <algorithm> header to check if an element is present in the winning numbers. 
It also leverages the <algorithm> header's transform and back_inserter functions to populate vectors directly from strings. 
Additionally, it handles spaces in the input string by converting them to -1 during transformation. 
This way, you don't need a separate function to create a vector from a string.
*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int calculatePoints(const vector<int>& winningNumbers, const vector<int>& elfNumbers) {
    int points = 0;
    for (const int& elfNumber : elfNumbers) {
        if (find(winningNumbers.begin(), winningNumbers.end(), elfNumber) != winningNumbers.end()) {
            points = (points == 0) ? 1 : points * 2;
        }
    }
    return points;
}

int main() {
    ifstream input_file("/home/tsg/Documents/CalenderTasks/Task4/input");
    if (!input_file.is_open()) {
        cerr << "Error opening input file!" << endl;
        return 1;
    }

    int totalPoints = 0;
    string line;
    while (getline(input_file, line)) {
        istringstream iss(line);
        string winningNumbersStr, elfNumbersStr;
        getline(iss, winningNumbersStr, '|');
        getline(iss, elfNumbersStr);

        vector<int> winningNumbers, elfNumbers;
        transform(winningNumbersStr.begin(), winningNumbersStr.end(), back_inserter(winningNumbers),
                  [](char c) { return c == ' ' ? -1 : c - '0'; });
        transform(elfNumbersStr.begin(), elfNumbersStr.end(), back_inserter(elfNumbers),
                  [](char c) { return c == ' ' ? -1 : c - '0'; });

        int points = calculatePoints(winningNumbers, elfNumbers);
        cout << "Points on this card: " << points << '\n';
        totalPoints += points;
    }

    cout << "Total points: " << totalPoints << '\n';
    return 0;
}


