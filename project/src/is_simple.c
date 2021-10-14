#include "is_simple.h"
#define SINGLE_DIGIT_LIMIT 10

// Function checks whether an input number is simple
char is_simple(int num) {
	if (num < 0) {
	return 0;
	}
	for (int i = 2; i < SINGLE_DIGIT_LIMIT; ++i) {
	    if (num % i == 0 || num == 1) {
	    	return 0;
	    }
	}
	return 1;
}
