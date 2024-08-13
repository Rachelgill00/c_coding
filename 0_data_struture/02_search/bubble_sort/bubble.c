#include <stdio.h>
#include <stdlib.h>

#define INPUT_MAX 1024                      // Maximum number of elements
#define INPUT_FILE_NAME "input_sort.txt"    // Input file containing input data to sort (+ the number of elements)

// Read input data from a file and write the data into buffer
int readInput(int* buffer)
{
    FILE* fd;    
    int dataTotal;
    int i;

    fd = fopen(INPUT_FILE_NAME, "r");
	if (fd == NULL)	{
		printf("Error: Failed to open '%s'.\n", INPUT_FILE_NAME);
		return -1;
	}

	/* read input file to get task parameters */
	fscanf(fd, "%d \n", &dataTotal);
    if (dataTotal > INPUT_MAX) {
        printf("The number of elements exceeds the limit %d.\n", INPUT_MAX);
        return -1;
    }

	for (i = 0; i < dataTotal; i++) {
		fscanf(fd, "%d ", &buffer[i]);
    }
   
    return dataTotal;
}

// Swap two elements
void swapVariable(int* a, int* b)
{
    int temp = *a;
    
    *a = *b;
    *b = temp;
}

// Implement the bubble sort algorithm
void bubbleSort(int dataTotal, int* dataArray)
{
    int i,j;

    for (i = 0; i < dataTotal; i++) {
        for (j = 0; j < dataTotal - i - 1; j++) {
            if (dataArray[j] > dataArray[j+1])
                swapVariable(&dataArray[j], &dataArray[j+1]);
        }
    }
}

void main(void)
{
    int inputTotal;                         // Number of elements to sort
    int inputData[INPUT_MAX];               // Elements to sort
    int i;

    // Read input data from a file
    if ((inputTotal = readInput(inputData)) < 1)
        printf("Error: Invalid input data in "INPUT_FILE_NAME".\n");

    // Sort the data
    bubbleSort(inputTotal, inputData);

    // Print the result
    for(i = 0; i < inputTotal; i++) {
        printf("%d ",inputData[i]);
    } 

    printf("\n");
}