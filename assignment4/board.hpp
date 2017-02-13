#ifndef BOARD_H_
#define BOARD_H_

#include <map>

class Board {

// The types need to be visible for outside manipulations,
// even if the variables they modify are private.
public: enum color {BLANK = '.', BLACK = 'B', WHITE = 'W'};
public: enum players {P1, P2};

private:
    // Player turn
    players turn;
    // Player scores
    int score_p1;
    int score_p2;
    // The tiles
    std::map< std::pair<int, int>, color > tiles;
    // Tracks if game is over yet
    bool game_over;

protected:
    // Direction arrays
    const static int di[];
    const static int dj[];

public:
    // Constructors
    Board();
    Board(int board_size);

    // Getters
    int getSize();
    int getScore(players p);
    char getTile(int i, int j);
    void getUserAction(int *x, int *y);

    // Setters
    void setTile(int i, int j, color c);
    void placeTile(int i, int j, color c);
    void removeTile(int i, int j);
    void flipTile(int i, int j);

    // Take a turn
    void takeTurn();

    // Flank in a specific direction
    bool flank(int i, int j, int di, int dj, color flanker);

    // Test for a game over, and indicate it on the value
    bool gameOver();

    // Print the board out with scores
    void printBoard();
};

#endif // BOARD_H_
