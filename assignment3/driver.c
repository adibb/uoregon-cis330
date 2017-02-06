#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "intake.h"

int main(int argc, char** argv){
    int game_size;
    board playing_field;

    game_size = getGameSize();

    allocateBoard(&playing_field, game_size);
    initBoard(&playing_field, game_size);

    while (!gameOver(playing_field)){
        printBoard(playing_field);
        takeTurn(&playing_field);
    }
    printBoard(playing_field);

    if (playing_field.score_p1 > playing_field.score_p2)
        printf("WINNER: PLAYER 1!\n");
    else if (playing_field.score_p2 > playing_field.score_p1)
        printf("WINNER: PLAYER 2!\n");
    else
        printf("Wait, a tie? Really?\n");

    deallocateBoard(&playing_field);

    return 0;
}
