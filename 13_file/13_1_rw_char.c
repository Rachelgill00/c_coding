#include <stdio.h>
#include <stdlib.h>

//从键盘键入一串字符，然后把它们转存到磁盘文件上。

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
    //注意：使用getchar时，是先将所有字符送入缓冲区，
    //知道键入“回车换行符”后才从缓冲区中诸葛读出并赋值给变量ch
    //write " I am a student " to “demo.txt”
    ch = getchar();
    while(ch != '\n'){
        fputc(ch, fp);
        ch = getchar();
    }    

    fclose(fp);

    return 0;
}