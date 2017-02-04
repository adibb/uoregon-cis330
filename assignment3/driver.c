#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "intake.h"

int main(int argc, char** argv){
    int game_size;
    int row, col;
    board test;

    game_size = getGameSize();

    allocateBoard(&test, game_size);
    initBoard(&test, game_size);

    printBoard(test);
    getPosition(&row, &col, test);
    printf("Position given: %d, %d\n", row, col);

    deallocateBoard(&test);

    return 0;
}
