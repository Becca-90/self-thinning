// Prints the first n digits of pi, where n is specified 
// by the user
// written by Rebecca Stolper, z3378134

#include <stdio.h>

#define MAX_DIGITS 10

void print_pi(int num_digits);

int main(void) {

    printf("How many digits of pi would you like to print? ");
    int digits;
    scanf("%d", &digits);
    print_pi(digits);

    return 0;

}

void print_pi(int num_digits) {

    int pi[MAX_DIGITS] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    
    int i = 0;
    
    printf("%d.", pi[0]);
    
    while (i < num_digits - 1) {
        
        printf("%d", pi[i + 1]);
        i = i + 1;
        
    }
    
    printf("\n");
}
