#ifndef INTAKE_H_
#define INTAKE_H_

#include "board.h"
#define BUFFER_SIZE 32

// Gets the size of the game
int getGameSize();

// Gets a position on the board
void getPosition(int *x, int *y, board game_board);

#endif // INTAKE_H_
