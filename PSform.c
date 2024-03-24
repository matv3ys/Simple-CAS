#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "PSform.h"

#define WITH_COEFS 1
#define WITHOUT_COEFS 0

void free_product(struct product_head* product) {
    struct factor *cur = product->first;
    struct factor *next;
    while (cur != NULL) {
        next = cur->next;
        free(cur);
        cur = next;
    }
    free(product);
}

void free_products_list(struct product_head* product) {
    struct product_head *cur = product;
    struct product_head *next;
    while (cur != NULL) {
        next = cur->next;
        free_product(cur);
        //free(cur);
        cur = next;
    }
}

/*
struct factor *copy_factor(struct factor *src) {
    struct factor *res = NULL;
    struct factor *cur;
    struct factor *new_factor;

    if (src == NULL) {
        return res;
    }

    res = (struct factor *) malloc(sizeof(struct factor));
    if (res == NULL)
        return res;
    memcpy(res, src, sizeof(struct factor));
    res->variable = src->vafactor
    res->coef = src->coef;

    cur = res;
    src = src->next;
    while (src != NULL) {
        new_factor = (struct factor *) malloc(sizeof(struct factor));
        if (new_factor == NULL) {
            free_product(res);
            return NULL;
        }
        memcpy(new_factor, src, sizeof(struct factor));
        new_factor->first = copy_factor(src->first);
        cur->next = new_factor;
        cur = cur->next;
        src = src->next;
    }
    return res;
}


struct product_head *copy_sum(struct product_head *src) {
    struct product_head *res = NULL;
    struct product_head *cur;
    struct product_head *new_product;

    if (src == NULL) {
        return res;
    }

    res = (struct product_head *) malloc(sizeof(struct product_head));
    if (res == NULL)
        return res;
    memcpy(res, src, sizeof(struct product_head));
    res->first = copy_factor(src->first);

    cur = res;
    src = src->next;
    while (src != NULL) {
        new_product = (struct product_head *) malloc(sizeof(struct product_head));
        if (new_product == NULL) {
            free_product(res);
            return NULL;
        }
        memcpy(new_product, src, sizeof(struct product_head));
        new_product->first = copy_factor(src->first);
        cur->next = new_product;
        cur = cur->next;
        src = src->next;
    }
    return res;
}
 */

void print_psf(struct product_head *product) {
    struct factor* cur_factor;
    char variable;
    short is_not_first_product = 0;
    short printed_coef = 0;
    int exponent;
    int coef;

    if (product == NULL) {
        printf("0\n");
        return;
    }

    while (product != NULL) {
        cur_factor = product->first;
        coef = cur_factor->coef;
        if (is_not_first_product) {
            if (coef >= 0) {
                printf(" + ");
            } else {
                printf(" - ");
                coef = abs(coef);
            }
        } else {
            is_not_first_product = 1;
            if (coef < 0) {
                putchar('-');
                coef = abs(coef);
            }
        }
        cur_factor = cur_factor->next;
        if (coef != 1 || cur_factor == NULL) {
            printf("%d", coef);
            printed_coef = 1;
        }
        if (cur_factor != NULL) {
            exponent = cur_factor->coef - 1;
            variable = cur_factor->variable;
            if (printed_coef) {
                putchar('*');
                printed_coef = 0;
            }
            putchar(variable);
            for (int i = 0; i < exponent; i++) {
                printf("*%c", variable);
            }
            cur_factor = cur_factor->next;
        }
        while (cur_factor != NULL) {
            exponent = cur_factor->coef;
            variable = cur_factor->variable;
            for (int i = 0; i < exponent; i++) {
                printf("*%c", variable);
            }
            cur_factor = cur_factor->next;
        }
        product = product->next;
    }
    putchar('\n');
}

