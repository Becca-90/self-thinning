// Program which prints a letter depending on the user's request.
// by Rebecca Stolper, z3378134

#include <stdio.h>

int main(void) {

    char is_uppercase;
    printf("Uppercase: ");
    scanf("%c", &is_uppercase);

    int index;
    printf("Index: ");
    scanf("%d", &index);
    
    int my_char_up = 'A' + index;
    int my_char_low = 'a' + index;
    
    if (is_uppercase == 'y') {
    
        printf("The letter is %c\n", my_char_up);
        
    } else if (is_uppercase == 'n') {
    
        printf("The letter is  %c\n", my_char_low);
        
    }
    
    return 0;
}

