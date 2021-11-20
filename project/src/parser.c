#include "parser.h"

int get_info(char** str, info** output, lexeme_t cur_lexeme) {
    if (str == NULL || *str == NULL || output == NULL || *output == NULL) {
        return FAIL;
    }
    size_t from_size = DEF_MEM_INFO;
    size_t to_size = DEF_MEM_INFO;
    size_t seek = -1;
    size_t mem_counter = 0;

    char* tmp;
    char* from_beg = (*output) -> from;
    char* to_beg = (*output) -> to;
    char* date_beg = (*output) -> date;

    switch (cur_lexeme) {
        case L_FROM: {
            if ((*output)->from) {
                return SUCCESS;
            } else {
                (*output)->from = malloc(DEF_MEM_INFO);
                if ((*output)->from == NULL) {
                    printf(MEMALLOC_ERR);
                    return FAIL;
                }
                from_beg = (*output) -> from;
            }
            break;
        }
        case L_TO: {
            if ((*output)->to) {
                return SUCCESS;
            } else {
                (*output)->to = malloc(DEF_MEM_INFO);
                if ((*output)->to == NULL) {
                    printf(MEMALLOC_ERR);
                    return FAIL;
                }
                to_beg = (*output) -> to;
            }
            break;
        }
        case L_DATE: {
            if ((*output)->date) {
                return SUCCESS;
            } else {
                (*output)->date = malloc(DEF_MEM_INFO);
                if ((*output)->date == NULL) {
                    printf(MEMALLOC_ERR);
                    return FAIL;
                }
                date_beg = (*output) -> date;
            }
            break;
        }
        default:
            printf("error");
            return FAIL;
    }
    while (**str == ' ' || **str == '\r') {
        ++(*str);
    }
    while (**str) {
        if (**str == '\r') {
            ++(*str);
        } else if (**str == '\n') {
            if (*(*str + 1) == '\r') {
                ++(*str);
            }
            if (*(*str + 1) == ' ' || *(*str + 1) == '\t') {
                ++(*str);
            } else {
                if (cur_lexeme == L_FROM) {
                    if (from_size <= mem_counter) {
                        tmp = realloc (from_beg, (from_size + DEF_MEM_INFO));
                        if (tmp == NULL) {
                            printf(MEMALLOC_ERR);
                            return FAIL;
                        }
                        from_beg = tmp;
                        (*output) -> from = from_beg + seek;
                    }
                    *(*output) -> from = '\0';
                    (*output) -> from = from_beg;
                } else if (cur_lexeme == L_TO) {
                    if (to_size <= mem_counter) {
                        tmp = realloc (to_beg, (to_size + DEF_MEM_INFO));
                        if (tmp == NULL) {
                            printf(MEMALLOC_ERR);
                            return FAIL;
                        }
                        to_beg = tmp;
                        (*output) -> to = to_beg + seek;
                    }
                    *(*output) -> to = '\0';
                    (*output) -> to = to_beg;
                } else {
                    *(*output) -> date = '\0';
                    (*output) -> date = date_beg;
                }
                return SUCCESS;
            }
        } else {
            switch (cur_lexeme) {
                case L_FROM:
                    *(*output) -> from = **str;
                    ++seek;
                    ++mem_counter;
                    if (from_size <= mem_counter) {
                        tmp = realloc (from_beg, (from_size + DEF_MEM_INFO));
                        if (tmp == NULL) {
                            printf(MEMALLOC_ERR);
                            return FAIL;
                        }
                        from_beg = tmp;
                        (*output) -> from = from_beg + seek;
                        from_size += DEF_MEM_INFO;
                    }
                    ++((*output) -> from);
                    ++(*str);
                    break;
                case L_TO:
                    *(*output) -> to = **str;
                    ++seek;
                    ++mem_counter;
                    if (to_size <= mem_counter) {
                        tmp = realloc (to_beg, (to_size + DEF_MEM_INFO));
                        if (tmp == NULL) {
                            printf(MEMALLOC_ERR);
                            return FAIL;
                        }
                        to_beg = tmp;
                        (*output) -> to = to_beg + seek;
                        to_size += DEF_MEM_INFO;
                    }
                    ++((*output) -> to);
                    ++(*str);
                    break;
                case L_DATE:
                    *(*output) -> date = **str;
                    ++(*output) -> date;
                    ++(*str);
                    break;
                default:
                    return FAIL;
            }
        }
    }
    return FAIL;
}

