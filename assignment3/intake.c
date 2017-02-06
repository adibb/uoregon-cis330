#include <stdio.h>
#include <stdlib.h>
#include "intake.h"

/*
    Gets the size of the game from the user. Minimum
    of 5, maximum of 15.
*/
int getGameSize(){
    int valid = 0;
    int result;
    char line[BUFFER_SIZE];

    while (!valid){
        printf("Please input the size of the game [4 - 9]: ");
        fgets(line, BUFFER_SIZE, stdin);
        result = atoi(line);
        valid = (result >= 4) && (result <= 9) && (line[1] == '\n');
    }

    return result;
}

/*
    Gets the position indicated by the user and returns
    it as two pass-by-reference variables in the parameter.
    They are returned with the values of the associated
    row and column index respectively.

    Params:
    - int *row: An integer to house the returned row value.
    - int *col: An integer to house the returned column value.

    NOTE: This function only acquires two single digit values.
*/
void getPosition(int *row, int *col){
    int valid = 0;
    char line[BUFFER_SIZE];

    while (!valid){
        printf("Please input your selected position in the form 'row col': ");
        fgets(line, BUFFER_SIZE, stdin);
        // Change the inputs from characters to integers, and correct for
        // 0 indexing
        *row = line[0] - '0' - 1;
        *col = line[2] - '0' - 1;
        /*
        There are several conditions that must be met for a space to be
        valid. It must:

        - be properly formatted, so there's a space in the second
          character of the line and a nextline character in the fourth
        - be within the board, so 0 <= row and col < game_size
        */
        valid = (line[1] == ' ') && (line[3] == '\n');
    }
}
