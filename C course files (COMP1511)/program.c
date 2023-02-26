#include <stdio.h>
#include <stdlib.h>

void chop_string(char string[]) {
    int i = 0;
    while (string[i] != '\0') {
        if (i > 0 && string[i] == string[i - 1]) {
            string[i] = '\0';
        }

        i++;
    }
}

int main(void) {
    char a[] = "What did Tom say to Sasha after he learned C? I want arrays.";
    chop_string(a);
    char b[] = "Two characters will be in a new film. They are seeking  a stunt double.";
    chop_string(b);
    char c[] = "Why did the pointer cross the road? He just wanted to be free!";
    chop_string(c);
    char d[] = "A group of different data types fell in love. They were love-struct.";
    chop_string(d);
    char e[] = "An array of characters had it's 'r' stolen -- that must sting.";
    chop_string(e);

    // Which of a, b, c, d or e are the longest string
    // at this point in the code?
    
    printf(" %s", a);

}
