#include <stdio.h>
#include <stdlib.h>
#define N 80

//从键盘输入一串字符，然后把它们添加到文本文件demo.txt的末尾
int main(){
    FILE *fp;
    char str[N];

    if((fp = fopen("demo.txt","w")) == NULL){
        printf("Failure to open demo.txt!\n");
        exit(0);
    }

    //gets(str);
    fgets(str, sizeof(str), stdin);
    fputs(str,fp);

    fclose(fp);

    if((fp = fopen("demo.txt","r")) == NULL){
        printf("Failure to open demo,txt!\n");
        exit(0);
    }

    fgets(str,N,fp);
    puts(str);

    fclose(fp);

    return 0;
}