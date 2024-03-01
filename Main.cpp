#include <iostream>
#include "Matrix.cpp"

int main() {
    Matrix m(2, 3);
    int elements[] = {1, 2, 3, 4, 5, 6};
    m.fill_matrix(elements);    
    m.display_matrix();
}