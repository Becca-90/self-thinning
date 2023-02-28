// Program name
//
// This program was written by [your name] (z5555555)
// on [date]
//
// Description of program

// every room is a struct...each floor a sequence of struct rooms and the hotel a series of many floors
// struct room hotel[8][8]
// each object of type room is called hotel[floor][room] and has elements inside the room written as hotel[floor][room]booking_id and hotel[floor][room].price 
// we want to enter in the number of guests and allocate each one to hotel[floor][room] of our choice, so for each n, scanf floor number and room number, and number each booking_id incrementing

// for each n set booking id with chosen floor and room 




#include <stdio.h>

// Additional libraries here

// Provided constants
#define TRUE 1
#define FALSE 0

#define TOTAL_FLOORS 8
#define ROOMS_PER_FLOOR 8
#define INITIAL_PRICE 10
#define NO_BOOKING -1

// Your constants here

// Provided struct
struct room {
    int booking_id;
    int price;
};

// Provided functions use for game setup
// You do not need to use these functions yourself.
void init_hotel(struct room hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR]);

// You will need to use these functions for stage 1.
void print_hotel(struct room hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR]);
void print_hotel_with_prices(struct room hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR]);

// Your function prototypes here:

void print_result(int floor_number, int room_on_floor, int booking_id) {
    printf("hotel[%d][%d].%d", floor_number, room_on_floor, booking_id);
}

int main(void) {
    struct room hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR];
    init_hotel(hotel);

    printf("Welcome to the CS Hotel!!\n\n");

    int n;
    int room_on_floor = 0;
    int floor_number = 0;
    int booking_id = 0;    
    
    printf("Add your current guests, how many guests? ");
    scanf("%d", &n);
    
    printf("Input in your guests room numbers\n");
    
    while (n > 0 && floor_number < TOTAL_FLOORS && room_on_floor < ROOMS_PER_FLOOR) {
        scanf("%d %d", &hotel[floor_number][room_on_floor].booking_id);
        booking_id++;
        n--;
    }

    print_hotel(hotel);
    printf("Enter a command: ");

    // TODO: keep scanning in commands from the user until the user presses
    // ctrl-d

    printf("Bye!\n");
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
///////////////////////////// ADDITIONAL FUNCTIONS /////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// TODO: you may need to add additional functions here

////////////////////////////////////////////////////////////////////////////////
////////////////////////////// PROVIDED FUNCTIONS //////////////////////////////
/////////////////////////// (DO NOT EDIT BELOW HERE) ///////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Provided Function (you shouldn't need to edit this in stage 1 or 2)
// Initalises the booking id and price of each room in the hotel to be
// the default values.
void init_hotel(struct room hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR]) {
    int row = 0;
    while (row < TOTAL_FLOORS) {
        int col = 0;
        while (col < ROOMS_PER_FLOOR) {
            hotel[row][col].booking_id = NO_BOOKING;
            hotel[row][col].price = INITIAL_PRICE;
            col++;
        }
        row++;
    }
}

// Provided Function - DO NOT EDIT
// Prints out the hotel with the booking number of each room, or empty
// if there is no booking.
void print_hotel(struct room hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR]) {
    printf(
        "\n"
        "         /--^--\\\n"
        "   _     |  O  |     _\n"
        " _/ \\___/_^___^_\\___/ \\_\n"
        "/                       \\\n");

    int row = 0;
    while (row < TOTAL_FLOORS) {
        int col = 0;
        printf("|--+--+--+--+--+--+--+--|\n");
        while (col < ROOMS_PER_FLOOR) {
            printf("|");
            if (hotel[row][col].booking_id == NO_BOOKING) {
                printf("  ");
            } else {
                printf("%02d", hotel[row][col].booking_id);
            }
            col++;
        }
        printf("|\n");
        row++;
    }
    printf(
        "|--+--+--+--+--+--+--+--|\n"
        "|         /^^^\\         |\n"
        "|_________|_\"_|_________|\n\n");
}

// Provided Function - DO NOT EDIT
// Prints out the hotel with the the price and booking number included.
void print_hotel_with_prices(struct room hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR]) {
    printf(
        "\n"
        "             /--^--\\\n"
        "   _         |  O  |         _\n"
        " _/ \\_______/_^___^_\\_______/ \\_\n"
        "/                               \\\n");

    int row = 0;
    while (row < TOTAL_FLOORS) {
        int col = 0;
        printf("|---+---+---+---+---+---+---+---|\n");
        while (col < ROOMS_PER_FLOOR) {
            printf("|");
            if (hotel[row][col].booking_id == NO_BOOKING) {
                printf("   ");
            } else {
#ifndef NO_COLORS
                printf("\033[1;35m");
#endif
                printf("%03d", hotel[row][col].booking_id);
#ifndef NO_COLORS
                printf("\033[0m");
#endif
            }
            col++;
        }
        printf("|\n");
        col = 0;
        while (col < ROOMS_PER_FLOOR) {
            printf("|");
#ifndef NO_COLORS
            printf("\033[1;32m");
#endif
            printf("%03d", hotel[row][col].price);
#ifndef NO_COLORS
            printf("\033[0m");
#endif
            col++;
        }
        printf("|\n");
        row++;
    }
    printf(
        "|---+---+---+---+---+---+---+---|\n"
        "|             /^^^\\             |\n"
        "|_____________|_\"_|_____________|\n\n");
}

