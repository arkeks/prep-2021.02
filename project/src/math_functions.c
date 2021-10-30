#include "matrix.h"

Matrix* mul_scalar(const Matrix* matrix, double val) {
    Matrix* mul_matrix = create_matrix(matrix -> rows, matrix -> cols);
    for (size_t i = 0; i < (matrix -> rows); ++i) {
        for (size_t g = 0; g < (matrix -> cols); ++g) {
            mul_matrix -> matrix[i][g] = matrix -> matrix[i][g];
            mul_matrix -> matrix[i][g] *= val;
        }
    }
    return mul_matrix;
}

Matrix* transp(const Matrix* matrix) {
    Matrix* tr_matrix = create_matrix(matrix -> cols, matrix -> rows);
    for (size_t i = 0; i < (tr_matrix -> rows); ++i) {
        for (size_t g = 0; g < (tr_matrix -> cols); ++g) {
            tr_matrix -> matrix[i][g] = matrix -> matrix[g][i];
        }
    }
    return tr_matrix;
}

Matrix* sum(const Matrix* l, const Matrix* r) {
    if ((l -> rows == r -> rows) && (l -> cols == r -> cols)) {
        Matrix* sum_matrix = create_matrix(l -> rows, l -> cols);
        for (size_t i = 0; i < (l -> rows); ++i) {
            for (size_t g = 0; g < (l -> cols); ++g) {
                sum_matrix -> matrix[i][g] = l -> matrix[i][g] + r -> matrix[i][g];
            }
        }
        return sum_matrix;
    }
    printf("%s", MATRIX_SUM_ERROR);
    return NULL;
}

Matrix* sub(const Matrix* l, const Matrix* r) {
    if ((l -> rows == r -> rows) && (l -> cols == r -> cols)) {
        Matrix* sub_matrix = create_matrix(l -> rows, l -> cols);
        for (size_t i = 0; i < (l -> rows); ++i) {
            for (size_t g = 0; g < (l -> cols); ++g) {
                sub_matrix -> matrix[i][g] = l -> matrix[i][g] - r -> matrix[i][g];
            }
        }
        return sub_matrix;
    }
    printf("%s", MATRIX_SUM_ERROR);
    return NULL;
}

Matrix* mul(const Matrix* l, const Matrix* r) {
    if (l -> cols == r -> rows) {
        Matrix* mul_matrix = create_matrix(l -> rows, r -> cols);
        for (size_t i = 0; i < mul_matrix -> rows; ++i) {
            for (size_t g = 0; g < mul_matrix -> cols; ++g) {
                mul_matrix -> matrix[i][g] = 0;
            }
        }
        for (size_t k = 0; k < (r -> cols); ++k) {
            for (size_t i = 0; i < (l -> rows); ++i) {
                for (size_t g = 0; g < (l -> cols); ++g) {
                    mul_matrix -> matrix[i][k] += (l -> matrix[i][g]) * (r -> matrix[g][k]);
                }
            }
        }
        return mul_matrix;
    }
    printf("%s", MATRIX_MUL_ERROR);
    return NULL;
}

int det(const Matrix* matrix, double* val) {
    Matrix* new_matrix = malloc(sizeof(Matrix));
    new_matrix -> rows = matrix -> rows;
    *val *= *val;
    return new_matrix -> rows;
}
Matrix* adj(const Matrix* matrix) {
    Matrix* new_matrix = malloc(sizeof(Matrix));
    new_matrix -> rows = matrix -> rows;
    return new_matrix;
}
Matrix* inv(const Matrix* matrix) {
    Matrix* new_matrix = malloc(sizeof(Matrix));
    new_matrix -> rows = matrix -> rows;
    return new_matrix;
}