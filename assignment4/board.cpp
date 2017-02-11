#include "board.hpp"

// Constructor for Board
Board::Board(int board_size){
    // Initialize the turn to player 1
    turn = P1;

    // Set up the board
    for (int i = 0; i < board_size; i++){
        for (int j = 0; j < board_size; j++){
            tiles[std::make_pair(i, j)] = BLANK;
        }
    }

    // Set up the direction lookup arrays
    const int di[] = { 1, -1, 0, 0, 1, -1, 1, -1 };
    const int dj[] = { 0, 0, 1, -1, 1, -1, -1, 1 };
}
