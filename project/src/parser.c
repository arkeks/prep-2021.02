#include "parser.h"

// lexemes: "from:"  "to:" "date:"  "content-type:"  "multipart:"  "boundary="  '\n' "str"
// actions: get && print_info() (for "from:"  "to:" "date:") (if there's no "str" after 'lexeme:', error);
// get_con_type() (multipart or other); get_boundary() (if multipart)
// parts_num() (in background after getting boundary)


int get_info(char** str, info** output, lexeme_t cur_lexeme) {
    if (str == NULL || *str == NULL || output == NULL || *output == NULL) {
        exit(999);
    }
    //printf("in get_info()\n");
    //printf("cur_lex is %d\n", cur_lexeme);
    //size_t from_size = 0;
    //size_t to_size = 0;
    //size_t date_size = 0;
    //size_t mem_counter = 0;

    //char* tmp;
    char* from_beg;
    char* to_beg;
    char* date_beg;

    //printf("in get_inf(); cur_lex is %d\n", cur_lexeme);
    //debug_print(*output, *str);

    switch (cur_lexeme) {
        case L_FROM: {
            if ((*output)->from) {
                return SUCCESS;
            } else {
                (*output)->from = malloc(1000);
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
                (*output)->to = malloc(1000);
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
                (*output)->date = malloc(1000);
                if ((*output)->date == NULL) {
                    printf(MEMALLOC_ERR);
                    return FAIL;
                }
                date_beg = (*output) -> date;
            }
            break;
        }
        default:
            printf("what?");
            return FAIL;
    }
    while (**str == ' ' || **str == '\r') {
        ++(*str);
    }
    while (**str) {
        if (**str == '\r') {
            //printf("CAN'T PLACE r IN INFO\n");
            ++(*str);
        } else if (**str == '\n') {
            if (*(*str + 1) == '\r') {
                //printf("new line\n");
                ++(*str);
            }
            if (*(*str + 1) == ' ' || *(*str + 1) == '\t') {
                ++(*str);
                while(**str == ' ' || **str == '\t' || **str == '\r') {
                    ++(*str);
                }
            } else {
                if (cur_lexeme == L_FROM) {
                    *(*output) -> from = '\0';
                    (*output) -> from = from_beg;
                    //printf("from: %s\n", (*output) -> from);
                } else if (cur_lexeme == L_TO) {
                    *(*output) -> to = '\0';
                    (*output) -> to = to_beg;
                    //printf("from: %s\n", (*output) -> from);
                    //printf("to: %s\n", (*output) -> to);
                } else {
                    *(*output) -> date = '\0';
                    (*output) -> date = date_beg;
                    //printf("from: %s\n", (*output) -> from);
                    //printf("to: %s\n", (*output) -> to);
                    //printf("date: %s\n", (*output) -> date);
                }
                return SUCCESS;
            }
        } else {
            switch (cur_lexeme) {
                case L_FROM:
                    /*if (from_size <= mem_counter) {
                        if ((*output) -> from != NULL) {
                            tmp = (char *) realloc((*output) -> from, (mem_counter + 30));
                            if (tmp == NULL) {
                                printf(MEMALLOC_ERR);
                                //free(tmp);
                                return FAIL;
                            }
                            (*output) -> from = tmp;
                            from_beg = (*output) -> from;
                            from_size += 30;
                        }
                    }*/
                    //++mem_counter;
                    /*if (**str == '\r') {
                        printf("CAN'T PLACE r IN INFO\n");
                        ++(*str);
                        break;
                    }*/
                    *(*output) -> from = **str;
                    //printf("%c%c ", *(output -> from - 1), *(output -> from));
                    ++((*output) -> from);
                    ++(*str);
                    break;
                case L_TO:
                    /*if (to_size <= mem_counter) {
                        if ((*output) -> to != NULL) {
                            tmp = (char *) realloc((*output) -> to, (mem_counter + 30));
                            if (tmp == NULL) {
                                printf(MEMALLOC_ERR);
                                //free(tmp);
                                return FAIL;
                            }
                            (*output) -> to = tmp;
                            to_beg = (*output) -> to;
                            to_size += 30;
                        }
                    }*/
                    //++mem_counter;
                    /*if (**str == '\r') {
                        printf("CAN'T PLACE r IN INFO\n");
                        ++(*str);
                        break;
                    }*/
                    *(*output) -> to = **str;
                    ++(*output) -> to;
                    ++(*str);
                    break;
                case L_DATE:
                    /*if (date_size <= mem_counter) {
                       if ((*output) -> date != NULL) {
                            tmp = (char *) realloc((*output) -> date, (mem_counter + 30));
                            if (tmp == NULL) {
                                printf(MEMALLOC_ERR);
                                //free(tmp);
                                return FAIL;
                            }
                           (*output) -> date = tmp;
                           date_beg = (*output) -> date;
                           date_size += 30;
                        }
                    }*/
                    //++mem_counter;
                    /*if (**str == '\r') {
                        printf("CAN'T PLACE r IN INFO\n");
                        ++(*str);
                        break;
                    }*/
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
        exit(999);
    }
    //printf("in get_cont_t(); cur_lex is %d\n", cur_lexeme);
    //if (debug_print(*output, *str) == FAIL) {
    //    return FAIL;
    //}
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
                exit(999);
            }
            if (strncmp(*str, "multipart", 9) == 0) {
                (*output) -> cont_t = MULTIPART_T;
                *str += 9;
                return SUCCESS;
            } else {
                (*output) -> cont_t = PLAIN_T;
                (*output) -> parts_num = 1;
                //printf("plain_t (%u)\n", (*output) -> cont_t);
                return SUCCESS;
            }
        default:
            //printf("in default of cont_t\n");
            (*output) -> cont_t = PLAIN_T;
            while (**str) {
                if (**str == '\n') {
                    break;
                }
                ++(*str);
            }
            //output -> parts_num = 1; ???
            //printf("plain_t (%u)\ncur_letter is %c\n", (*output) -> cont_t, **str);
            return SUCCESS;
    }
}

