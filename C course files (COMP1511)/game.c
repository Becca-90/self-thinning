// This program requires the player to guess an integer, giving hints until
// the correct number is guessed.
// written by Rebecca Stolper, z3378134

#include <stdio.h>

int main(void) {
    
    int user_guess;
    int answer;

    int should_loop = 1;
        
    printf("Answer: ");
    scanf("%d", &answer);
        
    while (should_loop == 1) {
    
        printf("Guess: ");
        scanf("%d", &user_guess);
        
        if (user_guess < answer) {
            printf("Too low\n");
        
        } else if (user_guess > answer) {
            printf("Too high\n");
        
        } else if (user_guess == answer) {
            printf("Correct!\n");
            should_loop = 0;
        }
    }
    
    return 0;
}