int get_cont_t(char** str, info** output, lexeme_t cur_lexeme) {
    if (str == NULL || *str == NULL || output == NULL || *output == NULL) {
        return FAIL;
    }

    if (cur_lexeme != L_CONT_T) {
        return FAIL;
    }
    while (**str == ' ') {
        ++(*str);
    }
    switch(**str) {
        case 'M':
        case 'm':
            if (str_tolower(*str, 9) == NULL) {
                return FAIL;
            }
            if (strncmp(*str, "multipart", 9) == 0) {
                (*output) -> cont_t = MULTIPART_T;
                *str += 9;
                return SUCCESS;
            } else {
                (*output) -> cont_t = PLAIN_T;
                (*output) -> parts_num = 1;
                return SUCCESS;
            }
        default:
            (*output) -> cont_t = PLAIN_T;
            while (**str) {
                if (**str == '\n') {
                    break;
                }
                ++(*str);
            }
            return SUCCESS;
    }
}

int get_bound(char** str, info** output, lexeme_t cur_lexeme) {
    if (str == NULL || *str == NULL || output == NULL || *output == NULL) {
        return FAIL;
    }

    if (cur_lexeme != L_BOUND || (*output) -> cont_t != MULTIPART_T) {
        return FAIL;
    }

    size_t bound_size = DEF_MEM_BOUND;
    size_t mem_counter = 0;
    size_t seek = -1;
    void* tmp;

    (*output) -> boundary = malloc(DEF_MEM_BOUND);
    if ((*output) -> boundary == NULL) {
        printf(MEMALLOC_ERR);
        return FAIL;
    }
    char* bound_beg = (*output) -> boundary;
    while (**str == ' ' || **str == '"' || **str == '\r') {   // propusk vseh '"', '\r', i probelov pered samim razdelitelem
        ++(*str);
    }

    while (**str) {
        if (**str == '\r') {
            if (*(*str + 1) == '\n') {

                if (bound_size <= mem_counter) {
                    tmp = realloc (bound_beg, (bound_size + DEF_MEM_BOUND));
                    if (tmp == NULL) {
                        printf(MEMALLOC_ERR);
                        return FAIL;
                    }
                    bound_beg = tmp;
                    (*output) -> boundary = bound_beg + seek;
                    bound_size += DEF_MEM_BOUND;
                }
                *(*output) -> boundary = '\0';
                (*output) -> boundary = bound_beg;
                ++(*str);

                return SUCCESS;
            }
            ++(*str);
        } else if (**str == '"' || **str == ' ') {
            if (bound_size <= mem_counter) {
                tmp = realloc (bound_beg, (bound_size + DEF_MEM_BOUND));
                if (tmp == NULL) {
                    printf(MEMALLOC_ERR);
                    return FAIL;
                }
                bound_beg = tmp;
                (*output) -> boundary = bound_beg + seek;
                bound_size += DEF_MEM_BOUND;
            }
            *(*output) -> boundary = '\0';
            (*output) -> boundary = bound_beg;
            ++(*str);
            return SUCCESS;
        } else if (**str == '\n') {
            if (*(*str + 1) == ' ') {
                ++(*str);
                while (**str == ' ' || **str == '\t' || **str == '\r') {
                    ++(*str);
                }
            } else {
                if (bound_size <= mem_counter) {
                    tmp = realloc (bound_beg, (bound_size + DEF_MEM_BOUND));
                    if (tmp == NULL) {
                        printf(MEMALLOC_ERR);
                        return FAIL;
                    }
                    bound_beg = tmp;
                    (*output) -> boundary = bound_beg + seek;
                    bound_size += DEF_MEM_BOUND;
                }
                *(*output) -> boundary = '\0';
                (*output) -> boundary = bound_beg;
                return SUCCESS;
            }
        } else {
            *(*output) -> boundary = **str;
            ++seek;
            ++mem_counter;
            if (bound_size <= mem_counter) {
                tmp = (char*) realloc(bound_beg, (mem_counter + DEF_MEM_BOUND));
                if (tmp == NULL) {
                    printf(MEMALLOC_ERR);
                    return FAIL;
                }
                bound_beg = tmp;
                (*output) -> boundary = bound_beg + seek;
                bound_size += DEF_MEM_BOUND;
            }
            ++(*output) -> boundary;
        }
        ++(*str);
    }
    return FAIL;
}


