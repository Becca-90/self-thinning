// This program asks for an integer and prints all numbers from 0
// up to the value on separate lines
// written by Rebecca Stolper, z3378134

#include <stdio.h>

int main(void) {
    int number;

    printf("Enter number: ");
    scanf("%d/n", &number);

    int i = 0;
    int j = 0;

    while (number <= j) {
        printf("%d\n", j);
        j = j - 1;
    }
    
    while (number >= i) {  
        printf("%d\n", i);
        i = i + 1;
    }
        
    return 0;
}

