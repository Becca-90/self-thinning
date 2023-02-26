#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 256

int main() {
    char test_line_1[MAX_SIZE];
    char test_line_2[MAX_SIZE];
    char base_line[MAX_SIZE];
    
    printf("Enter the base line:\n");
    scanf("%s", base_line);
    
    int length = strlen(base_line);
    
    printf("Enter the test lines:\n");
    scanf("%s %s", test_line_1, test_line_2);
    
    int differences1 = 0;
    int differences2 = 0;
    int i = 0;
    int j = 0;
    
    while (i < length) {
        if (tolower(base_line[i]) != tolower(test_line_1[i])) {
            differences1++;
            i++;
        } else {
            i++;
        }
    }
    
    while (j < length) {
        if (tolower(base_line[j]) != tolower(test_line_2[j])) {
            differences2++;
            j++;
        } else {
            j++;
        }
    }
    
    if (differences1 > differences2) {
        printf("%d %s\n", differences2, test_line_2);
    } else {
        printf("%d %s\n", differences1, test_line_1);    
    }

}
