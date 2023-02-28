//
//
//

#include <stdio.h>

int main(void) {
    
    int user_guess;
    int answer;

    int should_loop = 1; // 0 is false, 1 is true
        
    printf("Answer: ");
    scanf("%d", &answer);
        
    while(should_loop == 1) {
    
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
