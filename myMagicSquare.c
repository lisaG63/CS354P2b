///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission, CS 354 Fall 2020, Deb Deppeler
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        myMagicSquare.c
// This File:        myMagicSquare.c
// Other Files:      None.
// Semester:         CS 354 Fall 2020
//
// Author:           Weihang Guo
// Email:            wguo63@wisc.edu
// CS Login:         weihang 
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   Fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          None.
//
// Online sources:   None.
//
////////////////////////////////////////////////////////////////////////////////
   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure that represents a magic square
typedef struct {
    int size;      // dimension of the square
    int **magic_square; // pointer to heap allocated magic square
} MagicSquare;

/* Prompts the user for the magic square's size, reads it,
 * checks if it's an odd number >= 3 (if not display the required
 * error message and exit), and returns the valid number.
 */
int getSize() {
    printf("Enter magic square's size (odd integer >=3)\n");
    int size;//the user entered integer
    fscanf(stdin, "%io", &size);//get the integer from the console
    if (size % 2 != 1) {//check if the integer is odd
        printf("Size must be odd.\n");
        exit(1);
    }
    if (size < 3) {//check if the integer is larger than 3
        printf("Size must be >= 3.\n");
        exit(1);
    }
    return size;   
} 

/* Helper function to assign the numbers into the magic square
 * mgsquare the magic square to be filled
 * coordinates the coordinates of the number in the magic square
 * size the number of rows and columns of the magic square
 * number the number to be put into the magic square
 */
void assignNumbers(int **mgsquare, int *coordinates, int size, int number) {
    //assign the number to the give position
    *(*(mgsquare + *coordinates) + *(coordinates + 1)) = number;
    //determine the next pair of coordinates by going down right
    //which simply means incrementing row and column by 1
    int r = *coordinates  + 1;//the next row index
    int c = *(coordinates + 1) + 1;//the next column index
    //if the coordinates is out of the square, wrap around to the first row/column
    if (r > size - 1)
        r = 0;
    if (c > size - 1)
        c = 0;
    //if the position is already filled, move to the left position
    //which means decrementing column by 1
    if (*(*(mgsquare + r) + c) != 0){
        r = *coordinates;
        c = *(coordinates + 1) - 1;
    }
    //update the coordinates array
    *coordinates = r;
    *(coordinates + 1) = c;
}

/* Makes a magic square of size n using the alternate 
 * Siamese magic square algorithm from assignment and 
 * returns a pointer to the completed MagicSquare struct.
 *
 * n the number of rows and columns
 */
MagicSquare *generateMagicSquare(int n) {
    MagicSquare *square = malloc(sizeof(MagicSquare));//declare a MagicSquare
    if (square == NULL) {//check the return value of malloc
        printf("Error creating the square.\n");
        exit(1);
    }
    square -> size = n;//assgin the size value
    square -> magic_square = malloc(sizeof(int) * n);
    if (square -> magic_square == NULL) {//check the return value of malloc
        printf("Error creating the square.\n");
        exit(1);
    }
    for (int i = 0; i < n; i ++) {
        *(square -> magic_square + i) = malloc(sizeof(int) * n);
        if (*(square -> magic_square + i) == NULL) {//check the return value of malloc
            printf("Error creating the square.\n");
            exit(1);
        }
    }
    int *rc = malloc(sizeof(int) * 2);//a 1D array containing a pair of coordinates
    if (rc == NULL) {//check the return value of malloc
        printf("Error creating the square.\n");
        exit(1);
    }
    //the first position which the number 1 goes
    *rc = (n - 1) / 2;
    *(rc + 1) = n - 1;
    //put each number into the magic square
    for (int i = 0; i < n * n; i ++) {
        assignNumbers(square -> magic_square, rc, n, i + 1);
    }
    //free the memory for the array of coordinates
    free(rc);
    rc = NULL;
    return square;    
} 


/* Opens a new file (or overwrites the existing file)
 * and writes the square in the specified format.
 *
 * magic_square the magic square to write to a file
 * filename the name of the output file
 */
void fileOutputMagicSquare(MagicSquare *magic_square, char *filename) {
    FILE *ofp = fopen(filename, "w");//open file
    if (ofp == NULL) {//check the return value of fopen
        printf("Can't open output file %s!\n", filename);
        exit(1);
    }
    fprintf(ofp, "%i\n", magic_square -> size);//write the size into the output file
    for (int i = 0; i < magic_square -> size; i ++) {//write the square into the output file
        for (int j = 0; j < magic_square -> size; j ++) {
            if (j != magic_square -> size - 1) {
                fprintf(ofp, "%i,", *(*(magic_square -> magic_square + i) + j));
            } else {
                fprintf(ofp, "%i\n", *(*(magic_square -> magic_square + i) + j));
            }
        }
    }
    //close the file
    if (fclose(ofp) != 0) {
        printf("Error while closing the file.\n");
        exit(1);
    }
}


/* Generates a magic square of the user specified size and
 * output the quare to the output filename
 */
int main(int argc, char *argv[]) {
    // Check input arguments to get output filename
    if (argc != 2) {
        printf("Usage: ./myMagicSquare <output_filename>\n");
        exit(1);
    }
    // Get magin square's size from user
    int size = getSize();
    //  Generate the magic square
    MagicSquare *square = generateMagicSquare(size);    
    //  Output the magic square
    fileOutputMagicSquare(square, *(argv + 1));
    //Free all dynamically allocated memory.
    for (int i = 0; i < size; i ++) {
        free(*(square -> magic_square + i));
    }
    free(square -> magic_square);
    free(square);
    square = NULL;
    return 0;
} 


                                                         
//				myMagicSquare.c      

