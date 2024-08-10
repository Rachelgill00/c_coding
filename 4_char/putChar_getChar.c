#include <stdio.h>

int main(){
    char ch;
    printf("Press a key and then press Enter:");

    ch = getchar();
    while(ch != '\n'){
        ch = ch + 32;
        putchar(ch);
        ch = getchar();
    }  
    
    putchar('\n');

    return 0;
}