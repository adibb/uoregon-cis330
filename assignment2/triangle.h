#ifndef TRIANGLE_H_
#define TRIANGLE_H_

/* Print a triangle of height 5 */
void print5Triangle();

/* Allocate a triangle of height "height" (a 2-D array of int) */
void allocateNumberTriangle(const int height, int ***triangle);

/* Initialize the 2-D triangle array */
void initializeNumberTriangle(const int height, int **triangle);

/* Print a formatted triangle */
void printNumberTriangle(const int height, int **triangle);

/* Free the memory for the 2-D triangle array */
void deallocateNumberTriangle(const int height, int ***triangle);

#endif /* TRIANGLE_H_ */
