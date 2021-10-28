#include "is_simple.h"

// Function checks whether an input number is simple
bool is_simple(int num) {
	if (num <= 1) {
	    return FALSE;
	}
	for (int i = 2; i <= sqrt(num); ++i) {
	    if (num % i == 0) {
	    	return FALSE;
	    }
	}
	return TRUE;
}
