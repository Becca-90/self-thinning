// This program reads a year and prints
// whether it is a leap year
// by Rebecca Stolper, z3378134


#include <stdio.h>

int main(void) {
    
    int year;
    
    printf("Enter year: ");
    scanf("%d", &year);
    
    if (year % 4 != 0) {
        printf("%d is not a leap year.\n", year);
        
    } else if (year % 4 == 0 && year % 100 != 0) {
        printf("%d is a leap year.\n", year);
    
    } else if (year % 4 == 0 && year % 100 == 0 && year % 400 != 0) {
        printf("%d is not a leap year.\n", year);
    
    } else if (year % 4 == 0 && year % 100 == 0 && year % 400 == 0) {
        printf("%d is a leap year.\n", year);
    
    }

    return 0;
}
