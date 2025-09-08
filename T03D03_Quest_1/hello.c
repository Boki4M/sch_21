#include <stdio.h>

int main(void) {
    int d = 10;
    int *gpt = &d;
    int *x = gpt;

    scanf("%d",&d);
    printf("d = %d, gpt = %d, x = %d \n", d, *gpt, *x);

    *gpt = 100;

    printf("\nd = %d, gpt = %d, x = %d", d, *gpt, *x);

    return 0;
}