#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "PSform.h"
#include <time.h>

char *get_str() {
    char buf[11] = {0};
    char *res = NULL;
    int len = 0;
    int n = 0;

    do {
        n = scanf("%10[^\n]", buf);
        if (n < 0) {
            if (!res) {
                return NULL;
            }
        } else if (n > 0) {
            int chunk_len = strlen(buf);
            int str_len = len + chunk_len;
            res = realloc(res, str_len + 1);
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        } else {
            scanf("%*c");
        }
    } while (n > 0);

    if (len > 0) {
        res[len] = '\0';
    } else {
        res = calloc(1, sizeof(char));
    }
    return res;
}

int check_operation(char operation) {
    switch (operation) {
        case '=':;
        case '+':;
        case '-':;
        case '*':
            return 0;
        default:
            return 1;
    }
}

int main() {
    //clock_t t;
    char operation;
    char *input_form_1;
    char *input_form_2;
    struct product_head *form_1;
    struct product_head *form_2;
    operation = getchar();
    if (getchar() != '\n' || check_operation(operation)) {
        printf("Error on reading operation code\n");
        return 1;
    }
    input_form_1 = get_str();
    if (input_form_1 == NULL) {
        printf("Error on reading 1st form\n");
        return 1;
    }
    input_form_2 = get_str();
    if (input_form_2 == NULL) {
        printf("Error on reading 2nd form\n");
        free(input_form_1);
        return 1;
    }

    //t = clock();
    form_1 = parse_form(input_form_1);
    form_2 = parse_form(input_form_2);
    switch (operation) {
        case '=':
            printf("%s\n", is_equal(&form_1, &form_2) ? "not equal" : "equal");
            break;
        case '+':
            add(&form_1, &form_2);
            print_psf(form_1);
            break;
        case '-':
            subtract(&form_1, &form_2);
            print_psf(form_1);
            break;
        default:
            printf("Runtime error\n");
    }
    free_products_list(form_1);
    free_products_list(form_2);
    //t = clock() - t;
    //double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    //printf("psf took %f seconds to execute \n", time_taken);
    return 0;
}
