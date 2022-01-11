#ifndef PROJECT_INCLUDE_MATRIX_H_
#define PROJECT_INCLUDE_MATRIX_H_
#define MATRIX_MUL_ERROR "The number of the left matrix rows must be equal to the right matrix columns!"
#define MATRIX_SUM_ERROR "Matrices must be the same size!"
#define MATRIX_SQ_ERROR "Matrix must be squared!"
#define SUCCESS 0
#define FAIL 1

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>

typedef struct Matrix {
    size_t rows;
    size_t cols;
    double** matrix;
} Matrix;

// Init/release operations
Matrix* create_matrix_from_file(const char* path_file);
Matrix* create_matrix(size_t rows, size_t cols);
void free_matrix(Matrix* matrix);

// Basic operations
int get_rows(const Matrix* matrix, size_t* rows);
int get_cols(const Matrix* matrix, size_t* cols);
int get_elem(const Matrix* matrix, size_t row, size_t col, double* val);
int set_elem(Matrix* matrix, size_t row, size_t col, double val);

// Math operations
Matrix* mul_scalar(const Matrix* matrix, double val);
Matrix* transp(const Matrix* matrix);
Matrix* get_minor_matrix(const Matrix* matrix, size_t el_row, size_t el_col);
double determinant(const Matrix* matrix);

Matrix* sum(const Matrix* l, const Matrix* r);
Matrix* sub(const Matrix* l, const Matrix* r);
Matrix* mul(const Matrix* l, const Matrix* r);

// Extra operations
int det(const Matrix* matrix, double* val);
Matrix* adj(const Matrix* matrix);
Matrix* inv(const Matrix* matrix);


#endif  // PROJECT_INCLUDE_MATRIX_H_
