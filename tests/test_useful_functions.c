#include "../include/test_useful_functions.h"
/* This function tests the functions get_piece_in_square and change_the_square.
   If there is and error, prints an error message and returns 1, otherwise returns 0. */
int test_useful_functions() {
    board b;
    /* A demo squares array: */
    char arr[32] = {0x01,0x01,0x71,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01};
    
    int i;

    /* Copy arr to to board: */
    for (i = 0; i < 32; i++)
        b.squares[i] = arr[i];

    /* Test get_piece_in_square: */
    if (get_piece_in_square(&b,4) != 7) {
        printf("Error in get_piece_in_square.");
        return 1;
    }

    /* Test change_the_square: */
    change_the_square(&b, 4, 5);
    if (get_piece_in_square(&b,4) != 5) {
        printf("Error in change_the_square.");
        return 1;
    }


    if (create_a_move(1,2,3,1,0) != 0x7081) {
        printf("Error in create a move.");
        return 1;
    }

    return 0;
}
