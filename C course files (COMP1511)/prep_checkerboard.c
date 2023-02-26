#include <stdio.h>
#include <assert.h>

#define BOARD_LENGTH 8
#define PIECE_RED 'R'
#define PIECE_BLACK 'B'
#define PIECE_EMPTY ' '
#define TYPE_KING 1
#define TYPE_NORMAL 0
struct board_square {
    int type;
    char piece_color;
};

// Prints out a checkerboard using the provided 2D array as reference.
void print_checkerboard(struct board_square board[BOARD_LENGTH][BOARD_LENGTH]);
    
int main(void) {

    struct board_square checkerboard[BOARD_LENGTH][BOARD_LENGTH];
    
    int row_index = 0;    
    while (row_index < BOARD_LENGTH) {
        
        int column_index = 0;
        while (column_index < BOARD_LENGTH) {
            checkerboard[row_index][column_index].type = PIECE_EMPTY;
            checkerboard[row_index][column_index].piece_color = TYPE_NORMAL;
            column_index++;
        }
        row_index++;
    }
    
    int input_row;
    int input_column;
    char input_color;    
    int input_type;
    
    printf("Please enter pieces:\n");
    
    while (scanf(" %d %d %c %d", 
    &input_row, &input_column, &input_color, &input_type) == 4) {
        checkerboard[input_row][input_column].piece_color = input_color;
        checkerboard[input_row][input_column].type = input_type;
    }

    print_checkerboard(checkerboard);

    return 0;
}

/*
// initialise each member variable with PIECE_EMPTY and TYPE_NORMAL
void init_board(struct board_square board[BOARD_LENGTH][BOARD_LENGTH]) {    
    int row_index = 0;    
    while (row_index < BOARD_LENGTH) {
        int column = 0;
        while (column < BOARD_LENGTH) {
            board[row_index][column].type = PIECE_EMPTY;
            board[row_index][column].piece_color = TYPE_NORMAL;
            column++;
        }
        row_index++;
    }
}
*/
///////////////////////////////////////////////////////////////////////////////
//////////////////// DO NOT EDIT THE CODE BELOW THIS LINE! ////////////////////
///////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// print_checkerboard(): Prints out a checkerboard using the provided 2D array
//                       as reference.
//
// Takes in:
// - `board[BOARD_LENGTH][BOARD_LENGTH]` -- The 2D array containing a
//                                          representation of the checkerboard
//
// Returns: nothing.
void print_checkerboard(struct board_square board[BOARD_LENGTH][BOARD_LENGTH]) {
    int row_index = 0;
    while (row_index < BOARD_LENGTH) {

        // NOTE: Print row dividers of checkerboard
        printf("+-----+-----+-----+-----+-----+-----+-----+-----+\n");
        printf("|");
        
        int column_index = 0;
        while (column_index < BOARD_LENGTH) {
            
            // NOTE: Check that all struct values contain valid input.
            assert(
                board[row_index][column_index].piece_color == PIECE_RED ||
                board[row_index][column_index].piece_color == PIECE_BLACK ||
                board[row_index][column_index].piece_color == PIECE_EMPTY
            );
   
            assert(
                board[row_index][column_index].type == TYPE_KING || 
                board[row_index][column_index].type == TYPE_NORMAL
            );
            
            // NOTE: Print column dividers of checkerboard
            if (board[row_index][column_index].type == TYPE_KING) {
                printf(" %c-K |", board[row_index][column_index].piece_color);
            } else {
                printf("  %c  |", board[row_index][column_index].piece_color);

            }
            
            column_index++;
        }
        
        printf("\n");
        row_index++;
    }
    // NOTE: Print final row divider of checkerboard
    printf("+-----+-----+-----+-----+-----+-----+-----+-----+\n");

    return;
}
