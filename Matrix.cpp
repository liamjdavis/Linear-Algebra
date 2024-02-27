#include <iostream>

class Matrix {
    public:

    int rows;
    int cols;

    Matrix(int rows, int cols) {
        rows = rows;
        cols = cols;
    }
};

int main() {
    Matrix m(1, 2);
}