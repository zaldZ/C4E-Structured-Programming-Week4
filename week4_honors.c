#include <stdio.h>
#include <stdlib.h>

typedef struct btree{int data; struct btree *right; struct btree *left;} btree;

//////////////////////////////////////////////////////////////////////////
//  Reads file 'inputFilePointer' and stores its data in 'inputDataArray'.
void readData(FILE *inputFilePointer, int inputDataArray[], int *inputDataSize){
    *inputDataSize = 0;
    rewind(inputFilePointer);
    while(fscanf(inputFilePointer, "%d", &inputDataArray[*inputDataSize+1]) == 1){ (*inputDataSize)++; }
}

////////////////////////////////////
//  Creates a new node of value 'x'.
btree *newNode(int x, btree *inputLeft, btree *inputRight){
    btree *localNode = malloc(sizeof(btree));
    localNode->data = x;
    localNode->left = inputLeft;
    localNode->right = inputRight;
    return localNode;
}

//////////////////////////////////////////////////////////////
//  Creates a binary tree from an array 'x[]' of size 'xSize'.
btree *createTree(int x[], int xIndex, int xSize){
    if(xIndex >= xSize){ return NULL; }
    return newNode(x[xIndex], createTree(x, 2*xIndex+1, xSize), createTree(x, 2*xIndex+2, xSize));
}

/////////////////////////////////////////////
//  Prints a binary tree in "inorder" format.
void printInorder(btree *inputRoot){
    if(inputRoot != NULL){
        printInorder(inputRoot->left);
        printf("%3d: ", inputRoot->data);
        printInorder(inputRoot->right);
    }
}

/////////////////////////////////////////////////////////////
//  sequence.txt contains twenty integers separated by space:
//
//  1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
/////////////////////////////////////////////////////////////

int main(void){
    FILE *ifp;  //  Input file pointer.
    int rawData[21];    //  Data array in which the first element is the number of data in a file.
    int data[20];   //  Workable data array.

    ifp = fopen("sequence.txt", "r");   // Opening file sequence.txt.
    readData(ifp, rawData, &rawData[0]);    //  Reading file grades.txt and storing its data in the array rawData[].

    int i;
    for(i=1; i < rawData[0]+1; i++){
        data[i-1] = rawData[i]; //  Creating a workable data array.
    }
    
    btree *root=NULL;
    root = createTree(data, 0, rawData[0]); //  Root is a binary tree that contains the elements of data[].
    printInorder(root); //  Inorder printing format.

    fclose(ifp);
    return 0;
}