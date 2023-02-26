// Starter code for prac_q3

#include <stdio.h>

#define MAX_SIZE 10000

int main(void) {
    // TODO: write code to complete prac_q3 here!
    // You may define your own helper functions if you like.
    int array[MAX_SIZE];
    int i = 0;
    int j = 0;
    int k = 0;
                
    while (scanf("%d", &array[i]) == 1 && array[i] != 0) {
        i++;
    }
    
    while (j < i) {
        if (j % 2 == 0) {
            printf("%d ", array[j]);
        }
        j++;
    }

    while (k < i) {
        if (k % 2 != 0) {
            printf("%d ", array[k]);
        }
        k++;
    }
    
    printf("\n");
    
    return 0;
}
