#include <test.h>

int main(void) {
    const char* filename = "student.dat";
    struct student_info student_1;
    student_1.number = 1;
    strcpy(student_1.name, "Arseny");
    strcpy(student_1.surname, "Dobrotin");
    strcpy(student_1.group, "IU4-31B");
    strcpy(student_1.status, "PASSED");
    FILE* students_list = fopen(filename, "w");
    write_to_file(filename, &student_1);
    fclose(students_list);
    struct student_info student_1_check = {0};
    FILE* students_list_check = fopen(filename, "r");
    read_from_file(filename, &student_1_check);
    if (student_1.group == student_1_check.group) {
        printf("Succesful writing.");
        } else {
            printf("Writing failed.");
            }
    fclose(students_list_check);
    return 0;
}
