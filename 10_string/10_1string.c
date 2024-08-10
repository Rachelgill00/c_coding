#include <stdio.h>
#define N 12

int main(){
    char name[N];
    
    printf("Enter your name:");

    fgets(name,sizeof(name),stdin);
    printf("Hello %s!\n", name);
    
    //puts(name);

    return 0;
}