/*
 * 1. if products are equal (has same variables and their exponents), returns 0
 * 2. if product a > product b (has higher degree or lexicographically low variable has higher exponent), returns 1
 * 3. returns -1 in other cases
 * 4. with_coefs = 0 if function is used for sorting products in sum
*/
int compare_products(int with_coefs, struct product_head *a, struct product_head *b) {
    struct factor *factor_a;
    struct factor *factor_b;
    char variable_a;
    char variable_b;
    int exponent_a;
    int exponent_b;
    if (a->degree > b->degree)
        return 1;
    if (a->degree < b->degree)
        return -1;
    if (with_coefs) {
        if (a->first->coef > b->first->coef)
            return 1;
        if (b->first->coef > a->first->coef)
            return -1;
    }
    if (a->degree == 0) {
        return 0;
    }
    factor_a = a->first->next;
    factor_b = b->first->next;
    while (factor_a != NULL && factor_b != NULL) {
        variable_a = factor_a->variable;
        variable_b = factor_b->variable;
        if (variable_a < variable_b)
            return 1;
        if (variable_b < variable_a)
            return -1;
        exponent_a = factor_a->coef;
        exponent_b = factor_b->coef;
        if (exponent_a > exponent_b)
            return 1;
        if (exponent_b > exponent_a)
            return -1;
        factor_a = factor_a->next;
        factor_b = factor_b->next;
    }
    return 0;
}

struct product_head *sum_insert_with_merge(struct product_head *list, struct product_head *product) {
    struct product_head *prev;
    struct product_head *next;
    int cmp;

    if (list == NULL)
        return product;
    if ((cmp = compare_products(WITHOUT_COEFS, product, list)) >=  0) {
        if (!cmp) {
            list->first->coef += product->first->coef;
            free_product(product);
            return list;
        }
        product->next = list;
        return product;
    }
    prev = list;
    next = list->next;
    while (1) {
        if (next == NULL) {
            prev->next = product;
            return list;
        }
        if ((cmp = compare_products(WITHOUT_COEFS, product, next)) >= 0) {
            if (!cmp) {
                next->first->coef += product->first->coef;
                free_product(product);
                return list;
            }
            prev->next = product;
            product->next = next;
            return list;
        }
        prev = next;
        next = prev->next;
    }
}

struct product_head *clear_zero_products(struct product_head *products_list) {
    struct product_head *res = NULL;
    struct product_head *end = NULL;
    struct product_head *cur = NULL;
    while (products_list != NULL) {
        if (products_list->first->coef == 0) {
            cur = products_list;
            products_list = products_list->next;
            free_product(cur);
            continue;
        }
        if (res == NULL) {
            res = products_list;
            end = products_list;
            products_list = products_list->next;
            res->next = NULL;
            continue;
        }
        end->next = products_list;
        products_list = products_list->next;
        end = end->next;
        end->next = NULL;
    }
    return res;
}

struct product_head *sort(struct product_head *products_list) {
    struct product_head *res = NULL;
    struct product_head *cur;
    while (products_list != NULL) {
        cur = products_list;
        products_list = products_list->next;
        cur->next = NULL;
        res = sum_insert_with_merge(res, cur);
    }
    res = clear_zero_products(res);
    return res;
}

int is_equal(struct product_head **a, struct product_head **b) {
    struct product_head *cur_a;
    struct product_head *cur_b;

    *a = sort(*a);
    *b = sort(*b);
    cur_a = *a;
    cur_b = *b;
    while (cur_a != NULL && cur_b != NULL) {
        if (compare_products(WITH_COEFS, cur_a, cur_b) != 0)
            return 1;
        cur_a = (cur_a)->next;
        cur_b = (cur_b)->next;
    }
    if (cur_a == NULL && cur_b == NULL)
        return 0;
    else
        return 1;
}

void add(struct product_head **a, struct product_head **b) {
    struct product_head *cur;

    *a  = sort(*a);
    while (*b != NULL) {
        cur = *b;
        *b = (*b)->next;
        cur->next = NULL;
        *a = sum_insert_with_merge(*a, cur);
    }
    *a = clear_zero_products(*a);
}

void negate_sum(struct product_head *a) {
    while (a != NULL) {
        a->first->coef *= -1;
        a = a->next;
    }
}

void subtract(struct product_head **a, struct product_head **b) {
    negate_sum(*b);
    add(a, b);
}

// removes unused characters
char *remove_chars(char *string, size_t size) {
    char c;
    size_t pos = 0;
    for (size_t i = 0; i < size; i++) {
        c = string[i]; //TODO operators priority
        if (c == 42 || c == 43 || c == 45 || (47 < c && c < 58) || (64 < c && c < 91) || (96 < c && c < 123)) {
            string[pos++] = c;
        }
    }
    string[pos] = '\0';
    if (pos < size) {
        char *new_string = (char *) realloc(string, pos + 1);
        if (!new_string) {
            free(string);
            return NULL;
        }
        string = new_string;
    }
    return string;
}

