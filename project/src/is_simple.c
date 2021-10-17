#include "is_simple.h"

// Function checks whether an input number is simple
char is_simple(int num) {
	if (num <= 1) {
	    return 0;
	}
	for (int i = 2; i <= sqrt(num); ++i) {
	    if (num % i == 0 || num == 1) {
	    	return 0;
	    }
	}
	return 1;
}