int get_bound(char** str, info** output, lexeme_t cur_lexeme) {
    if (str == NULL || *str == NULL || output == NULL || *output == NULL) {
        exit(999);
    }
    //printf("in get_bound()\n");
    //printf("start is on %c\n", **str);
    //if (debug_print(*output, *str) == FAIL) {
    //    return FAIL;
    //}

    if (cur_lexeme != L_BOUND || (*output) -> cont_t != MULTIPART_T) {
        return FAIL;
    }

    //size_t bound_size = 0;
    //size_t mem_counter = 0;


    //void* tmp;

    (*output) -> boundary = malloc(150);
    if ((*output) -> boundary == NULL) {
        printf(MEMALLOC_ERR);
        return FAIL;
    }
    char* bound_beg = (*output) -> boundary;
    while (**str == ' ' || **str == '"' || **str == '\r') {
        ++(*str);
    }

    while (**str) {
        if (**str == '\r') {
            if (*(*str + 1) == '\n') {
                *(*output) -> boundary = '\0';
                (*output) -> boundary = bound_beg;
                ++(*str);
                printf("char after bound %c\n", **str);
                return SUCCESS;
            }
            ++(*str);
        } else if (**str == '"') {
            *(*output) -> boundary = '\0';
            (*output) -> boundary = bound_beg;
            ++(*str);
            printf("char after bound %c\n", **str);
            return SUCCESS;
        } else if (**str == '\n') {
            if (*(*str + 1) == ' ') {
                ++(*str);
                while (**str == ' ' || **str == '\t' || **str == '\r') {
                    ++(*str);
                }
            } else {
                *(*output) -> boundary = '\0';
                (*output) -> boundary = bound_beg;
                return SUCCESS;
            }
        } else {
            /*if (bound_size <= mem_counter) {
                if ((*output) -> boundary != NULL) {
                    tmp = (char*) realloc((*output) -> boundary, (mem_counter + 30));
                    if (tmp == NULL) {
                        printf(MEMALLOC_ERR);
                        return FAIL;
                    }
                }
                (*output) -> boundary = tmp;
                bound_beg = (*output) -> boundary;
                bound_size += 30;
            }*/
            *(*output) -> boundary = **str;
            //++mem_counter;
            ++(*output) -> boundary;
        }
        ++(*str);
    }
    return FAIL;
}


