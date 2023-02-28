#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define MAX_SIZE = 1024;

int main(void) {
	int both_lines = 0;
    int letter_count[26] = {0}; //array of 26 zeroes
	char line1[1024];
	char line2[1024];
	
	fgets(line1, 1024, stdin);
	fgets(line2, 1024, stdin);
	
	
	int i = 0;
	while (line1[i] != '\0') {     
		if (isalpha(line1[i])) {       
			letter_count[tolower(line1[i]) - 'a']++; 
	//if character at line1[i] is a letter,		
    //sets letter_count at index of the letter (letter_count[i]) to 
    //increase by 1
    //by first changing all to lowercase, and subtracting value of 
    //a, so index of a = 'a' - 'a' = 0, index of b = 'b' - 'a' = 1, etc
    //so every time the letter c is read throughout the string, it will 
    //increase position 2 value by 1, i.e. letter_count[2]++
		}
		i++;                                    
	}
	
	i = 0;
	while (line2[i] != '\0') {      //while not end of string
		if (isalpha(line2[i])) {        //if line2[i] a letter
			int index = tolower(line2[i]) - 'a';   //set index = position of line2[i]
			if (letter_count[index] > 0) {       //if letter_count at same 
			    both_lines++;                   //position has value > 0, is in both
			    letter_count[index] = 0;          //set letter count at that index to
			}                                   //zero so doesn't double count
		}
		i++;
	}
	printf("%d\n", both_lines);
    return 0;
}

// tolower() converts uppercase letter to lowercase
// isalpha() checks whether a characters is a letter or not (either case)
// and returns a non-zero integer, if not returns 0

