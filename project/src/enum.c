#include "enum.h"

int enumeration(int n) {
    if (n == 1) {
    printf("%d", n);
    return 1;
    }
    if (n <= 0) {
    printf(" %d", enumeration(n + 1) - 1);
    return n;
    } else {
    printf(" %d", enumeration(n - 1) + 1);
    return n;
    }
    return 0;
}
