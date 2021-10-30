#include "matrix.h"

Matrix* create_matrix(size_t rows, size_t cols) {
    Matrix* new_matrix = (Matrix*) malloc(sizeof(Matrix));
    new_matrix -> rows = rows;
    new_matrix -> cols = cols;
    new_matrix -> matrix = (double**) malloc(rows * sizeof(double*));
    for (size_t i = 0; i < rows; ++i) {
        new_matrix -> matrix[i] = (double*) malloc(cols * sizeof(double));
    }
    return new_matrix;
}

Matrix* create_matrix_from_file(const char* path_file) {
    FILE* file_ptr = fopen(path_file, "r");
    if (file_ptr == NULL) {
        return NULL;
    }
    size_t rows, cols;
    fscanf(file_ptr, "%zu %zu", &rows, &cols);
    Matrix* new_matrix = create_matrix(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t g = 0; g < cols; ++g) {
            fscanf(file_ptr, "%lf", &new_matrix -> matrix[i][g]);
        }
    }
    fclose(file_ptr);
    return new_matrix;
}

void free_matrix(Matrix* matrix) {
    for (size_t i = 0; i < matrix -> rows; ++i) {
        free(matrix -> matrix[i]);
    }
    free(matrix -> matrix);
    free(matrix);
}