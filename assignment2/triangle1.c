#include <stdio.h>
#include <stdlib.h>

#define WIDTH 9
#define HEIGHT 5

void print5Triangle();

/* Print a triangle of height 5 */
void print5Triangle(){
    /*
        I understand this is sloppy, but this is
        the sort of thing where any sophisticated
        loop to set the values should really just
        print them directly. I mean, come on! Why
        bother with a 2D integer array here? The
        whitespace alone suggests - GRR GRR GRR
    */
    int arr[HEIGHT][WIDTH] = {
        {0,0,0,0,1,0,0,0,0},
        {0,0,0,1,2,3,0,0,0},
        {0,0,1,2,3,4,5,0,0},
        {0,1,2,3,4,5,6,7,0},
        {1,2,3,4,5,6,7,8,9}
    };
    int i, j;

    // Print the array
    for(i = 0; i < HEIGHT; i++) {
        for(j = 0; j < WIDTH; j++) {
            if (arr[i][j] > 0)
                printf("%d ", arr[i][j] - 1);
            else
                printf("  ");
        }
        printf("\n");
    }
}