int parts_num(char** str, info** output, lexeme_t cur_lexeme) {
    if (str == NULL || *str == NULL || output == NULL || *output == NULL) {
        return FAIL;
    }
    if (cur_lexeme != L_ENDL) {
        printf("wrong lex\n");
        return FAIL;
    }
    while (**str == ' ' || **str == '\n' || **str == '\r' || **str == '\t') {
        ++(*str);
        if (**str == '\0') {
            return SUCCESS;
        }
    }
    if ((*output) -> cont_t == NO_TYPE) {
        (*output) -> cont_t = PLAIN_T;
    }

    if ((*output) -> cont_t) {
        if ((*output) -> cont_t == PLAIN_T) {
            while (**str) {
                if (**str == '\n' || **str == ' ' || **str == '\t' || **str == '\r') {
                    ++(*str);
                    if (**str == EOF) {
                        return SUCCESS;
                    }
                } else {
                    (*output) -> parts_num = 1;
                    return SUCCESS;
                }
            }
        } else {
            if ((*output) -> boundary == NULL) {
                (*output) -> parts_num = 1;
            }
            while (**str) {
                if (get_lexeme(str, output) == L_DIVIDER) {
                    while (**str) {
                        if (**str != '\n') {
                            ++(*str);
                        } else {
                            break;
                        }
                    }
                    while (**str == '\n' || **str == ' ' || **str == '\t' || **str == '\r') {  // propuskaem vse \n \t i probeli posle divider'a
                        ++(*str);
                    }
                    while (**str) {
                        if (**str == ':') {
                            if (*(*str - 1) && *(*str + 1)) {
                                ++((*output) -> parts_num);
                                break;
                            }
                        }
                        else {
                            ++(*str);
                        }
                    }
                    if (**str == '\0') {    // esli posle divider'a est' text, to pribavlyaem chislo partov
                        return SUCCESS;
                    }
                }
            }
            return SUCCESS;   // kogda str == EOF, zakanchivaem parse
        }
    }
    printf("parts fail\n");
    return FAIL;
}

rule_t syntax[ROW_NUM][COL_NUM] =
                //     L_FROM                        L_TO                L_DATE                         L_CONT_T                     L_BOUND                   L_ENDL
/*S_HEADERS*/{  { {S_HEADERS, get_info},    {S_HEADERS, get_info},      {S_HEADERS, get_info},        {S_CONT_T, get_cont_t},    {S_HEADERS, NULL},         {S_ENDL, parts_num}, },
/*S_CONT_T*/    { {S_HEADERS, get_info},   {S_HEADERS, get_info},      {S_HEADERS, get_info},         {S_ERR, NULL},            {S_HEADERS, get_bound},   {S_ENDL, parts_num}, },
/*S_ENDL*/      { {S_ERR, NULL},                {S_ERR, NULL},          {S_ERR, NULL},                 {S_ERR, NULL},             {S_ENDL, NULL},         {S_ENDL, parts_num}, }  };

char* get_eml_text(FILE* eml_file) {
    if (eml_file == NULL) {
        return NULL;
    }
    char* eml_text = (char*) malloc(1);
    if (eml_text == NULL) {
        printf(MEMALLOC_ERR);
        return NULL;
    }
    size_t text_size = 0;
    while (fread(eml_text, 1, 1, eml_file)) {
        text_size++;
    }
    fseek(eml_file, 0, SEEK_SET);
    if (text_size < 1) {
        printf("Empty file!");
        return NULL;
    }

    char* tmp = realloc(eml_text, (text_size + 2));
    if (tmp == NULL) {
        printf(MEMALLOC_ERR);
        return NULL;
    } else {
        eml_text = tmp;
    }
    *eml_text = '\n';
    fread((eml_text + 1), 1, text_size, eml_file);
    eml_text[text_size] = '\0';
    fclose(eml_file);
    return eml_text;
}

