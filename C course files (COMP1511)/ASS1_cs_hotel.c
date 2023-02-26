// cs_hotel.c
//
// This program was written by Rebecca Stolper (z3378134)
// on [11 July 2022]
//
// CS Hotel is a hotel management system for a Sydney Harbourfront Hotel,
// in which the user can enter in any number of given commands, such as adding guests, 
// changing floor prices and calaculating a night's revenue, to keep track of 
// the state of the hotel.


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
#define TOTAL_NUM_ROOMS 64

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
void room_check(int floor_number, int room_on_floor, struct room 
hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR]);
void add_guests(int floor_number, int room_on_floor, struct room 
hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR]);
void guest_leaves(int floor_number, int room_on_floor, struct room 
hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR]);
int total_num_bookings(struct room hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR]);
int highest_booking_num(struct room hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR]);
void change_floor_price(int floor_number, int new_price, struct room hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR]);
void change_price_all(int price_increase, struct room hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR]);
int total_revenue(struct room hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR], int previous_revenue);
void best_available(struct room hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR]);
void swap_rooms(struct room hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR], 
                int floor_num_1, int room_num_1, 
                int floor_num_2, int room_num_2);
int rooms_avail_on_floor(int floor_number, struct room hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR]);
int cheapest_floor(struct room hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR]);
void group_booking_cheapest(int cheapest_or_highest, int num_guests, struct room hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR]);

int main(void) {
    struct room hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR];
    init_hotel(hotel);

    printf("Welcome to the CS Hotel!!\n\n");

    int n;
    int room_on_floor;
    int floor_number;
    int floor_num_1 = 0;
    int floor_num_2 = 0;
    int room_num_1 = 0;
    int room_num_2 = 0;
    int booking_num = 0;   
    char command = 0;
    int continue_loop = 1;
    int new_price = 0;
    int previous_revenue = 0; 
    int num_guests = 0;
    int cheapest_or_highest = 0;
    
    printf("Add your current guests, how many guests? ");
    scanf("%d", &n);
    
    printf("Input in your guests room numbers\n");
    
    while (n > 0 && booking_num >= 0) {
        
        scanf("%d %d", &floor_number, &room_on_floor);
        
        if (room_on_floor < 0 || room_on_floor >= ROOMS_PER_FLOOR) {
            printf("Invalid room number!\n");           
        } else if (floor_number < 0 || floor_number >= TOTAL_FLOORS) {
            printf("Invalid room number!\n");           
        } else if (hotel[floor_number][room_on_floor].booking_id >= 0) {
            printf("Room already occupied!\n"); 
        } else { 
            hotel[floor_number][room_on_floor].booking_id = booking_num;
            booking_num++;         
        } 
        n--;
 
    }

    print_hotel(hotel);
    printf("Enter a command: ");
    
    while (scanf(" %c", &command) == 1) {
    
        if (command == 'p') {
            print_hotel(hotel);
            printf("Enter a command: ");
        } else if (command == '?' && continue_loop == 1) {
            room_check(floor_number, room_on_floor, hotel);
            printf("Enter a command: ");             
        } else if (command == 'a' && continue_loop == 1) {
            add_guests(floor_number, room_on_floor, hotel);
            printf("Enter a command: ");            
        } else if (command == 'l' && continue_loop == 1) {
            guest_leaves(floor_number, room_on_floor, hotel);
            printf("Enter a command: ");  
        } else if (command == 'c') {
            print_hotel_with_prices(hotel);
            printf("Enter a command: ");                    
        } else if (command == '$' && continue_loop == 1) {
            change_floor_price(floor_number, new_price, hotel);
            printf("Enter a command: ");
        } else if (command == '^' && continue_loop == 1) {
            change_price_all(new_price, hotel);
            printf("Enter a command: ");
        } else if (command == 'r') {
            int i = 0;
            if (i ==  0) {
            	previous_revenue = total_revenue(hotel, previous_revenue);
            } else if (i > 0) {            
            	total_revenue(hotel, previous_revenue);
            }            
            i++;            
            printf("Enter a command: ");       
        } else if (command == 'j') {
	        best_available(hotel);
	        printf("Enter a command: ");
        } else if (command == 's' && continue_loop == 1) {
            swap_rooms(hotel, floor_num_1, room_num_1, floor_num_2, room_num_2); 
            printf("Enter a command: ");
        } else if (command == 'g' && continue_loop == 1) {
            group_booking_cheapest(cheapest_or_highest, num_guests, hotel);
            printf("Enter a command: ");
        }
    }

    printf("Bye!\n");
    return 0;
}

