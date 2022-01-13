#include "parser.h"

int main(int argc, const char **argv) {
    if (argc != ARG_NUM) {
        return WRONG_ARG_ERR;
    }
    info output;
    output.from = NULL;
    output.to = NULL;
    output.date = NULL;
    output.boundary = NULL;
    info* output_ptr = &output;
    const char *path_to_eml = argv[1];
    FILE* eml_file = fopen(path_to_eml, "r");

    if (eml_file == NULL) {
        printf("File can't be opened.\n");
        return FAIL;
    }
    char* eml_text = get_eml_text(eml_file);
    if (eml_text == NULL) {
        return FAIL;
    }
    if (parse(eml_text, &output_ptr) == FAIL) {
        printf("error\n");
    }
    print_info(output_ptr);
    free_info(output, eml_text);
    return 0;
}
