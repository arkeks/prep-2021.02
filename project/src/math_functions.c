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

Matrix* get_minor_matrix(const Matrix* matrix, size_t el_row, size_t el_col) {
    if (matrix -> rows == 1) {
        Matrix* minor_matrix = create_matrix(matrix -> rows, matrix -> cols);
        minor_matrix -> matrix[0][0] = matrix -> matrix[0][0];
        return minor_matrix;
    }
    Matrix* minor_matrix = create_matrix(((matrix -> rows) - 1), ((matrix -> cols) - 1));
    for (size_t i = 0, k = 0; i < minor_matrix -> rows; ++i, ++k) {
        size_t g = 0;
        size_t j = 0;
        while (g < minor_matrix -> cols) {
            if (k == el_row) {
                --i;
                break;
            } else if (j == el_col) {
                ++j;
            } else {
                minor_matrix -> matrix[i][g] = matrix -> matrix[k][j];
                ++j;
                ++g;
            }
        }
    }
    return minor_matrix;
}

double determinant(const Matrix* matrix) {
    if ((matrix -> rows) != (matrix -> cols)) {
        printf("%s", MATRIX_SQ_ERROR);
        return FAIL;
    } else if (matrix -> rows == 1) {
        return matrix -> matrix[0][0];
    } else {
        double res = 0;
        for (size_t g = 0; g < matrix -> cols; ++g) {
            res += pow(-1, (1+(g+1))) * (matrix -> matrix[0][g])
                    * determinant(get_minor_matrix(matrix, 0, g));
        }
        return res;
    }
}

int det(const Matrix* matrix, double* val) {
    if (matrix != NULL) {
        *val = determinant(matrix);
        return SUCCESS;
    }
    return FAIL;
}

Matrix* adj(const Matrix* matrix) {
    Matrix* adj_matrix = create_matrix(matrix -> rows, matrix -> cols);
    for (size_t i = 0; i < adj_matrix -> rows; ++i) {
        for (size_t g = 0; g < adj_matrix -> cols; ++g) {
            adj_matrix -> matrix[i][g] = pow(-1, ((i+1)+(g+1))) * determinant(get_minor_matrix(matrix, i, g));
        }
    }
    return transp(adj_matrix);
}

Matrix* inv(const Matrix* matrix) {
    if (matrix -> rows == 1 && matrix -> cols == 1) {
        Matrix* inv_matrix = create_matrix(1, 1);
        inv_matrix -> matrix[0][0] = 1.0 / (matrix -> matrix[0][0]);
        return inv_matrix;
    }
    Matrix* inv_matrix = create_matrix(matrix -> rows, matrix -> cols);
    for (size_t i = 0; i < matrix -> rows; ++i) {
        for (size_t g = 0; g < matrix -> cols; ++g) {
            inv_matrix -> matrix[i][g] = matrix -> matrix[i][g];
        }
    }
    if (determinant(inv_matrix) != 0) {
        inv_matrix = mul_scalar(adj(inv_matrix), (1.0 / determinant(inv_matrix)));
        return inv_matrix;
    } else {
        return NULL;
    }
}
