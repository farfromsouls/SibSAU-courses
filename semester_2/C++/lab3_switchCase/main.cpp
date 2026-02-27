#include <cctype>
#include <iostream>
#include <fstream>
using namespace std;


int main() {
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    char ch;
    while (inputFile.get(ch)) {
        if (islower(ch)) {
            ch = toupper(ch);
        } else if (isupper(ch)) {
            ch = tolower(ch);
        }
        outputFile << ch;
    }

    inputFile.close();
    outputFile.close();

    cout << "Success" << endl;

    return 0;
}