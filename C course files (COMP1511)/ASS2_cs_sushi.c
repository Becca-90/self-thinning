// cs_sushi.c
//
// This program was written by Rebecca Stolper (z3378134)
// on 05 August 2022
//
// This program allows the user to manage their sushi train restaurant
// Tables can be added, customers added to free tables, and sushi plates
// Added to the train in a given order

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////  CONSTANTS  /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Provided constants
#define TRUE 1
#define FALSE 0

#define MAX_STRING_LENGTH 100
#define EMPTY_CUSTOMER "EMPTY"

#define COMMAND_ADD_TABLE 'a'
#define COMMAND_ADD_CUSTOMER 'c'
#define COMMAND_PRINT_TABLES 'p'
#define COMMAND_ADD_PLATE 'r'
#define COMMAND_PRINT_PLATES 't'

// Provided Enums

// the numerical value is the cost of that plate color
enum plate_colour { RED = 3, GREEN = 4, BLUE = 5, PURPLE = 6, ORANGE = 7 };

enum sushi_type { VEGETARIAN, SEAFOOD, CHICKEN, TEMPURA };

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////  STRUCTS  //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Provided structs
struct table {
    char customer[MAX_STRING_LENGTH];
    struct plate *orders;
    struct table *next;
};

struct plate {
    char roll_name[MAX_STRING_LENGTH];
    enum plate_colour colour;
    enum sushi_type type;
    struct plate *next;
};

struct restaurant {
    struct table *tables;
    struct plate *plates;
};

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  FUNCTION PROTOTYPES  ////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Helper Functions
void print_restaurant(struct restaurant *restaurant);
int scanf_command(char *command);
void interpret_line(
    char buffer[MAX_STRING_LENGTH], char name[MAX_STRING_LENGTH],
    enum plate_colour *colour, enum sushi_type *type);

void interpret_order(
    char buffer[MAX_STRING_LENGTH], char customer[MAX_STRING_LENGTH],
    char roll[MAX_STRING_LENGTH]);

enum plate_colour string_to_colour(char colour[MAX_STRING_LENGTH]);
enum sushi_type string_to_type(char type[MAX_STRING_LENGTH]);
void remove_newline(char input[MAX_STRING_LENGTH]);
char color_to_char(enum plate_colour colour);
void to_type(char types[MAX_STRING_LENGTH], enum sushi_type type);
void to_colour(char cols[MAX_STRING_LENGTH], enum plate_colour colour);

struct table *create_table(struct restaurant *sushi_restaurant);
struct table *last(struct table *head);
struct table *add_customer(struct restaurant *sushi_restaurant);
struct plate *create_plate(struct restaurant *sushi_restaurant);
void print_train(struct restaurant *sushi_restaurant);

// add a new empty table to the restaurant
struct table *create_table(struct restaurant *sushi_restaurant) {
    struct table *new_table = malloc(sizeof(struct table));
    strcpy(new_table->customer, EMPTY_CUSTOMER);
    new_table->orders = NULL;
    new_table->next = NULL;        

    if (sushi_restaurant->tables == NULL) {
        sushi_restaurant->tables = new_table;
        strcpy(new_table->customer, EMPTY_CUSTOMER);
        new_table->orders = NULL;
        new_table->next = NULL;
        sushi_restaurant->tables = new_table;
    } else {
        struct table *next_table = last(sushi_restaurant->tables);
        next_table->next = new_table;
    }
    
    return sushi_restaurant->tables;
}
  
    
// return pointer to last table in list, if list is empty returns NULL   
struct table *last(struct table *head) {
    if (head == NULL) {
        return NULL;
    }
    struct table *end_table = head;
    while (end_table->next != NULL) {
        end_table = end_table->next;
    }
    return end_table;
}

// add a customer by name to the next free table
struct table *add_customer(struct restaurant *sushi_restaurant) {
    struct table *current = sushi_restaurant->tables;  
    char customer_name[MAX_STRING_LENGTH];
    
    printf("Enter customer name: ");
    fgets(customer_name, MAX_STRING_LENGTH, stdin);    
    remove_newline(customer_name); 
         
    if (current == NULL) {
        printf("No empty tables!\n");
        return sushi_restaurant->tables;     
    }
    
    if (current != NULL && strcmp(current->customer, EMPTY_CUSTOMER) == 0) {
        strcpy(current->customer, customer_name);
        return sushi_restaurant->tables;            
    } else {         
        while (current != NULL &&
        strcmp(current->customer, EMPTY_CUSTOMER) != 0) {
            current = current->next;
        }           
        if (current == NULL) {
            printf("No empty tables!\n");
            return sushi_restaurant->tables; 
        } else {        
            strcpy(current->customer, customer_name);
            return sushi_restaurant->tables;           
        }
    }            
}

