#ifndef BOARD_H_
#define BOARD_H_

// Declare the tile color types
typedef enum {BLANK = '.', BLACK = 'B', WHITE = 'W'} color;

// Declare the players
typedef enum {P1, P2} players;

// Declare the board struct
typedef struct board {
    // Board contents represented as a matrix of tiles
    color **tiles;
    // Keeps track of which player's turn it is
    players turn;
    // Tracks how large the board is.
    int game_size;
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

#endif // BOARD_H_
