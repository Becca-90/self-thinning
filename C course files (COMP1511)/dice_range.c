// This program reads the number of dice and how many sides they
// have, outputting the possible range of totals and average value
// written by Rebecca Stolper, z3378134

#include <stdio.h>

int main(void) {

    int sides;
    int number;

    printf("Enter the number of sides on your dice: ");
    scanf("%d", &sides);
   
    printf("Enter the number of dice being rolled: ");
    scanf("%d", &number);
    
    int min = 1 * number;
    int max = sides * number;
    double average = (min + max) / 2.0;
    
    if (sides <= 0 || number <= 0) {
    
        printf("These dice will not produce a range.\n");
    
    } else {
    
        printf("Your dice range is %d to %d.\n", min, max);
        printf("The average value is %lf\n", average);
    
    }
    
    return 0;
}
