#include <iostream>
#include "templ.h"
using namespace std;


int main() {
    int rows = 15;
    int cols = 15;
    double mul = 2;
    int k = 10;

    double** matrix = new double*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new double[cols];
    }

    fillMatrix(matrix, rows, cols, k);

    cout << "orig matrix:" << "\n";
    printMatrix(matrix, rows, cols);

    mulMatrix(matrix, rows, cols, mul);

    cout << "\nmatrix mul by " << mul << ":" << "\n";
    printMatrix(matrix, rows, cols);

    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}
