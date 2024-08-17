#include <stdio.h>

int main(){
    int a = 0, b = 1;
    char c = 'A';
    int *pa = &a, *pb = &b;
    char *pc = &c;

    printf("a is %d, &a is %p, pa is %p, *pa is %d\n",a ,&a, pa, *pa);
    printf("b is %d, &b is %p, pb is %p, *pb is %d\n",b ,&b, pb, *pb);

    return 0;
}