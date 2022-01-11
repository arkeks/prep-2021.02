#include "matrix.h"

int get_rows(const Matrix* matrix, size_t* rows) {
    if (rows == NULL || matrix == NULL) {
        return FAIL;
    }
    *rows = matrix -> rows;
    if (*rows) {
        return SUCCESS;
    }
    return FAIL;
}

int get_cols(const Matrix* matrix, size_t* cols) {
    if (cols == NULL || matrix == NULL) {
        return FAIL;
    }
    *cols = matrix -> cols;
    if (*cols) {
        return SUCCESS;
    }
    return FAIL;
}

int get_elem(const Matrix* matrix, size_t row, size_t col, double* val) {
    if (val == NULL || matrix == NULL) {
        return FAIL;
    }
    *val = matrix -> matrix[row][col];
    if (*val == matrix -> matrix[row][col]) {
        return SUCCESS;
    }
    return FAIL;
}

int set_elem(Matrix* matrix, size_t row, size_t col, double val) {
    if (matrix == NULL) {
        return FAIL;
    }
    matrix -> matrix[row][col] = val;
    if (matrix -> matrix[row][col] == val) {
        return SUCCESS;
    }
    return FAIL;
}
