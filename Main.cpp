#include <iostream>
#include "Matrix.cpp"

int main() {
    Matrix m(2, 3);
    int elements[] = {1, 2, 3, 4, 5, 6};
    m.fill_matrix(elements);    
    m.display_matrix();
    bool rref = m.isRREF();
    std::cout << "Is the matrix in Reduced Row Echelon Form (RREF)? " << std::boolalpha << rref << std::endl;
    Matrix::row_reduce(m);
    m.display_matrix();
    return 0;
}