int parts_num(char** str, info** output, lexeme_t cur_lexeme) {
    if (str == NULL || *str == NULL || output == NULL || *output == NULL) {
        exit(999);
    }
    if (cur_lexeme != L_ENDL) {
        printf("wrong lex\n");
        return FAIL;
    }
    printf("in parts_num()\n");
    printf("%s\n", (*output) -> boundary);
    //print_info(*output);
    //printf("\n");
    //debug_print(*output, *str);
    if ((*output) -> cont_t) {
        //printf("in plain 0\n");
        if ((*output) -> cont_t == PLAIN_T) {
            while (**str) {
                if (**str == '\n' || **str == ' ' || **str == '\t' || **str == '\r') {
                    //printf("in plain\n");
                    ++(*str);
                    if (**str == EOF) {
                        return SUCCESS;    // kogda str == EOF, zakanchivaem parse
                    }
                } else {
                    //printf("in plain 2\n");
                    (*output) -> parts_num = 1;
                    return SUCCESS;
                }
            }
        } else {  // esli multipart
            while (**str) {
                printf("%c\n", **str);
                if (get_lexeme(str, output) == L_DIVIDER) {
                    printf("got bound\n");
                    //if (*(*str - 2) == '\n' && *(*str - 1) == '\n') {    // esli do divider'a bila pustaya stroka
                        //*str += strlen((*output) -> boundary);
                        //printf("letter after bound is %c\n", **str);
                        //if (**str == '\n') {
                            //printf("cur_let is %c", **str);
                            while (**str) {
                                //printf("running to endl\n");
                                if (**str != '\n') {
                                    ++(*str);
                                } else {
                                    break;
                                }
                            }
                            while (**str == '\n' || **str == ' ' || **str == '\t' || **str == '\r') {  // propuskaem vse \n \t i probeli posle divider'a
                                ++(*str);
                            }
                            if (**str == '\0') {    // esli posle divider'a est' text, to pribavlyaem chislo partov
                                return SUCCESS;
                            }
                            //printf("incr the parts_num\n");
                            ++((*output) -> parts_num);
                        //} else {
                            //printf("no endl after bound\n");
                        //}
                    //}
                }
                ++(*str);
            }
            return SUCCESS;   // kogda str == EOF, zakanchivaem parse
        }
    }
    printf("parts fail\n");
    return FAIL;
}
// CONT - content
rule_t syntax[ROW_NUM][COL_NUM] =
                //     L_FROM                        L_TO                L_DATE                         L_CONT_T                     L_BOUND                   L_ENDL
/*S_HEADERS*/{  { {S_HEADERS, get_info},    {S_HEADERS, get_info},      {S_HEADERS, get_info},        {S_CONT_T, get_cont_t},      {S_ERR, NULL},         {S_ENDL, parts_num}, },
/*S_CONT_T*/    { {S_HEADERS, get_info},   {S_HEADERS, get_info},      {S_HEADERS, get_info},         {S_ERR, NULL},            {S_HEADERS, get_bound},   {S_ENDL, parts_num}, },
/*S_ENDL*/      { {S_ERR, NULL},                {S_ERR, NULL},          {S_ERR, NULL},                 {S_ERR, NULL},              {S_ERR, NULL},         {S_ENDL, parts_num}, }  };

