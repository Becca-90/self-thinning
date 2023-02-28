// Written 24 June 2022
// By Rebecca Stolper
// z3378134
// This program creates an array of integers, with the length of the array &
// set of integers determined by the user, and returns the min and max values

#include <stdio.h>

#define MAX_SIZE 100

void print_array_minmax(int length, int numbers[MAX_SIZE]);

int main(void) {

    int numbers[MAX_SIZE];
    
    int length;
    printf("How many numbers: ");    
    scanf("%d", &length);
    
    int i = 0;
    printf("Please enter numbers: ");
        
    while (i < length) {
    
        scanf("%d", &numbers[i]);
        i = i + 1;
        
    }  
    
    print_array_minmax(length, numbers);

    return 0;
}

void print_array_minmax(int length, int numbers[MAX_SIZE]) {
    int index = 0;
    if (length > 0) {
        int minimum = numbers[index];
        int maximum = numbers[index];

        while (index < length) {
            if (numbers[index] < minimum) {
                minimum = numbers[index];
            } else if (numbers[index] > maximum) {
                maximum = numbers[index];
            }
            
            index++;
        }

        printf("Minimum: %d\nMaximum: %d\n", minimum, maximum);
    }
    
    return;
}
