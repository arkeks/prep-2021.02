#include "utils.h"
#include "is_simple.h"
#include "num_sequence.h"

#define ERR_ARGS_COUNT (-1)
#define ERR_WRONG_FLG (-2)

#define TST_FOO_FIX     1
#define TST_FOO_IMPL    2
#define TST_MOD_IMPL    3
#define TST_MOD_ENUM    4

int main(int argc, const char** argv) {
    if (argc < 3) {
        return ERR_ARGS_COUNT;
    }

    char* end = NULL;
    int test_case = (int) strtol(argv[1], &end, 0);
    if (*end != '\0') {
        return ERR_WRONG_FLG;
    }
    const char* data;
    data = argv[2];

    switch (test_case) {
        case TST_FOO_FIX: {
            int to = (int) strtol(data, &end, 0);
            if (*end != '\0') {
                return ERR_WRONG_FLG;
            }
            int ticks_count = timer_from(to);
            printf("%d\n", ticks_count);
            break;
        }
        case TST_FOO_IMPL: {
            if (argc == 4) {
                int base = (int) strtol(data, &end, 0);
                if (*end != '\0') {
                    return ERR_WRONG_FLG;
                }
                int pow =  (int) strtol(argv[3], &end, 0);
                if (*end != '\0') {
                    return ERR_WRONG_FLG;
                }
                int res = custom_pow(base, pow);
                printf("%i\n", res);
            } else {
                return ERR_ARGS_COUNT;
            }
            break;
        }
        case TST_MOD_IMPL: {
            int num = (int) strtol(data, &end, 0);
            if (*end != '\0') {
                return ERR_WRONG_FLG;
            }
            printf("%d", is_simple(num));
            break;
        }
        case TST_MOD_ENUM: {
            int num = (int) strtol(data, &end, 0);
            if (*end != '\0') {
                return ERR_WRONG_FLG;
            }
            num_sequence(num);
            break;
        }
        default: {
            return ERR_WRONG_FLG;
        }
    }
}
