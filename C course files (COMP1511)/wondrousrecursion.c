// This program takes a number and prints number/2 asterisks if even, 
// or 3*number + 1 asterisks if odd, continuing for each new number until reaching 1
// written by Rebecca Stolper, z3378134

#include <stdio.h>

void asterisk(int count) {

    int i = 0;    
        
    while (i < count) {                
        printf("*");
        i = i + 1;    
    }
    printf("\n");
    
        if (count % 2 == 0 && count > 2) {
            count = count / 2;
            asterisk(count);
                                                        
        } else if (count % 2 == 1 && count > 2) {    
            count = (3 * count) + 1;
            asterisk(count);
                    
        }
        
 }

int main(void) {

    int count;

    printf("What number would you like to see: ");
    scanf("%d", &count);

    asterisk(count);

    return 0;

} 
    