// adds '+' separator before negative product
char *separate_negative_products(char *string, size_t size) {
    char cur, next;
    size_t pos = 0;
    char *new_string = (char *) malloc((size * 3 + 1) * sizeof(char));
    if (!new_string) {
        free(string);
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        cur = string[i];
        next = string[i + 1];
        if (cur == '-')
            new_string[pos++] = '+';
        new_string[pos++] = cur;
        if (cur == '-' && !isdigit(next)) {
            new_string[pos++] = '1';
            new_string[pos++] = '*';
        }
    }
    new_string[pos] = '\0';
    free(string);
    return new_string;
}


char *parse_string(char *string) {
    size_t size;
    if (!string)
        return NULL;
    size = strlen(string);
    if (!size) {
        free(string);
        return NULL;
    }
    string = remove_chars(string, size);
    if (!string) {
        return NULL;
    }
    size = strlen(string);
    if (!size) {
        free(string);
        return NULL;
    }
    string = separate_negative_products(string, size);
    if (!string) {
        return NULL;
    }

    return string;
}

struct factor *product_insert_with_merge(struct factor *first_factor, struct factor *new_factor) {
    struct factor *cur;
    struct factor *next;
    if (first_factor == NULL) {
        return new_factor;
    }
    if (new_factor->variable == '_') {
        first_factor->coef *= new_factor->coef;
        free(new_factor);
        return first_factor;
    }
    cur = first_factor;
    while (1) {
        next = cur->next;
        if (next == NULL) {
            cur->next = new_factor;
            return first_factor;
        }
        if (next->variable == new_factor->variable) {
            next->coef += new_factor->coef;
            free(new_factor);
            return first_factor;
        }
        if (new_factor->variable < next->variable) {
            cur->next = new_factor;
            new_factor->next = next;
            return first_factor;
        }
        cur = next;
    }
}

// TODO: rewrite, split into funcs
struct product_head *create_product(char *product_token) {
    struct product_head *product;
    struct factor *new_factor;
    char *factor_token;
    short is_coef;
    int coef;

    factor_token = strtok(product_token, "*");

    coef = 1;
    is_coef = 0;
    if (factor_token[0] == '-' || isdigit(factor_token[0])) {
        is_coef = 1;
        coef = atoi(factor_token); //TODO -x
    }

    product = (struct product_head *) malloc(sizeof(struct product_head));
    if (product == NULL) {
        return NULL;
    }
    new_factor = (struct factor *) malloc(sizeof(struct factor));
    if (new_factor == NULL) {
        free(product);
        return NULL;
    }
    //*new_factor = (struct factor) {' ', 1, NULL};
    new_factor->variable = '_';
    new_factor->coef = coef;
    new_factor->next = NULL;
    product->degree = 0;
    product->first = new_factor;
    product->next = NULL;


    if (is_coef) {
        factor_token = strtok(NULL, "*");
    }
    while (factor_token != NULL) {
        new_factor = (struct factor *) malloc(sizeof(struct factor));
        if (new_factor == NULL) {
            free_product(product);
            return NULL;
        }
        new_factor->variable = factor_token[0];
        new_factor->coef = 1;
        new_factor->next = NULL;
        product->first = product_insert_with_merge(product->first, new_factor);
        product->degree += 1;
        factor_token = strtok(NULL, "*");
    }
    return product;
}

struct product_head *parse_form(char *string) {
    struct product_head *products_list = NULL;
    struct product_head *products_list_end = NULL;
    struct product_head *product = NULL;
    char *end_of_string;
    char* product_token;

    string = parse_string(string);
    if (string == NULL) {
        return NULL;
    }

    end_of_string = string + strlen(string);

    product_token = strtok(string, "+");
    while (product_token != NULL) {
        size_t offset_next = strlen(product_token) + 1;
        product = create_product(product_token);

        if (product == NULL) {
            free(string);
            return NULL;
        }
        if (product->first->coef != 0) {
            if (products_list == NULL) {
                products_list = product;
                products_list_end = product;
            } else {
                products_list_end->next = product;
                products_list_end = product;
            }
        } else {
            free_product(product);
        }
        if (product_token + offset_next < end_of_string)
            product_token = strtok(product_token + offset_next, "+");
        else
            product_token = NULL;
    }

    free(string);
    return products_list;
}