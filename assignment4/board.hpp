#ifndef BOARD_H_
#define BOARD_H_

#include <map>

class Board {

    typedef enum {BLANK = ' ', BLACK = 'B', WHITE = 'W'} color;
    typedef enum {P1, P2} players;

public:
    // Constructor
    Board(int board_size);

private:
    // Player turn
    players turn;
    // The tiles
    std::map< std::pair<int, int>, color > tiles;
    // Direction arrays
    const static int di[];
    const static int dj[];
};

#endif // BOARD_H_
