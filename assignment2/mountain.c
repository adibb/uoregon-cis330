#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mountain.h"
#include "triangle.h"

#define BUFFER_SIZE 32

/* Print a mountain consisting of numPeaks triangles.
 * @param numPeaks: number of mountain peaks
 * @param heights: an array of heights with numPeak elements
 * @param triangles: an array of triangles
 */
void printNumberMountain(const int numPeaks, int *heights, int ***triangles){
    int i, j, k;
    // Pinter to triangles
    triangles = (int ***) malloc(numPeaks * sizeof(int **));

    // Find the maximum height and total width
    int max_h = heights[0], total_w = 2 * heights[0] - 1;
    for (i = 1; i < numPeaks; i++){
        total_w += (2 * heights[i] - 1);
        if (max_h < heights[i])
            max_h = heights[i];
    }

    // Secondary allocation for the triangles
    for (i = 0; i < numPeaks; i++){
        triangles[i] = (int **) malloc(max_h * sizeof(int *));
        for (j = 0; j < max_h; j++){
            triangles[i][j] = (int *) malloc(total_w * sizeof(int));
            memset(triangles[i][j], 0 ,sizeof(int) * total_w);
        }
    }

    // Set up the triangles themselves
    for (i = 0; i < numPeaks; i++){
        for (j = 0; j < max_h; j++){
            for (k = 0; k < total_w; k++){
                triangles[i][j][k] = i + 1;
            }
        }
    }

    // Print out the whole thing (also, EW EW EW TRIPLE LOOP)
    for (i = 0; i < numPeaks; i++){
        for (j = 0; j < max_h; j++){
            for (k = 0; k < total_w; k++){
                int value = triangles[i][j][k];
                if (value > 0)
                    printf("%d ", value - 1);
                else
                    printf("  ");
            }
            printf("\n");
        }
    }

    // Deallocate the 3D array
    for (i = 0; i < numPeaks; i++){
        for (j = 0; j < max_h; j++){
            free(triangles[i][j]);
            triangles[i][j] = NULL;
        }
        free(triangles[i]);
        triangles[i] = NULL;
    }

    free(triangles);
    triangles = NULL;
}

int main(int argc, char** argv){
    char line[BUFFER_SIZE];
    int ***triangles;
    int *peak_heights = NULL;
    int peak_count, i, valid = 0;

    // Prompt the user for 1-5 inclusive
    while (!valid){
        printf("Please enter the number of peaks [1-5]: ");
        fgets(line, BUFFER_SIZE, stdin);
        peak_count = atoi(line);   // 0 if not an integer
        valid = (line[1] == '\n' && peak_count > 0 && peak_count < 6);
    }

    // Reset the validity toggle
    valid = 0;

    // Allocate the heights array
    peak_heights = malloc(peak_count * sizeof(int));
    memset(peak_heights, 0, peak_count * sizeof(int));

    // Prompt the user for space separated peak heights
    while (!valid){
        printf("Please enter the peak heights [1-5, single space separated]: ");
        fgets(line, BUFFER_SIZE, stdin);
        // Check if the string is the right length to avoid overflowing the
        // peak_heights array
        if (line[2 * peak_count - 1] == '\n'){

            // Valid is set to true for now
            valid = 1;
            int index = 0;

            // Split the string by spaces
            char *temp = strtok(line, " ");
            while (temp != NULL){
                int value = atoi(temp);
                // Validity check 1 - catches correct length but bad inputs
                if (value <= 0 || value >= 5)
                    valid = 0;
                peak_heights[index++] = value;
                temp = strtok(NULL, " ");
            }

            // Validity check 2 - catches edge case
            valid = (peak_heights[peak_count - 1] != 0);
        }
        printf("\n");
    }

    printNumberMountain(peak_count, peak_heights, triangles);

    free(peak_heights);
}
