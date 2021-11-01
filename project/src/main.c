#include "matrix.h"

int main(void) {
    Matrix* test_matrix = create_matrix(3, 3);
    for (size_t i = 0; i < test_matrix -> rows; ++i) {
        for (size_t g = 0; g < test_matrix -> cols; ++g) {
            test_matrix->matrix[i][g] = i + g;
        }
    }

    for (size_t i = 0; i < test_matrix -> rows; ++i) {
        for (size_t g = 0; g < test_matrix -> cols; ++g) {
            printf("%lf ", test_matrix -> matrix[i][g]);
        }
        printf("\n");
    }
    printf("\n");
    Matrix* test_minor;
    printf("now getting min\n");
    test_minor = get_minor_matrix(test_matrix, 0, 0);

    for (size_t i = 0; i < test_minor -> rows; ++i) {
        for (size_t g = 0; g < test_minor -> cols; ++g) {
            printf("%lf ", test_minor -> matrix[i][g]);
        }
        printf("\n");
    }

    Matrix* test_adj;
    test_adj = adj(test_matrix);

    for (size_t i = 0; i < test_adj -> rows; ++i) {
        for (size_t g = 0; g < test_adj -> cols; ++g) {
            printf("adj %lf ", test_adj -> matrix[i][g]);
        }
        printf("\n");
    }
    free_matrix(test_matrix);
    free_matrix(test_minor);
    free_matrix(test_adj);
    return 0;
}