// Checks the booking ID number of any given room
void room_check(int floor_number, int room_on_floor, struct room 
hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR]) {   
    scanf("%d %d", &floor_number, &room_on_floor);
    
    if (room_on_floor < 0 || room_on_floor >= ROOMS_PER_FLOOR) {
        printf("Invalid room number!\n");           
    } else if (floor_number < 0 || floor_number >= TOTAL_FLOORS) {
        printf("Invalid room number!\n");         
    } else if (hotel[floor_number][room_on_floor].booking_id >= 0) {
        printf("Booking ID at Floor %d, Room %d is : %d\n", floor_number,      
        room_on_floor, hotel[floor_number][room_on_floor].booking_id);  
    } else {
        printf("Floor %d, Room %d is empty.\n", floor_number, room_on_floor);        
    }    
}

// Adds guest to specified room in the hotel
void add_guests(int floor_number, int room_on_floor, struct room 
hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR]) {
    scanf("%d %d", &floor_number, &room_on_floor);
        
    if (room_on_floor < 0 || room_on_floor >= ROOMS_PER_FLOOR) {
        printf("Invalid room number!\n");           
    } else if (floor_number < 0 || floor_number >= TOTAL_FLOORS) {
        printf("Invalid room number!\n");           
    } else if (hotel[floor_number][room_on_floor].booking_id >= 0) {
        printf("Room already occupied!\n"); 
    } else { 
        hotel[floor_number][room_on_floor].booking_id = 
        highest_booking_num(hotel) + 1;
        printf("Guest's booking id is: %d\n", 
        hotel[floor_number][room_on_floor].booking_id);      
    }   
}

// Removes a guest booking from the hotel
void guest_leaves(int floor_number, int room_on_floor, struct room 
hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR]) {
    scanf("%d %d", &floor_number, &room_on_floor);
    
    if (room_on_floor < 0 || room_on_floor >= ROOMS_PER_FLOOR) {
        printf("Invalid room number!\n");           
    } else if (floor_number < 0 || floor_number >= TOTAL_FLOORS) {
        printf("Invalid room number!\n");           
    } else if (hotel[floor_number][room_on_floor].booking_id >= 0) {
        printf("Goodbye booking %d!\n", hotel[floor_number][room_on_floor].booking_id);
        hotel[floor_number][room_on_floor].booking_id = NO_BOOKING;
    } else { 
        printf("Room is already empty.\n");
    }   
}

// Calculates the total number of current hotel bookings
int total_num_bookings(struct room hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR]) {
    int i = 0;
    int num_bookings = 0;
    while (i >= 0 && i < TOTAL_FLOORS) {
        int j = 0;
        while (j >= 0 && j < ROOMS_PER_FLOOR) {
            if (hotel[i][j].booking_id >= 0) {
            num_bookings++;
            }
            j++;
        }        
        i++;
    }
    return num_bookings;
}

// Returns the highest booking ID number
int highest_booking_num(struct room hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR]) {
    int floor_number = 0;
    int highest_num = 0;
   
    while (floor_number < TOTAL_FLOORS - 1) {
        int room_on_floor = 0;
        while (room_on_floor <= ROOMS_PER_FLOOR - 1) {
            if (hotel[floor_number][room_on_floor].booking_id >= 
                highest_num) {
                highest_num = hotel[floor_number][room_on_floor].booking_id;
            }
            room_on_floor++;
        }
        floor_number++;        
    }

    return highest_num;
}

// Changes the price of all rooms on a specified floor
void change_floor_price(int floor_number, int new_price, struct room hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR]) {
    int room_on_floor = 0;
    scanf("%d %d", &floor_number, &new_price);

    if (floor_number < 0 || floor_number >= TOTAL_FLOORS) {
        printf("Invalid floor number!\n");        
    } else if (new_price < 0) {
        printf("Invalid price!\n");
    } else {
        while (room_on_floor >= 0 && room_on_floor < ROOMS_PER_FLOOR) {
            hotel[floor_number][room_on_floor].price = new_price;
            room_on_floor++;
        }
    }
}

// Increases or decreases the prices of rooms on all floors 
// by a specified amount
void change_price_all(int price_increase, struct room hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR]) {
    int floor_number = 0;
    scanf("%d", &price_increase);
    
    if (price_increase >= 0) {
        while (floor_number >= 0 && floor_number < TOTAL_FLOORS) { 
            int room_on_floor = 0;
            while (room_on_floor >= 0 && room_on_floor < ROOMS_PER_FLOOR) {
                hotel[floor_number][room_on_floor].price = 
                hotel[floor_number][room_on_floor].price + price_increase;
                room_on_floor++;
            }
        floor_number++; 
        }
    } else if (price_increase < 0) {
         while (floor_number >= 0 && floor_number < TOTAL_FLOORS) { 
            int room_on_floor = 0;
            while (room_on_floor >= 0 && room_on_floor < ROOMS_PER_FLOOR) {
                if (hotel[floor_number][room_on_floor].price + price_increase >= 0) {
                    hotel[floor_number][room_on_floor].price = 
                    hotel[floor_number][room_on_floor].price + price_increase;
                } else {
                    hotel[floor_number][room_on_floor].price = 0;
                }
                room_on_floor++;                
            }
        floor_number++; 
        }          
    }
}

