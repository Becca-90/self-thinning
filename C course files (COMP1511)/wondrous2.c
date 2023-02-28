// This program takes a number and prints number/2 asterisks if even, 
// or 3*number + 1 asterisks if odd, continuing for each new number until reaching 1
// written by Rebecca Stolper, z3378134

#include <stdio.h>

int asterisk(int count) {

    while (count > 0) {                
        printf("*");
        count = count - 1;   
    }
        if (count % 2 == 0) {
            count = count / 2;
                                                        
        } else if (count % 2 == 1) {    
            count = (3 * count) + 1;
                    
        }
    return count;
        
    
}

int main(void) {

    int count;
    
    printf("What number would you like to see: ");
    scanf("%d", &count);
     
    while(count >= 2) {
        
        asterisk(count);
        printf("\n"); 
         
        if (count % 2 == 0) {
            count = count / 2;
                                                        
        } else if (count % 2 == 1) {    
            count = (3 * count) + 1;
                    
        }
        
    } 
        
    return 0;            
}