// create a new plate and add to the train in correct order:
// vegetarian, seafood, chicken, tempura
struct plate *create_plate(struct restaurant *sushi_restaurant) {
    struct plate *new_plate = malloc(sizeof(struct plate));
 
    char remaining_input[MAX_STRING_LENGTH];   
    fgets(remaining_input, MAX_STRING_LENGTH, stdin);

    char dish_name[MAX_STRING_LENGTH];
    enum plate_colour colour;
    enum sushi_type type;
    
    interpret_line(remaining_input, dish_name, &colour, &type);
    
    strcpy(new_plate->roll_name, dish_name);    
    new_plate->colour = colour;
    new_plate->type = type;
    new_plate->next = NULL;

    if (sushi_restaurant->plates == NULL) {
        sushi_restaurant->plates = new_plate;
        return sushi_restaurant->plates;
    }
    
    struct plate *prev_plate = sushi_restaurant->plates;
    struct plate *curr_plate = prev_plate; 
  
    if (sushi_restaurant->plates != NULL) {
        while (curr_plate->type <= new_plate->type 
        && curr_plate->next != NULL) {
            prev_plate = curr_plate;
            curr_plate = curr_plate->next;
        }
        if (curr_plate->next == NULL && curr_plate->type <= new_plate->type) {
            curr_plate->next = new_plate;
            new_plate->next = NULL;      
            return sushi_restaurant->plates; 
        } else if (curr_plate->next == NULL && 
        curr_plate->type > new_plate->type) {
            prev_plate->next = new_plate;
            new_plate->next = curr_plate;
            return sushi_restaurant->plates;
        } else if (curr_plate->next != NULL && 
        curr_plate->type > new_plate->type) {
            prev_plate->next = new_plate;
            new_plate->next = curr_plate;               
            return sushi_restaurant->plates;                 
        }
    }
}     

// print out the ordered train with plate type, plate colour and sushi type
void print_train(struct restaurant *sushi_restaurant) {

    if (sushi_restaurant->plates == NULL) {
        printf("    empty :(\n");
    }

    struct plate *curr_plate = sushi_restaurant->plates;
         
    if (curr_plate != NULL) { 
        char my_colour[MAX_STRING_LENGTH];
        char my_type[MAX_STRING_LENGTH];    
        to_colour(my_colour, curr_plate->colour);
        to_type(my_type, curr_plate->type); 
        
        printf("    %s-%s-%s\n", curr_plate->roll_name, my_type, my_colour);
        printf("      |\n");
        printf("      v\n");
                                   
        while (curr_plate->next != NULL) {
            curr_plate = curr_plate->next;
            
            char my_colour2[MAX_STRING_LENGTH];
            char my_type2[MAX_STRING_LENGTH];
            to_colour(my_colour2, curr_plate->colour);
            to_type(my_type2, curr_plate->type);
    
            printf("    %s-%s-%s\n", 
            curr_plate->roll_name, my_type2, my_colour2);
            printf("      |\n");
            printf("      v\n");
            
        }      
    }
}

////////////////////////////////////////////////////////////////////////////////
//////////////////////////  FUNCTION IMPLEMENTATIONS  //////////////////////////
////////////////////////////////////////////////////////////////////////////////

