#include <iostream>
#include <set>

class Matrix {
    public:
    int rows;
    int cols;
    int **arr;

    Matrix(int rows, int cols) {
        this->rows = rows;
        this->cols = cols;
        
        // allocate memory for matrix
        arr = new int*[rows];
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
            std::cout << std::endl;
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

    // Matrix Multiplication
    Matrix matrix_multiply(Matrix m) {
        if (cols != m.rows) {
        throw std::invalid_argument("columns in first matrix must equal rows in second matrix");
        }

        Matrix product = Matrix(rows, m.cols);

        // fill matrix
        int index = 0;
        int* values = new int[rows * m.cols];

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < m.cols; j++) {
                int val = 0;

                // iterate through row/col
                for (int k = 0; k < cols; k++) {
                    val += arr[i][k] * m.arr[k][j];
                }

                values[index] = val;
                index++;
            }
        }

        product.fill_matrix(values);
        return product;
    }

    // boolean for is in RREF
    bool isRREF() {
        std::set<int> leading_column_indices;
        int last_nonzero_column = -1;

        for (int i = 0; i < rows; i++) {
            bool leading_one_found = false;

            // condition 1: leading entry in row is 1
            if (arr[i][i] != 1) {
                return false;
            }

            // condition 2: pivot is one to the right of the last pivot
            if (i == 0 && !leading_column_indices.empty() && *leading_column_indices.begin() <= last_nonzero_column) {
                return false;
            }
            
            // condition 3: all non pivots are zero
            for (int j = 0; j < cols; ++j) {
                if (arr[i][j] != 0) {
                    if (j > last_nonzero_column) {
                        leading_column_indices.insert(j);
                        last_nonzero_column = j;
                    } else if (j < last_nonzero_column) {
                        return false;
                    } else {
                        leading_one_found = true;
                    }

                    if (leading_one_found && arr[i][j] != 1) {
                        return false;
                    }
                } else {
                    if (j == last_nonzero_column) {
                        leading_one_found = false;
                    }
                }
            }
        }

        return true;
    }

    static Matrix row_reduce(Matrix m) {
        // initialize leading column index
        int leading_col = 0;

        // iterate over rows
        for (int i = 0; i < m.rows; i++) {
            // find pivot in current row
            bool pivot_found = false;

            for (int j = leading_col; j < m.cols; j++) {
                if (m.arr[i][j] == 1) {
                    pivot_found = true;

                    // if necessary, swap rows to bring pivot to the top
                    if (i != leading_col) {
                        std::swap(m.arr[i], m.arr[leading_col]);
                    }

                    // update leading column
                    leading_col = j;
                    break;
                }
            }

            if (pivot_found) {
                // make the pivot 1
                for (int j = 0; j < m.cols; j++) {
                    m.arr[i][j] /= m.arr[i][leading_col];
                }

                // eliminate entries below the pivot
                for (int k = i + 1; k < m.rows; k++) {
                    if (m.arr[k][leading_col] == 1) {
                        for (int j = 0; j < m.cols; j++) {
                            m.arr[k][j] ^= m.arr[i][j];
                        }
                    }
                }
            } else {
                // if no pivot found, move to the next column
                leading_col++;
            }

            // check if matrix is in echelon form
            if (m.isRREF()) {
                break;
            }
        }

        return m;
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