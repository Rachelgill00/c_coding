#include <stdio.h>
#include <stdlib.h>

int main(){
    //Init a file pointer
    FILE *fp;
    char ch;

    // Point the file pointer to a file
    // Check if the file has been successfully opened.
    // exit(0) is a Normal operation leads to program exit.
    if ((fp = fopen("demo.txt","w")) == NULL){
        printf("Failure to open the file!");
        exit(0);
    }

    //getchar其实"返回"的是"字符的ASCII码值（整数）"。
    //getchar在读取结束或者失败的时候，会返回EOF。
    //write " I am a student " to “demo.txt”
    ch = getchar();
    while(ch != '\n'){
        fputc(ch, fp);
        ch = getchar();
    }

    fclose(fp);

    return 0;
}