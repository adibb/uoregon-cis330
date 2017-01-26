#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "triangle.h"

/* Allocate a triangle of height "height" (a 2-D array of int) */
void allocateNumberTriangle(const int height, int ***triangle){
    // The width of the triangle is twice its height, minus 1
    const int width = height * 2 - 1;
    int i;

    // Initialize the rows, which are integer pointers
    *triangle = (int **) malloc(height * sizeof(int *));
    for (i = 0; i < height; i++){
        // Initialize each row of pointers to point to a 0 integer
        (*triangle)[i] = malloc(width * sizeof(int));
        memset((*triangle)[i], 0, width * sizeof(int));
    }
}

/* Initialize the 2-D triangle array */
void initializeNumberTriangle(const int height, int **triangle){
    const int width = 2 * height - 1;
    int i, j, left_bound, right_bound, acc;

    for(i = 0; i < height; i++){
        // The count starts and ends depending on which row
        // the loop has reached
        left_bound = height - i - 1;
        right_bound = left_bound + 2*i;
        acc = 1;
        for (j = 0; j < width; j++){
            if (j >= left_bound && j <= right_bound){
                triangle[i][j] = acc;
                acc++;
            }
        }
    }
}

/* Print a formatted triangle */
void printNumberTriangle(const int height, int **triangle){
    const int width = 2 * height - 1;
    int i, j;

    // Print the array
    for(i = 0; i < height; i++) {
        for(j = 0; j < width; j++) {
            int temp = triangle[i][j];
            if (temp > 0)
                printf("%d ", temp - 1);
            else
                printf("  ");
        }
        printf("\n");
    }
}

/* Free the memory for the 2-D triangle array */
void deallocateNumberTriangle(const int height, int ***triangle){
    int i;

    // Deallocate each row
    for (i = 0; i < height; i++){
        free((*triangle)[i]);
        (*triangle)[i] = NULL;
    }
    // Deallocate the array pointer itself
    free(*triangle);
    *triangle = NULL;
}
