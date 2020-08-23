#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////
//  Reads file 'inputFilePointer' and stores its data in 'inputDataArray'.
void readData(FILE *inputFilePointer, int inputDataArray[], int *inputDataSize){
    *inputDataSize = 0;
    rewind(inputFilePointer);
    while(fscanf(inputFilePointer, "%d", &inputDataArray[*inputDataSize+1]) == 1){ (*inputDataSize)++; }
}

////////////////////////////////////////////////////////////////////////////////////////
//  Prints the data stored in 'inputDataArray' on screen or on file 'outputFilePointer'.
//  'inputType' equals to 's' is for screen printing and 'f' is for file printing.
void printData(int inputDataArray[], int inputDataSize, char inputType, FILE *outputFilePointer){
    int i;
    for(i=0; i < inputDataSize+1; i++){
        if(inputType == 's'){
            printf("%3d\t", inputDataArray[i]);
            if((i+1) % 11 == 0){ printf("\n"); }
        }
        else if(inputType == 'f'){
            fprintf(outputFilePointer, "%3d\t", inputDataArray[i]);
            if((i+1) % 11 == 0){ fprintf(outputFilePointer, "\n"); }
        }      
    }
}

/////////////////////////////////////
//  Returns the average of array 'x'.
double arrayAverage(int x[], int xSize){
    double localSum=0.0;
    int i;
    for(i=0; i < xSize; i++){ localSum += x[i+1]; }
    return localSum/xSize;
}

///////////////////////////////////////////
//  Returns the maximum value of array 'x'.
int arrayMaximum(int x[], int xSize){
    int localMaximum=0;
    while(xSize-- > 1){
        if(localMaximum < x[xSize]){ localMaximum = x[xSize]; }
    }
    return localMaximum;
}

//////////////////////////////////////////////////////////////
//  grades.txt contains twenty integers separated by space:
//
//  47 61 90 24 91 48 36 5 43 53 4 40 15 43 45 84 99 100 77 29
//////////////////////////////////////////////////////////////

int main(){
    FILE *ifp, *ofp;    //  File pointers.
    int data[21];   //  data[0] will be the number that tells you how many data to read;

    ifp = fopen("grades.txt", "r"); //  Opening file grades.txt.
    readData(ifp, data, &data[0]);  //  Reading file grades.txt and storing its data in the array data[].
    printf("Data array:\n");
    printData(data, data[0], 's', NULL);  //  Prints the array data on screen.
    printf("\nAverage: %.3lf\nMaximum: %d", arrayAverage(data, data[0]), arrayMaximum(data, data[0])); // Prints average and maximum of array data on screen.

    ofp = fopen("answer-hw3.txt", "w"); //  Creating a file answer-hw3.txt.
    fprintf(ofp, "Data Array:\n");
    printData(data, data[0], 'f', ofp);   //  Prints the array data on file answer-hw3.txt.
    fprintf(ofp, "\nAverage: %.3lf\nMaximum: %d", arrayAverage(data, data[0]), arrayMaximum(data, data[0])); // Prints average and maximum of array data on file answer-hw3.txt.

    fclose(ifp);
    fclose(ofp);
    return 0;
}