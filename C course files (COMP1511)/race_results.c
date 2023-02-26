// race_results.c
// Written 24 June 2022
// By Rebecca Stolper
// z3378134
// This program allows the user to create an array of race results, inputting
// the no. of cars, each car's number and their race time, printing the results

#include <stdio.h>


#define MAX_CARS 20

struct race_result {
    int car_number;
    double race_time;
};

void print_result(int car_number, double race_time);

int main(void) {

    // makes array of result structs
    struct race_result race_results[MAX_CARS];
    
    int no_of_cars;
    printf("How many cars in the race? ");
    scanf("%d", &no_of_cars);
    
    int i = 0;
    printf("Enter results:\n");
    
    while (i < no_of_cars) {
        scanf("%d %lf", &race_results[i].car_number, &race_results[i].race_time);
        i = i + 1;
    }


    printf("Results:\n");
    int j = 0;
    
    while (j < no_of_cars) {
        print_result(race_results[j].car_number, race_results[j].race_time);
        j = j + 1;
    }

    return 0;
}

void print_result(int car_number, double race_time) {
    
    printf("%2d: %.2lf\n", car_number, race_time);
}
