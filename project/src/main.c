#include "parser.h"

int main(int argc, const char **argv) {
    if (argc != 2) {
        return -1;
    }
    //printf("1");
    info output;
    output.from = NULL;
    //output.from[0] = 0;
    output.to = NULL;
    //output.to[0] = 0;
    output.date = NULL;
    //output.date[0] = 0;
    output.boundary = NULL;
    //output.boundary[0] = 0;
    info* output_ptr = &output;
    //printf("2");
    const char *path_to_eml = argv[1];
    //printf("3");
    //puts(path_to_eml);
    //printf("4");
    FILE* eml_file = fopen(path_to_eml, "r");
    //printf("5");
    if (eml_file == NULL) {
        printf("ooops");
        return FAIL;
    }
    //printf("6\n");
    //size_t count = 0;
    char* eml_text = get_eml_text(eml_file);
    if (eml_text == NULL) {
        return FAIL;
    }
    //printf("%s", eml_text);
    /*while(*eml_text) {
        printf("%c", *eml_text);
        ++eml_text;
        ++count;
    }
    for (size_t i = 0; i < count; ++i) {
        --eml_text;
    }*/
    if (parse(eml_text, &output_ptr) == FAIL) {
        printf("error\n");
        //return FAIL;
    }
    //printf("\nfinal info:\n");
    print_info(output_ptr);
    free(output.from);
    free(output.to);
    free(output.date);
    free(output.boundary);
    free(eml_text);
    return 0;
}
