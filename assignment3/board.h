#ifndef BOARD_H_
#define BOARD_H_

#include "intake.h"

// Declare the tile color types
typedef enum {BLANK = '.', BLACK = 'B', WHITE = 'W'} color;

// Declare the players
typedef enum {P1, P2} players;

// Declare the directions for traversing the board
typedef enum {N, NE, E, SE, S, SW, W, NW} direction;

// Declare the board struct
typedef struct board {
    // Board contents represented as a matrix of tiles
    color **tiles;

    // Keeps track of which player's turn it is
    players turn;

    // Tracks how large the board is.
    int game_size;

    // Tracks the players' scores
    int score_p1;
    int score_p2;
} board;

// Allocates the memory necessary for the board
void allocateBoard(board *game_board, int game_size);

// Initializes a board to be completely blank save
// for the starting positions, and
void initBoard(board *game_board, int game_size);

// Frees the memory for the board
void deallocateBoard(board *game_board);

// Prints out the board's contents
void printBoard(board game_board);

// Gets the number of tiles of the passed color on the passed board
int getTileCount(board game_board, color tile_type);

// Take a turn, based on the 'turn' and 'tiles'
// value of the passed board.
void takeTurn(board *game_board);

// Flips the tile at the marked position on the passed board.
void flipTile(board *game_board, int row, int col);

// Place a tile on the board
void placeTile(board *game_board, int row, int col, color tile);

// Recursively flips tiles in all directions that have been flanked
int flank(board *game_board, int row, int col, color flanker, direction dir);

// Check if the game has concluded
int gameOver(board game_board);

#endif // BOARD_H_
