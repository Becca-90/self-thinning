// A program to calculate some stats from an array.
// Jake Renzella, COMP1511 22T2

#include <stdio.h>

// #defines replace the name with the value in the pre-compile
#define ARRAY_SIZE 5

// This is a function that reuturns a ???
// It is called calculate_sum 
// and it accepts a double array
double calculate_sum(double input_array[ARRAY_SIZE]) {
    int i = 0;
    double array_sum = 0;
    while (i < ARRAY_SIZE) {
        array_sum += input_array[i]; // += is sum = sum + my_data[i];
        i++;
    }
    
    return array_sum;
}

int main(void) {
    
    double my_data[ARRAY_SIZE];
    double my_second_data[ARRAY_SIZE] = {20.0, 10.1, -10, 100.11, 101.1};
    
    // initialise the data from the user input...
    
    int i = 0;
    while (i < ARRAY_SIZE) {
        printf("Enter in the %dth value: ", i+1);
        scanf("%lf", &my_data[i]);
        i = i + 1; // or we could do i++ if you are feeling fancy;
    }
    
    // arrays are randomly accessible... so
    printf("%lf\n", my_data[2]);
    
    // create a double named sum (within main)
    // and assign it the result of calling calculate_sum(my_data)
    double sum = calculate_sum(my_data);
    
    printf("The sum is: %lf\n", sum);
    
    // directly print without assigning to a variable first
    printf("The second sum is: %lf\n", calculate_sum(my_second_data));
    
    return 0;
}
