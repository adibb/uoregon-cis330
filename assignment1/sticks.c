#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int getUserChoice(int current_sticks) {
    /* Prompt the user "Player 1: How many sticks do you take (1-3)?" and return
       an integer. Check that the value is valid (1, 2, or 3) and print an error if
       is not, then ask again until a valid number is entered. You can exit the program with
       exit(1);
     */
     int user_choice, valid = 0;

     while (!valid){
        printf("Player 1: How many sticks do you take (1-3)? ");
        scanf(" %d", &user_choice);
        if (user_choice < 1 || user_choice > 3){
            puts("ERR: Invalid choice of taken sticks. Please remove 1-3.\n");
        } else if (user_choice > current_sticks){
            puts("ERR: You cannot remove more sticks than are present.\n");
        } else {
            valid = 1;
        }
     }
}

int getComputerChoice(int current_sticks) {

    /* get a pseudo-random integer between 1 and 3 (inclusive) */
    int rand_choice = rand() % 3 + 1;

    if (rand_choice > current_sticks) return current_sticks;

    /* Optionally replace with additional logic for the computer's strategy */

    return rand_choice;
}


int main(int argc, char** argv)
{
    int user, computer, number_sticks, operating = 1, turn = 0;


    srand (time(NULL)); /* for reproducible results, you can call srand(1); */

    printf("Welcome to the game of sticks!\n");
    printf("How many sticks are there on the table initially (10-100)? ");
    scanf("%d", &number_sticks);

    /* TODO: Main game loop:
      While some sticks remain:
        1. Human: Get number of sticks by calling getUserChoice
        2. Computer: get number of sticks by calling getComputerChoice
        3. Output the computer's choice, e.g., "Computer selects 3."
        3. Update number_sticks
        4. Print the current number of sticks, e.g., "There are 2 sticks on the board."
      After all sticks are gone, output the result of the game,
      e.g., "Computer wins." or "Computer loses."
     */

    if (number_sticks < 10 || number_sticks > 100){
        puts("ERR: Invalid number of initializing sticks. Exiting program.");
        operating = 0;
    }

    while (operating){
        printf("There are %d sticks on the board.\n", number_sticks);
        if (number_sticks == 0){
            // Game over. Whoever's turn it is won.
            if (turn == 0){
                puts("You win!");
            } else {
                puts("You lose!");
            }
            operating = 0;
        } else {
            if (turn == 0){
                user = getUserChoice(number_sticks);
                turn = 1;
                number_sticks -= user;
            } else {
                computer = getComputerChoice(number_sticks);
                printf("The computer took %d stick(s).\n", computer);
                turn = 0;
                number_sticks -= computer;
            }
        }
    }

    return 0;
}
