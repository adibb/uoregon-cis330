#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "board.h"

/*
    Allocates the memory necessary for the game board
    and assigns it to the passed pointer.

    Params:
    - board *game_board: The game board
      to be allocated, passed by reference.
    - int game_size: Integer value for the size of
      the game board. Required to know how much
      memory to allocate for tiles.
*/
void allocateBoard(board *game_board, int game_size){
    int i;

    // Allocate the rows in the form of pointers to colors
    (*game_board).tiles = (color**) malloc(game_size * sizeof(color*));
    for (i = 0; i < game_size; i++){
        // Allocate
        (*game_board).tiles[i] = (color*) malloc(game_size * sizeof(color));
    }
}

/*
    Initializes the board to appropriate starting values.

    Params:
    - board *game_board: The game board to be initialized,
      passed by reference.
    - int game_size: The size of the game board itself.
      Necessary to make sure we stay in bounds when
      manipulating tiles.
*/
void initBoard(board *game_board, int game_size){
    int i;
    int center = game_size / 2 - 1;

    // Set the value of the tiles across the board to BLANK
    for (i = 0; i < game_size; i++){
        // Set the memory therein to BLANK
        memset((*game_board).tiles[i], BLANK, game_size * sizeof(color));
    }

    // Set the starting tiles
    (*game_board).tiles[center][center] = BLACK;
    (*game_board).tiles[center][center + 1] = WHITE;
    (*game_board).tiles[center + 1][center] = WHITE;
    (*game_board).tiles[center + 1][center + 1] = BLACK;

    // Set the starting turn to Player 1
    (*game_board).turn = P1;

    // Pass in the game size
    (*game_board).game_size = game_size;
}

/*
    Deallocates the memory for the game board, freeing
    it for other tasks.

    Params:
    - board *game_board: The game board
      to be deallocated, passed by reference.
*/
void deallocateBoard(board *game_board){
    int i;

    for (i = 0; i < (*game_board).game_size; i++){
        free((*game_board).tiles[i]);
        (*game_board).tiles[i] = NULL;
    }
    free((*game_board).tiles);
    (*game_board).tiles = NULL;
}

/*
    Prints the contents of the board

    Params:
    - board game_board: The board to be printed to
      console.
*/
void printBoard(board game_board){
    int i, j;
    int dim = game_board.game_size;

    // Print the first row
    printf("  ");
    for (i = 0; i < dim; i++){
        printf("%d ", i + 1);
    }
    printf("\n");

    // Print out the actual contents of the board
    for (i = 0; i < dim; i++){
        // Start off the row
        printf("%d ", i + 1);
        // Print the tile contents
        for (j = 0; j < dim; j++){
            printf("%c ", game_board.tiles[i][j]);
        }
        printf("\n");
    }
}
