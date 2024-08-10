#include <stdio.h>
#include <stdlib.h>

//将0-127之间的ASC11字符写到文件中，然后从文件中读出并显示到屏幕上。

int main (){
    FILE *fp;
    char ch;

    if((fp = fopen("demo.bin","wb")) == NULL){
        printf("Failure to open demo.bin!\n");
        exit(0);
    }


    for(int i = 0; i <= 127; i++){
        fputc(i,fp);
    }   

    fclose(fp);

    if((fp = fopen("demo.bin","rb")) == NULL){
        printf("Failure to open demo.bin!\n");
        exit(0);
    }
    /*
    while(fgetc(fp) != EOF){
        ch = fgetc(fp);
        putchar(ch);
    }
    */
    ch = fgetc(fp);
    while(!feof(fp)){
        putchar(ch);
        ch = fgetc(fp);
    }
    
    putchar('\n');
    fclose(fp);
    
    return 0;
}