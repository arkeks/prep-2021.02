#include "matrix.h"

int get_rows(const Matrix* matrix, size_t* rows) {
    *rows = matrix -> rows;
    if (*rows) {
        return SUCCESS;
    }
    return FAIL;
}

int get_cols(const Matrix* matrix, size_t* cols) {
    *cols = matrix -> cols;
    if (*cols) {
        return SUCCESS;
    }
    return FAIL;
}

int get_elem(const Matrix* matrix, size_t row, size_t col, double* val) {
    *val = matrix -> matrix[row][col];
    if (*val == matrix -> matrix[row][col]) {
        return SUCCESS;
    }
    return FAIL;
}

int set_elem(Matrix* matrix, size_t row, size_t col, double val) {
    matrix -> matrix[row][col] = val;
    if (matrix -> matrix[row][col] == val) {
        return SUCCESS;
    }
    return FAIL;
}
