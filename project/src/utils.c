#include "utils.h"

size_t timer_from(unsigned int from) {
    size_t counter = 0;
    for (int i = from; i >= 0; --i) {
        ++counter;
        if (i == 0) {
        printf("%d\n", i);
        } else {
        printf("%d ", i);
        }
    }
    return counter;
}

float custom_pow(int base, int power) {
    float res = 1;
	if (power >= 0) {
        for (int i = 0; i < power; ++i) {
            res *= base;
        }
    } else {
        for (int i = 0; i > power; --i) {
            res *= (1/(float)base);
        }
    }
    return res;
}
