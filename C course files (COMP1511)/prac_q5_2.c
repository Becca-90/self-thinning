#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 256

int main(void) {
    int num_same = 0;
    char input1[MAX_SIZE];
    char input2[MAX_SIZE];
    
    fgets(input1, MAX_SIZE, stdin);
    fgets(input1, MAX_SIZE, stdin);

    int i = 0;
    
    while (input1[i] != '\0') {
        int j = 0;
        while (input2[j] != '\0') {
            if (input1[i] == input2[j]) {
                num_same++;
            }
            j++;
        }
        i++;
    }
    
    
    
    
    printf("%d\n", num_same);
    return 0;
}

// tolower() converts uppercase letter to lowercase
// isalpha() checks whether a characters is a letter or not (either case)
// and returns a non-zero integer, if not returns 0

Hi! I'm a bit confused about the example solution to question 5 in the prac exam... could someone help explain please?

So I understand there are 2 line input arrays, and an array of 26 zeroes plus both_lines counter for letters appearing twice...

Then while the index is not the end of the string, if is a letter, we do: letter_count[index = lowercase version of first letter in line1 minus value of 'a']++ 

What does this do? letter_count[this value] + 1?

So then in the next while loop, we check it's not the end of the string in line2, and if index i of line2 is a letter, we set 'index' to be the value of lowercase version of i minus 'a' value, and if letter_count[index], the letter is in both lines, then we set that index to have a zero value, I'm guessing to not reevaluate that letter?
