#ifndef PREP_2021_02_PARSER_H
#define PREP_2021_02_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SUCCESS 0
#define FAIL 1
#define MEMALLOC_ERR  "Memory has not been allocated :("
#define WRONG_ARG_ERR -1

#define ROW_NUM 3
#define COL_NUM 6

#define NO_TYPE 0
#define PLAIN_T 1
#define MULTIPART_T 2
#define ARG_NUM 2
#define DEF_MEM_INFO 1000
#define DEF_MEM_BOUND 150

typedef struct {
    char* from;
    char* to;
    char* date;
    unsigned int cont_t;
    char* boundary;
    unsigned int parts_num;
} info;

typedef enum {
    L_FROM,
    L_TO,
    L_DATE,
    L_CONT_T,
    L_BOUND,
    L_ENDL,
    L_DIVIDER,
    L_EOF
} lexeme_t;

typedef enum {
    S_HEADERS,
    S_CONT_T,
    S_ENDL,
    S_ERR
} state_t;

typedef int (*action_t)(char** str, info** output, lexeme_t cur_lexeme);

typedef struct {
    state_t state;
    action_t action;
} rule_t;

int get_info(char** str, info** output, lexeme_t cur_lexeme);
int get_cont_t(char** str, info** output, lexeme_t cur_lexeme);
int get_bound(char** str, info** output, lexeme_t cur_lexeme);

int parts_num(char** str, info** output, lexeme_t cur_lexeme);

char* get_eml_text(FILE* eml_file);

lexeme_t get_lexeme(char** str, info** output);

int parse(char* str, info** output);

char* str_tolower (char* str, size_t str_size);

void free_info (info output, char* buffer);

int print_info(info* output);

//int debug_print(const info* output, char* str);

#endif //PREP_2021_02_PARSER_H
