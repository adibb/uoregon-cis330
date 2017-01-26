#include <stdio.h>
#include <stdlib.h>
#include "triangle.h"

#define BUFFER_SIZE 32

int main(int argc, char** argv){
    int **triangle, height, valid = 0;
    char line[BUFFER_SIZE];

    // Prompt the user for 1-5 inclusive
    while (!valid){
        printf("Please enter the height of the triangle [1-5]: ");
        fgets(line, BUFFER_SIZE, stdin);
        height = atoi(line);   // 0 if not an integer
        valid = (line[1] == '\n' && height > 0 && height < 6);
    }

    height = (const int) height;

    allocateNumberTriangle(height, &triangle);
    initializeNumberTriangle(height, triangle);
    printNumberTriangle(height, triangle);
    deallocateNumberTriangle(height, &triangle);
}
