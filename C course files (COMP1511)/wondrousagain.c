//
//
//

#include <stdio.h>

int main(void) {

    int count;
    int i = 0;

    printf("What number would you like to see: ");
    scanf("%d", &count);
                    
    while (count > 0) {
        printf("*");
        count = count - 1;
    }
        
        while(count > 2) {
            
            if (count % 2 == 0) {
                count = count / 2;
                                                        
            } else if (count % 2 == 1) {    
                count = (3 * count) + 1;
                    
            }
                while (i < count) {
                
                    printf("*");
                    i = i + 1;   
                }
                        
            return count;
            printf("\n");
        
        } 
        
    return 0;
}
