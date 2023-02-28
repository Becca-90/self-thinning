// Written 14/3/2018 by Andrew Taylor (andrewt@unsw.edu.au)
// as a lab example for COMP1511

// Print an nxn "x" pattern of asterisks and spaces
//
// For example here is the output for n == 9
//
// *-------*
// -*-----*-
// --*---*--
// ---*-*---
// ----*----
// ---*-*---
// --*---*--
// -*-----*-
// *-------*

#include <stdio.h>

int main(void) {
    int size, n_numbers_read;
    int row, column;

    printf("Enter size: ");
    n_numbers_read = scanf("%d", &size);

    if (n_numbers_read != 1) {
        // scanf failed to read a number
        return 1;
    }

    if (size < 5 || size % 2 != 1) {
        printf("Error: size has to be odd and >= 5.\n");
        return 1;
    }

    row = 0;
    while (row < size) {
        column = 0;
        while (column < size) {
            if (row == column || row == size - (column + 1)) {
                printf("*");
            } else {
                printf("-");
            }
            column = column + 1;
        }
        printf("\n");
        row = row + 1;
    }

    return 0;
}
