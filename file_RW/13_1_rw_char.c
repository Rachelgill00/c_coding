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

    //getchar��ʵ"����"����"�ַ���ASCII��ֵ��������"��
    //getchar�ڶ�ȡ��������ʧ�ܵ�ʱ�򣬻᷵��EOF��
    //write " I am a student " to ��demo.txt��
    ch = getchar();
    while(ch != '\n'){
        fputc(ch, fp);
        ch = getchar();
    }

    fclose(fp);

    return 0;
}