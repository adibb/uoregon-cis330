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

    // Set the starting score values to 2 each
    (*game_board).score_p1 = 2;
    (*game_board).score_p2 = 2;

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

    // Print fhe players' scores
    printf("P1: %d\n", game_board.score_p1);
    printf("P2: %d\n", game_board.score_p2);

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

/*
    Takes the next turn for the board.

    Params:
    - board *game_board: The game board in question, passed
      by reference.
*/
void takeTurn(board *game_board){
    direction dir;
    color player_color;

    // Figure out whose turn it is
    if ((*game_board).turn == P1){
        player_color = BLACK;
        printf("PLAYER 1: ");
        (*game_board).turn = P2;
    } else {
        player_color = WHITE;
        printf("PLAYER 2: ");
        (*game_board).turn = P1;
    }

    // Get a valid position and play it
    int valid = 0;
    int start_p1, start_p2, end_p1, end_p2;
    int row, col;
    while (!valid){
        getPosition(&row, &col);
        // Sanitize the value
        valid = (row < (*game_board).game_size)
                && (row >= 0)
                && (col < (*game_board).game_size)
                && (col >= 0)
                && ((char) (*game_board).tiles[row][col] == BLANK);

        // Value is sane, so we can start the second round
        // of actions and checks
        if (valid){
            // Keep the starting scores of both players
            start_p1 = (*game_board).score_p1;
            start_p2 = (*game_board).score_p2;

            for (dir = N; dir <= NW; dir++){
                // Determine the row and column increments based on direction
                int row_inc = 0;
                if (dir == NW || dir == N || dir == NE)
                    row_inc = -1;
                else if (dir == SW || dir == S || dir == SE)
                    row_inc = 1;

                int col_inc = 0;
                if (dir == NW || dir == W || dir == SW)
                    col_inc = -1;
                else if (dir == NE || dir == E || dir == SE)
                    col_inc = 1;

                // Try flanks in all directions
                flank(game_board,
                      row + row_inc,
                      col + col_inc,
                      player_color,
                      dir);

                // Keep the new scores of both players for comparison
                end_p1 = (*game_board).score_p1;
                end_p2 = (*game_board).score_p2;
            }
        }

        // Tiles flipped by flank if possible. If any were flipped,
        // it was a valid play.
        valid = (start_p1 != end_p1)
                && (start_p2 != end_p2);

        // Don't forget to put the tile there!
        if (valid)
            placeTile(game_board, row, col, player_color);
    }
}

/*
    Flips the tile on the passed board at the given position.
    Black becomes white, white becomes black. Blank tiles are
    unaffected.

    Params:
    - board *game_board: The game board in question, passed by
      reference.
    - int row: The row of the tile to flip.
    - int col: The column of the tile to flip.
*/
void flipTile(board *game_board, int row, int col){
    // Get the tile in question
    color *tile = &(*game_board).tiles[row][col];

    // Flip the tile - nothing happens if blank
    if ((char) *tile == WHITE){
        *tile = BLACK;
        (*game_board).score_p1++;
        (*game_board).score_p2--;
    } else if ((char) *tile == BLACK){
        *tile = WHITE;
        (*game_board).score_p1--;
        (*game_board).score_p2++;
    }
}

/*
    Places a tile of the indicated color at the indicated
    position on the passed board.

    Params:
    - board *game_board: The game board the tile is being placed
      on, passed by reference.
    - int row: The row of the placed tile.
    - int col: the column of the placed tile.
    - color tile: The color of the placed tile.
*/
void placeTile(board *game_board, int row, int col, color tile){
    (*game_board).tiles[row][col] = tile;
    if (tile == BLACK)
        (*game_board).score_p1++;
    else
        (*game_board).score_p2++;
}

/*
    Outflanks the tiles in the 8 directions away from the
    indicated position.

    Params:
    - board *game_board: The game board the flanking is taking
      place on, passed by reference.
    - int row: The row of the flanking tile.
    - int col: The column of the flanking tile.
    - color flanker: The coloration of the flanking tile.
    - direction dir: The direction to look for flanked
      tile in.
*/
int flank(board *game_board,
          int row,
          int col,
          color flanker,
          direction dir){
    int result = 0;

    if (row < (*game_board).game_size
        && col < (*game_board).game_size
        && row >= 0
        && col >= 0)
    {
        // Flank is sane. Check if we've finished the flank, or need
        // to continue on
        color tile = (*game_board).tiles[row][col];
        if ((char) tile == flanker)
            // Flank complete, so return
            return result;
        else {
            // Flank continues, flip current tile
            result++;
            flipTile(game_board, row, col);

            // Determine the row and column increments based on direction
            int row_inc = 0;
            if (dir == NW || dir == N || dir == NE)
                row_inc = -1;
            else if (dir == SW || dir == S || dir == SE)
                row_inc = 1;

            int col_inc = 0;
            if (dir == NW || dir == W || dir == SW)
                col_inc = -1;
            else if (dir == NE || dir == E || dir == SE)
                col_inc = 1;

            // Get the recursive value of the continued flank
            int result_inc = flank(game_board,
                               row + row_inc,
                               col + col_inc,
                               flanker,
                               dir);

            // If the value was -1, it indicates a bad flank, so re-flip
            // the tile and return -1
            if (result_inc == -1){
                flipTile(game_board, row, col);
                return -1;
            } else {
                result += result_inc;
            }
        }

    } else {
        // Value has gone off of board or hit a blank space, so the
        // flank is bad.
        return -1;
    }

    return result;
}

/*
    Tests to see if the game has concluded.

    Params:
    - board game_board: The board we're looking at to tell
      if the game's concluded.
*/
int gameOver(board game_board){
    int i, j;
    int empty = 0;

    int max = game_board.game_size;
    for (i = 0; i < max; i++){
        for (j = 0; j < max; j++){
            if (game_board.tiles[i][j] == BLANK)
                empty = 1;
        }
    }

    return (empty
            || game_board.score_p1 == 0
            || game_board.score_p2 == 0);
}