int main(void) {
    // a pointer to the restaurant struct
    struct restaurant *sushi_restaurant = NULL;
    sushi_restaurant = malloc(sizeof(*sushi_restaurant));
    sushi_restaurant->tables = NULL;
    sushi_restaurant->plates = NULL;
    
    printf("Welcome to CSE Sushi Restaurant!\n");
    print_restaurant(sushi_restaurant);

    printf("Enter command: ");
    char command = 0;
    
    while (scanf_command(&command) == 1) {
    
        if (command == COMMAND_PRINT_TABLES) {
            print_restaurant(sushi_restaurant);
            printf("Enter command: ");
        } else if (command == COMMAND_ADD_TABLE) {
            create_table(sushi_restaurant);
            printf("Enter command: ");
        } else if (command == COMMAND_ADD_CUSTOMER) {
            add_customer(sushi_restaurant);
            printf("Enter command: ");            
        } else if (command == COMMAND_ADD_PLATE) {
            create_plate(sushi_restaurant);
            printf("Enter command: ");
        } else if (command == COMMAND_PRINT_PLATES) {
            print_train(sushi_restaurant);
            printf("Enter command: ");            
        }
    
    }
    
    printf("Thank you for dining with CSE Sushi Restaurant!\n");
    free(sushi_restaurant);
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

// Provided Function - DO NOT EDIT
void print_restaurant(struct restaurant *restaurant) {
    int i;
    if (restaurant == NULL) {
        printf("ERROR: No restaurant!\n");
        return;
    };

    printf("CSE Sushi Restaurant\n");
    struct table *table = restaurant->tables;
    int table_num = 0;
    while (table != NULL) {
        int table_length = 5;
        if (strcmp(table->customer, EMPTY_CUSTOMER) != 0) {
            table_length = strlen(table->customer) + 4;
        }
        // calculate number of plates
        int number_of_plates = 0;
        struct plate *curr = table->orders;
        while (curr != NULL) {
            number_of_plates++;
            curr = curr->next;
        }

        printf(" ");
        for (i = 0; i < table_length; i++) {
            printf("_");
        }
        printf(" ");

        // print out the top row
        for (i = 0; i < number_of_plates; i++) {
            printf("    _____ ");
        }

        printf("\n");

        // print out the data
        int occupied = FALSE;
        if (strcmp(table->customer, "EMPTY") != 0) {
            occupied = TRUE;
        }
        if (occupied) {
            printf("|  %s  |-->", table->customer);
        } else {
            printf("|  %d  |-->", table_num);
        }

        // print out the plates
        struct plate *order = table->orders;
        while (order != NULL) {
            printf("|  %c  |-->", color_to_char(order->colour));

            order = order->next;
        }

        printf("\n");
        printf(".");
        for (i = 0; i < table_length; i++) {
            printf("-");
        }
        printf(".");
        // print out the top row
        for (i = 0; i < number_of_plates; i++) {
            printf("   |-----|");
        }

        printf("\n");
        table = table->next;
        table_num++;
    }
}

// Helper Function
// scans a single character from the user and returns the value of scanf;
//
// Parameters:
//  - command: a pointer to a character to store the command
//
// Returns:
//  - the value that scanf returns (this will be 1 if it was successfully read);
//
// Usage:
//  ```
//  char command;
//  while (scanf_command(&command) == 1) {
//  ```
// this function does some wizadry that you **do not need to understand**
// for you to ensure that subsequent
// calls to fgets works correctlly.
int scanf_command(char *command) {
    // read in character + newline + null-terminator
    char buffer[3];
    char *result = fgets(buffer, 3, stdin);
    if (result == NULL) {
        return EOF;
    }

    // a non a-z character probably means not a char
    if (buffer[0] < 'a' || buffer[0] > 'z') {
        return EOF;
    }

    // set the character
    *command = buffer[0];
    return 1;
}

// Helper Function
// You DO NOT NEED TO UNDERSTAND THIS FUNCTION, and will not need to change it.
//
// Given a raw string in the format: [string] [enum1] [enum2]
// This function will extract the relevant values into the given variables.
// The function will also remove any newline characters.
//
// For example, if given: "salmon red seafood"
// The function will copy the string:
//     "salmon" into the 'name' array
// And will copy the enums:
//     red      into the colour pointer
//     seafood  into the type pointer
//
// If you are interested, `strtok` is a function which takes a string,
// and splits it up into before and after a "token" (the second argument)
//
// Parameters:
//     buffer  = A null terminated string in the following format
//               [string] [enum1] [enum2]
//     name    = An array for the [string] to be copied into
//     colour  = A pointer to where [enum1] should be stored
//     type    = A pointer to where [enum2] should be stored
// Returns:
//     None
void interpret_line(
    char buffer[MAX_STRING_LENGTH], char name[MAX_STRING_LENGTH],
    enum plate_colour *colour, enum sushi_type *type) {
    // Remove extra newline
    remove_newline(buffer);

    // Extract value 1 as string (sushi roll name)
    char *name_str = strtok(buffer, " ");
    if (name_str != NULL) {
        // Extract word
        strcpy(name, name_str);
    }

    // Extract value 2 as str, then enum
    char *colour_str = strtok(NULL, " ");
    if (colour_str != NULL) {
        *colour = string_to_colour(colour_str);
    }

    // Extract value 2 as str, then enum
    char *type_str = strtok(NULL, " ");
    if (type_str != NULL) {
        *type = string_to_type(type_str);
    }

    if (name_str == NULL || colour_str == NULL || type_str == NULL) {
        // If any of these are null, there were not enough words.
        printf("Could not properly interpret line: %s.\n", buffer);
    }
}

// Helper Function
// You DO NOT NEED TO UNDERSTAND THIS FUNCTION, and will not need to change it.
//
// Given a raw string in the following foramt: [string1] [string2]
// This function will extract the relevant values into the given variables.
// The function will also remove any newline characters.
//
// For example, if given: "Gab salmon"
// The function will put:
//     "Gab" into the 'customer' array
//     "salmon" into the 'roll' array
//
// Parameters:
//     buffer   = A null terminated string in the following format
//                [string1] [string2]
//     customer = An array for the [string1] to be copied into
//     roll     = An array for the [string2] to be copied into
// Returns:
//     None
void interpret_order(
    char buffer[MAX_STRING_LENGTH], char customer[MAX_STRING_LENGTH],
    char roll[MAX_STRING_LENGTH]) {
    // Remove extra newline
    remove_newline(buffer);

    // Extract value 1 as string
    char *customer_str = strtok(buffer, " ");
    if (customer_str != NULL) {
        strcpy(customer, customer_str);
    }

    // Extract value 2 as string
    char *roll_str = strtok(NULL, " ");
    if (roll_str != NULL) {
        strcpy(roll, roll_str);
    }

    if (customer_str == NULL || roll_str == NULL) {
        // If any of these are null, there were not enough words.
        printf("Could not properly interpret line: %s.\n", buffer);
    }
}

// Helper Function
// You likely do not need to change this function.
//
// Given a raw string will remove and first newline it sees.
// The newline character wil be replaced with a null terminator ('\0')
void remove_newline(char input[MAX_STRING_LENGTH]) {
    // Find the newline or end of string
    int index = 0;
    while (input[index] != '\n' && input[index] != '\0') {
        index++;
    }
    // Goto the last position in the array and replace with '\0'
    // Note: will have no effect if already at null terminator
    input[index] = '\0';
}

// Helper Function
// You likely do not need to change this function.
//
// Given an enum plate_colour will return the first letter of enum, or ? if the
// value is not one of the plate_colour values.
// Parameters:
//     colour  = enum plate_colour for a plate
// Returns:
//     char    = character represtning the first letter of the plate colour
char color_to_char(enum plate_colour colour) {
    if (colour == RED) {
        return 'r';
    } else if (colour == GREEN) {
        return 'g';
    } else if (colour == BLUE) {
        return 'b';
    } else if (colour == PURPLE) {
        return 'p';
    } else if (colour == ORANGE) {
        return 'o';
    } else {
        return '?';
    }
}

// Helper Function
// You likely do not need to change this function.
//
// Given a raw string will return the corresponding enum plate_colour, or FALSE
// if the string doesn't correspond with the enums.
// Parameters:
//     colour  = string representing the corresponding enum plate_colour value
// Returns:
//     enum plate_colour
enum plate_colour string_to_colour(char colour[MAX_STRING_LENGTH]) {
    if (strcmp(colour, "red") == 0) {
        return RED;
    } else if (strcmp(colour, "green") == 0) {
        return GREEN;
    } else if (strcmp(colour, "blue") == 0) {
        return BLUE;
    } else if (strcmp(colour, "purple") == 0) {
        return PURPLE;
    } else if (strcmp(colour, "orange") == 0) {
        return ORANGE;
    }
    return FALSE;
}

// Helper Function
// You likely do not need to change this function.
//
// Given a raw string will return the corresponding enum sushi_type, or FALSE
// if the string doesn't correspond with the enums.
// Parameters:
//     type  = string representing the corresponding enum sushi_type value
// Returns:
//     enum sushi_type
enum sushi_type string_to_type(char type[MAX_STRING_LENGTH]) {
    if (strcmp(type, "vegetarian") == 0) {
        return VEGETARIAN;
    } else if (strcmp(type, "seafood") == 0) {
        return SEAFOOD;
    } else if (strcmp(type, "chicken") == 0) {
        return CHICKEN;
    } else if (strcmp(type, "tempura") == 0) {
        return TEMPURA;
    }
    return FALSE;
}

// Helper Function
// You likely do not need to change this function.
//
// Given an enum sushi_type will return the enum name as a string, or "ERROR" if
// the value was not one of the given enums.
// Parameters:
//     types  = string to store the name of the enum in
//     type   = sushi_type enum to have the name stored in types.
// Returns:
//     None
void to_type(char types[MAX_STRING_LENGTH], enum sushi_type type) {
    if (type == VEGETARIAN) {
        strcpy(types, "vegetarian");
    } else if (type == SEAFOOD) {
        strcpy(types, "seafood");
    } else if (type == CHICKEN) {
        strcpy(types, "chicken");
    } else if (type == TEMPURA) {
        strcpy(types, "tempura");
    } else {
        strcpy(types, "ERROR");
    }
}

// Helper Function
// You likely do not need to change this function.
//
// Given an enum plate_colour will return the enum name as a string, or "ERROR"
// if the value was not one of the given enums.
// Parameters:
//     cols   = string to store the name of the enum in
//     colour = plate_colour enum to have the name stored in cols
// Returns:
//     None
void to_colour(char cols[MAX_STRING_LENGTH], enum plate_colour colour) {
    if (colour == RED) {
        strcpy(cols, "red");
    } else if (colour == BLUE) {
        strcpy(cols, "blue");
    } else if (colour == GREEN) {
        strcpy(cols, "green");
    } else if (colour == PURPLE) {
        strcpy(cols, "purple");
    } else if (colour == ORANGE) {
        strcpy(cols, "orange");
    } else {
        strcpy(cols, "ERROR");
    }
}
