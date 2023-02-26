// Read in a number, and determine whether it is negative.
// by the user
// Rebecca Stolper, z3378134


#include <stdio.h>

void print_positive_message(void) {
    printf("You have entered a positive number.\n");
}

void print_negative_message(void) {
    printf("Don't be so negative!\n");
}

void print_zero_message(void) {
    printf("You have entered zero.\n");
}


int main(void) {

    int number;

    scanf("%d", &number);

    if (number > 0) {
        print_positive_message();
    } else if (number < 0) {
        print_negative_message();
    } else {
        print_zero_message();
    }

    return 0;
}
