//
//
//
//
//

#include <stdio.h>

#define ARRAY_SIZE 100

int main(void) {
    int my_array[ARRAY_SIZE];    
    int i = 0;
    
    printf("Enter numbers forwards: \n");
        
    while (scanf("%d", &my_array[i]) == 1 && i < ARRAY_SIZE) {
        i = i + 1;
    }
    
    printf("Reversed: \n");
    
    while (i > 0) {
        i = i - 1;   
        printf("%d\n", my_array[i]);   
    }

    return 0;

}
