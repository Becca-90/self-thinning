// This program requires the player to guess an integer, giving hints until
// the correct number is guessed.
// written by Rebecca Stolper, z3378134

#include <stdio.h>

int main(void) {

    int answer;
    int number_guess;
    int should_loop = 1;
    
    printf("Answer: ");
    scanf("%d", &answer);
    
    while (should_loop == 1) {                  

        printf("Guess: ");
        scanf("%d", &number_guess);
            
        if (number_guess > answer) {
            printf("Too high\n");

        } else if (number_guess < answer) {
            printf("Too low\n");
        
        } else if (number_guess == answer) {
            printf("Correct!\n");
            should_loop = 0;
            
        }   
    }
    
    return 0;
}
