#include "board.hpp"
#include <iostream>
#include <cmath>

// Assign static direction arrays for future use
const int Board::di[8] = { -1, 0, 1, 0, -1, 1, 1, -1 };
const int Board::dj[8] = { 0, 1, 0, -1, 1, 1, -1, -1 };

// Constructors for Board
Board::Board()
:Board(8)
{}

Board::Board(int game_size)
:turn(P1), score_p1(2), score_p2(2), game_over(false)
{
    // Set the board to blank
    for (int i = 0; i < game_size; i++){
        for (int j = 0; j < game_size; j++){
            setTile(i, j, BLANK);
        }
    }

    // SEt the center 4 tiles
    int center = game_size/2 - 1;
    setTile(center, center, BLACK);
    setTile(center + 1, center + 1, BLACK);
    setTile(center + 1, center, WHITE);
    setTile(center, center + 1, WHITE);

}

// Getter for the board dimension
int Board::getSize(){
    return sqrt(tiles.size());
}

// Getter for a tile at indicated position
char Board::getTile(int i, int j){
    return (char) tiles[std::make_pair(i, j)];
}

// Getter for a player's score
int Board::getScore(players p){
    if (p == P1)
        return score_p1;
    else if (p == P2)
        return score_p2;
}

// Setter for a tile at the indicated position
void Board::setTile(int i, int j, color c){
    tiles[std::make_pair(i, j)] = c;
}

// Setter that places a tile in an empty space and modifies the scores
void Board::placeTile(int i, int j, color c){
    char space = getTile(i, j);

    if (space == BLANK){
        setTile(i, j, c);
        if (c == BLACK)
            score_p1++;
        else if (c == WHITE)
            score_p2++;
    }
}

// Removes the tile in place, modifying the score
void Board::removeTile(int i, int j){
    char space = getTile(i, j);
    if (space == BLACK){
        score_p1--;
    } else if (space == WHITE){
        score_p2--;
    }
    setTile(i, j, BLANK);
}

// Flips a tile already on the board and modifies the scores
void Board::flipTile(int i, int j){
    char space = getTile(i, j);
    if (space == BLACK){
        setTile(i, j, WHITE);
        score_p1--;
        score_p2++;
    } else if (space == WHITE){
        setTile(i, j, BLACK);
        score_p1++;
        score_p2--;
    }
}

// Take a turn
void Board::takeTurn(){
    // Prompt and acquire user input
    int i, j;
    int dim = getSize();
    players curr_player;
    color curr_color;
    players next_player;

    // Figure out which player's turn it is and whose
    // will follow
    curr_player = turn;
    if (curr_player == P1){
        next_player = P2;
        curr_color = BLACK;
    } else if (curr_player == P2){
        next_player = P1;
        curr_color = WHITE;
    }

    bool valid = false;
    while (!valid){
        getUserAction(&i, &j);
        if (i == -1){
            // Player skipped turn
            valid = true;
        } else if (j == -1) {
            // Game is over, player forfeited
            game_over = true;
            valid = true;
        } else {
            // Check tile sanity
            if (0 <= i
                && i < dim
                && 0 <= j
                && j < dim
                && getTile(i, j) == BLANK){

                // Get initial scores
                int s1 = score_p1;
                int s2 = score_p2;

                // Place the new tile
                placeTile(i, j, curr_color);

                // try flanks in all directions
                for (int d = 0; d < 8; d++){
                    flank(i + di[d], j + dj[d], di[d], dj[d], curr_color);
                }

                valid = (s1 != score_p1 && s2 != score_p2);

                // If the flank was bad, remove the placed tile to properly
                // reset the turn
                if (!valid){
                    removeTile(i, j);
                }
            }
        }
    }

    // Turn complete, so swap players and test for game completion
    turn = next_player;
}

// Flanks in the indicated direction for the indicated color
bool Board::flank(int i, int j, int di, int dj, color flanker){
    // Sanitize input
    int dim = getSize();
    if (0 <= i
        && i < dim
        && 0 <= j
        && j < dim)
    {
        char t = getTile(i, j);
        if (t == BLANK){
            // Bad flank (hit blank), return false
            return false;
        } else if (t == (char) flanker) {
            // Flank complete, return true
            return true;
        } else {
            // Flank continues!
            flipTile(i, j);
            bool result = flank(i + di, j + dj, di, dj, flanker);
            if (!result){
                // Flank was bad - reflip tile
                flipTile(i, j);
            }

            return result;
        }
    } else {
        // Bad flank (out of bounds), return false
        return false;
    }
}

// Get the action for this turn
// x is -1 if the action was 'skip'
// y is -1 if the action was 'quit'
void Board::getUserAction(int *x, int *y){
    // Find which player is acting
    std::string p;
    if (turn == P1){
        p = "Player 1";
    } else if (turn == P2){
        p = "Player 2";
    }

    bool valid = false;
    while (!valid){
        char option;
        *x = 0;
        *y = 0;
        std::cout << p << ": Please input your action for this turn." << std::endl;
        std::cout << "Valid actions are: (p row col) place a tile, "
            << "(s) skip, and (f) forfeit/quit. " << std::endl;
        std::cin >> option;

        // Evaluate the passed input
        valid = true;
        if (option == 'p'){
            // Get the next two inputs as positions
            std::cin >> *x >> *y;
        } else if (option == 's') {
            *x = -1;
        } else if (option == 'f') {
            *y = -1;
        } else {
            valid = false;
        }
    }
}

// Ascertains if the fail conditions of the board have been met
bool Board::gameOver(){
    bool board_full = true;
    int dim = getSize();

    for (int i = 0; i < dim; i++){
        for (int j = 0; j < dim; j++){
            if (getTile(i, j) == BLANK)
                board_full = false;
        }
    }

    return (game_over || score_p1 == 0 || score_p2 == 0 || board_full);
}

// Print the board to console
void Board::printBoard(){
    // Get the board's size to stay in bounds
    int dim = getSize();

    // Print the scores
    std::cout << "Player 1: " << getScore(P1) << std::endl;
    std::cout << "Player 2: " << getScore(P2) << std::endl;

    // Print the initial row of column indexes
    std::cout << "  ";
    for (int i = 0; i < dim; i++){
        std::cout << i << " ";
    }
    std::cout << std::endl;

    // Print the board itself
    for (int i = 0; i < dim; i++){
        // Print the row index at the start
        std::cout << i << " ";
        for (int j = 0; j < dim; j++){
            std::cout << getTile(i, j) << " ";
        }
        std::cout << std::endl;
    }
}
