#include <iostream>

class Matrix {
    public:
    int rows;
    int cols;
    int **arr;

    Matrix(int rows, int cols) {
        this->rows = rows;
        this->cols = cols;
        
        // allocate memory for matrix
        for (int i = 0; i < rows; i++) {
            arr[i] = new int[cols];
        }
    }

    // fill Matrix
    void fill_matrix(int elements[]) {
        int k = 0;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                arr[i][j] = elements[k++];
            }
        }
    }

    // display Matrix
    void display_matrix() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << arr[i][j] << " ";
            }
            std::cout << std::ends;
        }
    }

    // Matrix addition
    Matrix add(Matrix addent) {
        if (rows != addent.rows || cols != addent.cols) {
            throw std::invalid_argument("Matrices must have the same dimensions.");
        }

        Matrix sum = Matrix(rows, cols);

        // sum each individual values and add to an array
        int *elements = new int[rows * cols];
        int index = 0;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                elements[index] = arr[i][j] + addent.arr[i][j];
                index++;
            }
        }

        sum.fill_matrix(elements);
        return sum;
    }

    // Matrix scalar multiplication
    Matrix scalarMultiply(int n) {
        Matrix product = Matrix(rows, cols);

        int *elements = new int[rows * cols];

        int index = 0;
        // multiply every value by scalar
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                elements[index] = n * arr[i][j];
                index++;
            }
        }

        product.fill_matrix(elements);
        return product;
    }

    // Matrix destructor
    ~Matrix() {
        // deallocate memory
        for (int i = 0; i < rows; i++) {
            delete[] arr[i];
        }
        delete[] arr;
    }

};

int main() {
    
}