#include <test.h>

void write_to_file(FILE* filename, struct student_info* data) {
    if (filename == NULL) {
        puts("Not access");
        } else {
        fprintf(filename, "%d. %19s %19s %8s &6s\n",
        data->number,
        data->surname,
        data->name,
        data->group,
        data->status);
        }
}

void read_from_file(FILE* filename, struct student_info* data) {
    if (filename == NULL) {
        puts("Not access");
        } else {
            fscanf(filename, "%d%19s%19s%7s%6s",
            data->number,
            data->surname,
            data->name,
            data->group,
            data->status);
            }
}
