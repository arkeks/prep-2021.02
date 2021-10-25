#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef PROJECT_INCLUDE_TEST_H_
#define PROJECT_INCLUDE_TEST_H_

struct student_info {
        unsigned int number;
        char surname[20];
        char name[20];
        char group[8];
        char status[7];
        };

void write_to_file(FILE* filename, struct student_info* data);
void read_from_file(FILE* filename, struct student_info* data);

#endif  // PROJECT_INCLUDE_TEST_H_
