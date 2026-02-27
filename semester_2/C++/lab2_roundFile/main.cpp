#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;


int main() {
    ifstream inputFile;
    ofstream outputFile;

    inputFile.open("input.txt");
    outputFile.open("output.txt");

    double number;
    while (inputFile >> number) {
        outputFile << fixed << setprecision(1) << number << " ";
    }

    inputFile.close();
    outputFile.close();

    cout << "Success" << endl;
    return 0;
}