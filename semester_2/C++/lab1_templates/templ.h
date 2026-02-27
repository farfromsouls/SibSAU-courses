template <typename Type>
void fillMatrix(Type** matrix, int rows, int cols, int k) {
    srand(time(0));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = static_cast<Type>(rand() % (2 * k + 1) - k);
        }
    }
}

template <typename Type>
void mulMatrix(Type** matrix, int rows, int cols, Type mul) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] *= mul;
        }
    }
}

template <typename Type>
void printMatrix(Type** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << matrix[i][j] << " ";
        }
        printf("\n");
    }
}