lexeme_t get_lexeme(char** str, info** output) {
    if (str == NULL || *str == NULL || output == NULL || *output == NULL) {
        return FAIL;
    }
    while (**str) {
        if ((*output) -> boundary != NULL) {
            if ((**str) == (*(*output) -> boundary)) {
                if (strncmp(*str, (*output) -> boundary, strlen((*output) -> boundary)) == 0) {
                    return L_DIVIDER;
                }
            }
        }
        switch (**str) {
            case 'F':
            case 'f':
                if (*(*str - 1) == '\n') {
                    if (str_tolower(*str, 5) == NULL) {
                        exit(1);
                    }
                    if (strncmp(*str, "from:", 5) == 0) {
                        *str += 5;
                        return L_FROM;
                    } else {
                        ++(*str);
                        break;
                    }
                }
                ++(*str);
                break;
            case 'T':
            case 't':
                if (*(*str - 1) == '\n') {
                    if (str_tolower(*str, 3) == NULL) {
                        exit(1);
                    }
                    if (strncmp(*str, "to:", 3) == 0) {
                        *str += 3;
                        return L_TO;
                    } else {
                        ++(*str);
                        break;
                    }
                }
                ++(*str);
                break;
            case 'D':
            case 'd':
                if ((*(*str - 1)) == '\n') {
                    if (str_tolower(*str, 5) == NULL) {
                        exit(1);
                    }
                    if (strncmp(*str, "date:", 5) == 0) {
                        *str += 5;
                        return L_DATE;
                    } else {
                        ++(*str);
                        break;
                    }
                }
                ++(*str);
                break;
            case 'C':
            case 'c':
                if (*(*str - 1) == '\n') {
                    if(str_tolower(*str, 13) == NULL) {
                        exit(1);
                    }
                    if (strncmp(*str, "content-type:", 13) == 0) {
                        *str += 13;
                        return L_CONT_T;
                    } else {
                        ++(*str);
                        break;
                    }
                }
                ++(*str);
                break;
            case 'B':
            case 'b':
                if (*(*str - 1) == ' ' || *(*str - 1) == '\t' || *(*str - 1) == ';') {
                    if (strncmp(*str, "boundary", 8) == 0 || strncmp(*str, "BOUNDARY", 8) == 0) {
                        *str += 8;
                        while (**str == ' ') {
                            ++(*str);
                        }
                        if (**str == '=') {
                            ++(*str);
                            return L_BOUND;
                        } else {
                            ++(*str);
                            break;
                        }
                    } else {
                        ++(*str);
                        break;
                    }
                }
                else {
                    ++(*str);
                }
                break;
            case '\n':
                if (*(*str + 1) == '\r') {
                    ++(*str);
                    if (*(*str + 1) == '\n') {
                        while (**str == '\n' || **str == '\r' || **str == ' ' || **str == '\t') {
                            ++(*str);
                        }
                        return L_ENDL;
                    }
                    break;
                }
                if (*((*str) - 1) == '\n') {
                    while (**str == '\n' || **str == '\r' || **str == ' ' || **str == '\t') {
                        ++(*str);
                    }
                    return L_ENDL;
                }
                    ++(*str);
                    break;
            default:
                if (**str == '\0') {
                    return L_EOF;
                }
                ++(*str);
                break;
            }
        }
    return L_EOF;
}

int parse(char* str, info** output) {
    if (str == NULL || output == NULL) {
        return FAIL;
    }
    ++str;
    state_t state = S_HEADERS;
    (*output) -> cont_t = 0;
    (*output) -> parts_num = 0;
    lexeme_t lexeme;
    rule_t rule;
    while (*str) {
        lexeme = get_lexeme(&str, output);
        if (lexeme == L_EOF) {
            return SUCCESS;
        }
        rule = syntax[state][lexeme];
        if (rule.state == S_ERR) {
            printf("parse() fail");
            return FAIL;
        } else if (rule.state == S_ENDL) {
            if (rule.action(&str, output, lexeme) == FAIL) {
                printf("action failed\n");
                return FAIL;
            }
            return SUCCESS;
        } else {
            if (rule.action == NULL);
            else if (rule.action(&str, output, lexeme) == FAIL) {
                printf("action failed\n");
                return FAIL;
            }
        }
        state = rule.state;
        ++str;
    }
    return SUCCESS;
}

char* str_tolower (char* str, size_t str_size) {
    if (str == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < str_size; ++i) {
        str[i] = (char) tolower(str[i]);
    }
    return str;
}

void free_info (info output, char* buffer) {
    free(output.from);
    free(output.to);
    free(output.date);
    free(output.boundary);
    free(buffer);
}

int print_info(info* output) {
    if (output -> from == NULL) {
        printf("|");
    } else {
        printf("%s|", (output -> from));
    }
    if (output -> to == NULL) {
        printf("|");
    } else {
        printf("%s|", (output -> to));
    }
    if (output -> date == NULL) {
        printf("|");
    } else {
        printf("%s|", (output -> date));
    }
    printf("%u", (output -> parts_num));
    return SUCCESS;
}