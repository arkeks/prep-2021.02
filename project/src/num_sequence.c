#include "num_sequence.h"

int num_sequence(int n) {
    if (n == 1) {
        printf("%d", n);
        return 1;
    }
    if (n <= 0) {
        printf(" %d", num_sequence(n + 1) - 1);
        return n;
    } else {
        printf(" %d", num_sequence(n - 1) + 1);
        return n;
    }
    return 0;
}
