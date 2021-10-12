#include "is_simple.h"

char is_simple(int num) {
	if (num < 0) {
	return 0;
	}
	for (int i = 2; i < 10; ++i) {
	    if (num % i == 0 || num == 1) {
	    	return 0;
	    }
	}
	return 1;
}