// Calculates the total revenue from all occupied rooms
int total_revenue(struct room hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR], int previous_revenue) {
    int floor_number = 0;
    int new_revenue = 0;
    
    while (floor_number >= 0 && floor_number < TOTAL_FLOORS) { 
    int room_on_floor = 0;
        while (room_on_floor >= 0 && room_on_floor < ROOMS_PER_FLOOR) {
            if (hotel[floor_number][room_on_floor].booking_id >= 0) {
                new_revenue = new_revenue + hotel[floor_number][room_on_floor].price;
            }
            room_on_floor++;
        }
        floor_number++;
    }
           
            if (new_revenue > previous_revenue) {
               printf("The total revenue for the night is $%d\n", new_revenue);
               printf("This is $%d more than last time :)\n", new_revenue - 
               previous_revenue);
            } else if (new_revenue == previous_revenue) {
               printf("The total revenue for the night is $%d\n", new_revenue);
               printf("This is the same as the last time you asked :\\\n");             
            } else if (new_revenue < previous_revenue) {
               printf("The total revenue for the night is $%d\n", 
               new_revenue);
               printf("This is $%d less than last time (haha lol)\n", 
               (new_revenue - previous_revenue)*(-1));            
            }  
    
    return new_revenue;
}

// Adds a guest to the best available room, that is, the highest floor with
// an available room, and furthest available room to the left
void best_available(struct room hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR]) {
    int i = 0;
    int continue_loop = 1;
    int booking_num = highest_booking_num(hotel) + 1;
    
    if (total_num_bookings(hotel) == 64) {
    	printf("The hotel is full!");
    	continue_loop = 0;
    } else {
	    while (i >= 0 && i < TOTAL_FLOORS) {
            int j = 0;
            while (j >= 0 && j < ROOMS_PER_FLOOR && continue_loop == 1) {
                if (hotel[i][j].booking_id == -1) {
                    hotel[i][j].booking_id = booking_num;
          	        continue_loop = 0;
          	    }
            j++;        	
        	}
        i++;
        }        
    }   
}

// Swaps the guests of two specified rooms
void swap_rooms(struct room hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR], 
                int floor_num_1, int room_num_1, 
                int floor_num_2, int room_num_2) {
    
    int booking_num_1;
    int booking_num_2;
    scanf("%d %d %d %d", &floor_num_1, &room_num_1, &floor_num_2, 
    &room_num_2);  

    if (floor_num_1 >=0 && floor_num_1 < TOTAL_FLOORS
        && floor_num_2 >=0 && floor_num_2 < TOTAL_FLOORS
        && room_num_1 > 0 && room_num_1 < ROOMS_PER_FLOOR
        && room_num_2 > 0 && room_num_2 < ROOMS_PER_FLOOR) {
        
        booking_num_1 = hotel[floor_num_1][room_num_1].booking_id;
        booking_num_2 = hotel[floor_num_2][room_num_2].booking_id;
    
        hotel[floor_num_1][room_num_1].booking_id = booking_num_2;
        hotel[floor_num_2][room_num_2].booking_id = booking_num_1;
    } else {
        printf("Invalid room number!");
    }
}

// Returns the floor with the lowest price
int cheapest_floor(struct room hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR]) {
    int i = 7;
    int cheapest_floor = 7;

    while (i >= 0 && i < TOTAL_FLOORS) {
        int j = 0;
        if (hotel[i][j].price < hotel[cheapest_floor][j].price) {
            cheapest_floor = i;     
        }    
        i--;        
    }        

    return cheapest_floor;
}

// Returns the number of rooms available on a specified floor
int rooms_avail_on_floor(int floor_number, struct room hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR]) {
    int rooms_avail = 0;
    int i = 0;
    
    while (i >= 0 && i < ROOMS_PER_FLOOR) {   
        if (hotel[floor_number][i].booking_id == NO_BOOKING) {
            rooms_avail++;    
        }
        i++;        
    }
    
    return rooms_avail;
}

// Books a group of guests into the cheapest and lowest floor with space 
// to fit all guests
void group_booking_cheapest(int cheapest_or_highest, int num_guests, struct room hotel[TOTAL_FLOORS][ROOMS_PER_FLOOR]) {
    scanf("%d %d", &cheapest_or_highest, &num_guests);
    int g = 0;
    int room_on_floor = 0;
    int budget_floor = cheapest_floor(hotel);
    
    if (rooms_avail_on_floor(cheapest_floor(hotel), hotel) >= num_guests) {
        while (g < num_guests) {
            if (hotel[budget_floor][room_on_floor].booking_id == NO_BOOKING) { 
                hotel[budget_floor][room_on_floor].booking_id = 
                highest_booking_num(hotel) + 1;
                g++;
            } else {
                room_on_floor++;
            }
        }
    } else {
        budget_floor = cheapest_floor(hotel);
    }
}   

// need to keep track of the cheapest floor that fits everyone with a variable. before adding all the guests in after you've determined the correct floor...


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

