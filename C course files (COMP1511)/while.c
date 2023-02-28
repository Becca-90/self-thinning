// Guessing Game: CS Chardle
// cs_chardle.c
//
// This program was written by Rebecca Stolper (z3378134)
// The player must guess a letter until they guess the right one or run out of turns

#include <stdio.h>

#define MAX_ROUNDS 10
#define SCREEN_HEIGHT 10

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
    
    printf("What letter will the player guess? ");
    scanf(" %c", &solution);
    
    int ascii_letter = solution;
    
    
    
    
