// exam_q3.c
//
// This program was written by Rebecca Stolper (z3378134)
// on 12/08/22
//
// One line summary of what this exercise does.
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10000

int main(void) {
    // TODO: Finish the following line.
    
    int my_array[MAX_SIZE];
    int i = 0;
    
    while (scanf("%d", &my_array[i]) == 1 && i < MAX_SIZE) {
        i++;
    }
    
    int distance = 1;
    int distance2 = 1;
    i = 0;
    int j = 1;
    int k = j;
    while (my_array[i] != my_array[j]) {
        j++;
        distance++;
        while (my_array[k] != my_array[k+1]) {   
            k++;
            distance2++;
        }       
    }

    
    if (distance < distance2) {
        printf("The minimum distance was: %d\n", distance);
    } else {
        printf("The minimum distance was: %d\n", distance2);    
    }

    return 0;
}