char* get_eml_text(FILE* eml_file) {
    //printf("1");
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
    //printf("1\n");
    if (text_size < 1) {
        printf("Empty file!");
        return NULL;
    }

    char* tmp = realloc(eml_text, (text_size + 2));
    if (tmp == NULL) {
        printf(MEMALLOC_ERR);
        //free(tmp);
        return NULL;
    } else {
        eml_text = tmp;
    }
    //printf("%zu\n", text_size);
    *eml_text = '\n';
    fread((eml_text + 1), 1, text_size, eml_file);
    eml_text[text_size] = '\0';
    fclose(eml_file);
    return eml_text;
}

// lexemes: "from:"  "to:" "date:"  "content-type:"  "boundary="  '\n' "str"

lexeme_t get_lexeme(char** str, info** output) {
    //printf("in get_lexeme()\n");
    if (str == NULL || *str == NULL || output == NULL || *output == NULL) {
        exit(999);
    }
    //printf("%c\n", **str);
    while (**str) {
        //printf("%c\n", **str);
        switch (**str) {
            case 'F':
            case 'f':
                //printf("in F\n");
                //printf("in 'F' 2 prev_let is %c; cur_let is %c; next_let is %c\n", *((*str) - 1), **str, *((*str) + 1));
                if (*(*str - 1) == '\n') {
                    if (str_tolower(*str, 5) == NULL) {
                        exit(999);
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
                //printf("in 'T' 2 prev_let is %c; cur_let is %c; next_let is %c\n", *((*str) - 1), **str, *((*str) + 1));
                //printf("in T\n");
                if (*(*str - 1) == '\n') {
                    if (str_tolower(*str, 3) == NULL) {
                        exit(999);
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
                //printf("in 'D' 2 prev_let is %c; cur_let is %c; next_let is %c\n", *((*str) - 1), **str, *((*str) + 1));
                //printf("in D\n");
                if ((*(*str - 1)) == '\n') {
                    if (str_tolower(*str, 5) == NULL) {
                        exit(999);
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
                //printf("in 'C' 2 prev_let is %c; cur_let is %c; next_let is %c\n", *((*str) - 1), **str, *((*str) + 1));
                //printf("in C\n");
                if (*(*str - 1) == '\n') {
                    if(str_tolower(*str, 13) == NULL) {
                        exit(999);
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
                //printf("in 'B' 2 prev_let is %c; cur_let is %c; next_let is %c\n", *((*str) - 1), **str, *((*str) + 1));
                //printf("in B\n");
                if (str_tolower(*str, 9) == NULL) {
                    exit(999);
                }
                //if (*(*str - 1) == ' ') {
                if (strncmp(*str, "boundary=", 9) == 0) {
                    *str += 9;
                    return L_BOUND;
                }
                //}
                else {
                    ++(*str);
                }
                break;
            /*case '\r':
                //printf("found r\n");
                if (*(*str + 1) == '\n') {
                    *str += 2;
                    if (**str == '\r') {
                        if (*(*str + 1) == '\n') {
                            printf("found r\n");
                            ++(*str);
                            return L_ENDL;
                        }
                    }
                }
                ++(*str);
                break;*/
            case '\n':
                //printf("in ENDL\n");
                //printf("cur_let is %c\n", **str);
                if (*(*str + 1) == '\r') {
                    ++(*str);
                    if (**str == '\n') {
                        return L_ENDL;
                    }
                }
                if (*((*str) - 1) == '\n') {
                    //printf("in ENDL 111; prev_let is %c; cur_let is %c; next_let is %c\n", *((*str) - 1), **str, *((*str) + 1));
                    ++(*str);
                    return L_ENDL;
                }// else {
                    //printf("in ENDL 2 prev_let is %c; cur_let is %c; next_let is %c\n", *((*str) - 1), **str, *((*str) + 1));
                    ++(*str);
                    break;
                //}
            default:
                //printf("in default\n");
                //printf("in 'default' 2 prev_let is %c; cur_let is %c; next_let is %c\n", *((*str) - 1), **str, *((*str) + 1));
                if ((*output) -> boundary != NULL) {
                    //printf("BOUNDARY NOT NULL");
                    if ((**str) == (*(*output) -> boundary)) {
                        if (strncmp(*str, (*output) -> boundary, strlen((*output) -> boundary)) == 0) {
                            return L_DIVIDER;
                        } else {
                            ++(*str);
                            break;
                        }
                    } else {
                        ++(*str);
                        break;
                    }
                }
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
    //char** str_ptr = str;
    //info** output_ptr = &output;
    //print_info(*output);
    if (str == NULL || output == NULL) {
        return FAIL;
    }
    ++str;
    state_t state = S_HEADERS;
    (*output) -> cont_t = 0;
    (*output) -> parts_num = 0;
    lexeme_t lexeme;
    rule_t rule;
    //debug_print(*output, str);
    //char** l_end
    while (*str) {
        //printf("current letter is %c\n", *str);
        /*if (*str == '\n' && *(str - 1) == '\n') { // esli headers konchilis'
            printf("before parts()\n");
            //debug_print(*output, str);
            if (parts_num(&str, output) == SUCCESS) {
                printf("after parts()\n");
                return SUCCESS;
            }
        }*/
        //printf("before get_lex()\n");
        //print_info(*output);
        //debug_print(*output, str);
        lexeme = get_lexeme(&str, output);
        //printf("after get_lex()\n");
        //print_info(*output);
        //debug_print(*output, str);
        if (lexeme == L_EOF) {
            return SUCCESS;
        }
        rule = syntax[state][lexeme];
        if (rule.state == S_ERR) {
            printf("parse() fail");
            return FAIL;
        } else if (rule.state == S_ENDL) {
            printf("in ENDL state\n");
            //print_info(*output);
            printf("char before parts %c\n", *str);
            if (rule.action(&str, output, lexeme) == FAIL) {
                printf("action failed endl\n");
                return FAIL;
            }
            //printf("HERE\n");
            //print_info(*output);
            return SUCCESS;
        } else {
            //printf("before action()\n");
            //debug_print(*output, str);
            if (rule.action(&str, output, lexeme) == FAIL) {
                printf("action failed\n");
                return FAIL;
            }
            /*printf("--------------after action------------------\n");
            printf("from: %s\n", (*output) -> from);
            printf("to: %s\n", (*output) -> to);
            printf("date: %s\n", (*output) -> date);
            printf("cont_t: %u\n", (*output) -> cont_t);
            printf("--------------------------------------------\n");*/
            //printf("after action()\n");
            //debug_print(*output, str);
        }
        state = rule.state;
        //printf("s_state is %d\n", state);
        ++str;
    }
    //printf("parse() fail");
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


int print_info(info* output) {
    //if (output == NULL || output -> from == NULL || output -> to == NULL || output -> date == NULL) {
    //    printf("error print");
    //    return FAIL;
    //}
    printf("%s|", (output -> from));
    //printf("\n");
    printf("%s|", (output -> to));
    //printf("\n");
    printf("%s|", (output -> date));
    //printf("\n");
    //printf("cont_t: %u\n", (output -> cont_t));
    //printf("\n");
    printf("%u", (output -> parts_num));
    return SUCCESS;
}

/*int debug_print(const info* output, char* str) {
    if (output == NULL || output -> from == NULL || output -> to == NULL || output -> date == NULL) {
        printf("error");
        return FAIL;
    }
    printf("----------------------------\n");
    printf("cur_let is %c\n", *str);
    printf("cur char_address is %p\n", output);
    printf("cur ptr_address is %p\n", &output);
    printf("from: %s\n", output -> from);
    printf("to: %s\n", output -> to);
    printf("date: %s\n", output -> date);
    printf("cont_t: %u\n", output -> cont_t);
    printf("boundary: %s\n", output -> boundary);
    printf("parts_num: %u\n", output -> parts_num);
    printf("----------------------------\n");
    return SUCCESS;
}*/