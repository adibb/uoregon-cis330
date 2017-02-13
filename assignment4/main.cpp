#include <iostream>
#include "board.hpp"

using namespace std;

int main()
{
    Board reversi;

    while(!reversi.gameOver()){
        reversi.printBoard();
        reversi.takeTurn();
    }

    if (reversi.getScore(Board::P1) > reversi.getScore(Board::P2)){
        cout << "PLAYER 1 WINS!" << endl;
    } else if (reversi.getScore(Board::P1) < reversi.getScore(Board::P2)){
        cout << "PLAYER 2 WINS!" << endl;
    } else {
        cout << "Wait, a tie? How'd you pull that one off?" << endl;
    }

    return 0;
}
