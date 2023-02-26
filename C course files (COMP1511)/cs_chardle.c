// Guessing Game: CS Chardle
// cs_chardle.c
//
// This program was written by Rebecca Stolper (z3378134)
// The player must guess a letter until they guess the right one or run out of turns

#include <stdio.h>

#define MAX_ROUNDS 10
#define SCREEN_HEIGHT 10
#define DIFF_UPPER_LOWER 32

char case_fix(char players_guess);
int ascii_fix(int solution);

// Function to convert any upper case letter to its lower case equivalent
char case_fix(char players_guess){
    if (players_guess >= 'A' && players_guess <= 'Z') {
        players_guess = players_guess + DIFF_UPPER_LOWER;
    }
    return players_guess;
}    

// Function to convert the ascii value of any upper case letter to its lower case equivalent
int ascii_fix(int solution) {
    if (solution >= 'A' && solution <= 'Z') {
        solution = solution + DIFF_UPPER_LOWER;
    }
    return solution;
}

void print_game_instructions(void) {
    printf("[COMP1511 Guessing Game: CS Chardle]\n");
    printf("\n");
    printf("Welcome to the COMP1511 guessing game.\n");
    printf("You will need to input a letter to guess,\n");
    printf("Then let the player see the screen, and make guesses.\n");
}

int main(void) {
    print_game_instructions();
    
    char solution;
    char players_guess;
    int guesses = 0;
    int should_loop = 1;
    int i = 0;
    
    printf("What letter will the player guess? ");
    scanf(" %c", &solution);
    
    int ascii_letter = ascii_fix(solution);
    
    if (case_fix(solution) >= 'a' && case_fix(solution) <= 'z') {
        printf("The answer is '%c' (ascii %d).\n", (case_fix(solution)), ascii_letter);

        while(i < SCREEN_HEIGHT) {
            printf("*\n");
            i = i + 1;
        }      
        
            while(guesses < MAX_ROUNDS && should_loop == 1) {  
            
                printf("What is guess #%d? ", guesses + 1);
                scanf(" %c", &players_guess); 
    
                char player_wins = case_fix(solution);
                
                    if (case_fix(players_guess) == player_wins) {
                    printf("Congratulations! You got the letter right!\n");
                    should_loop = 0;
        
                    } else if (case_fix(players_guess) >= player_wins && case_fix(players_guess) <= 'z') {
                        printf("Not quite! Guess earlier in the alphabet.\n");
            
                    } else if (case_fix(players_guess) <= player_wins && case_fix(players_guess) >= 'a') {
                        printf("Not quite! Guess later in the alphabet.\n");   
                       
                    } else {
                        printf("Your guess must be a valid letter!\n");
                    }
            
                guesses = guesses + 1;        
            }            
        
    } else {
        printf("The answer must be a valid letter!\n");
        should_loop = 0;
    }
    
        return 0;
}
