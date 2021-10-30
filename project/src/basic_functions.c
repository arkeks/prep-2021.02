#include "matrix.h"

int get_rows(const Matrix* matrix, size_t* rows) {
    *rows = matrix -> rows;
    if (*rows) {
        return 0;
    }
    return 1;
}

int get_cols(const Matrix* matrix, size_t* cols) {
    *cols = matrix -> cols;
    if (*cols) {
        return 0;
    }
    return 1;
}

int get_elem(const Matrix* matrix, size_t row, size_t col, double* val) {
    *val = matrix -> matrix[row][col];
    if (*val == matrix -> matrix[row][col]) {
        return 0;
    }
    return 1;
}

int set_elem(Matrix* matrix, size_t row, size_t col, double val) {
    matrix -> matrix[row][col] = val;
    if (matrix -> matrix[row][col] == val) {
        return 0;
    }
    return 1;
}

