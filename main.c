#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "PSform.h"


int main() {
    char data1[6000];
    char data2[6000];
    scanf("%[^\n]%*c", data1);
    scanf("%[^\n]%*c", data2);
    //char data1[] = "-1*x + 3*y*x - 5*z + 0 + 678*j";
    char *input1 = (char *) malloc(6000 * sizeof(char));
    strcpy(input1, data1);
    char *input2 = (char *) malloc(6000 * sizeof(char));
    strcpy(input2, data2);
    struct product_head *form1 = parse_form(input1);
    struct product_head *form2 = parse_form(input2);
    print_psf(form1);
    printf("-----------------------------------------\n");
    print_psf(form2);
    printf("-----------------------------------------\n");
    printf("%d\n", is_equal(&form1, &form2));
    printf("-----------------------------------------\n");
    print_psf(form1);
    printf("-----------------------------------------\n");
    print_psf(form2);
    free_products_list(form1);
    free_products_list(form2);
    return 0;
}
