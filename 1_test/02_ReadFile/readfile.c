#include <stdio.h>
#include <stdlib.h>

#define  INPUT_FILE_NAME "input.txt"
#define INPUT_MAX 1024

int readInput(int *buffer){
    FILE* fd;
    int i;

    if((fd = fopen(INPUT_FILE_NAME, "r")) == NULL){
        printf("Error: Failure to open '%s'!\n", INPUT_FILE_NAME);
        exit(0);
        return -1; 
    }

    /* read input file to get task parameters */
    while(i < INPUT_MAX && fscanf(fd, "%d", &buffer[i]) != EOF) {
        i++;
    }

    if (i > INPUT_MAX){
        printf("Error: Invalid input data in "INPUT_FILE_NAME".\n");
    }
        
	fclose(fd);  

    return i;
}

void printFile(int inputTotal, int inputData[]){
    // Print the result
    for(int i = 0; i < inputTotal; i++){
        printf("%d ", inputData[i]);
    }
}
int main(){
    int inputData[INPUT_MAX];   // Array to store the elements
    int inputTotal;             // Number of elements read

    // Read input data from a file
    inputTotal = readInput(inputData);

    // Read input data from a file
    printFile(inputTotal, inputData);

    printf("\n");

    return 0;
}