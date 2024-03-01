#include <iostream>
#include "Matrix.cpp"

class Linear_System_Equations:
    public:
    int equations;
    int variables;
    int *coefficients;
    Matrix m;

    Linear_System_Equations(int equations, int variables, int* coefficients, int* solutions) {
        // set up Matrix for system
        m(equations, variables + 1);
    }