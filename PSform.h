#ifndef INTERNTASK_PSFORM_H
#define INTERNTASK_PSFORM_H

struct factor {
    char variable; // variable == "_" is for product coefficient
    int coef; // product coefficient or exponent
    struct factor *next;
};

struct product_head {
    int degree;
    struct factor *first;
    struct product_head *next;
};

struct product_head *parse_form(char *string);
void free_products_list(struct product_head* product);
void print_psf(struct product_head*);
int is_equal(struct product_head *a, struct product_head *b);
#endif //INTERNTASK_PSFORM_H
