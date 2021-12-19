#include "../include/test_useful_functions.h"
/* This function tests the functions get_piece_in_square and change_the_square.
   If there is and error, prints an error message and returns 1, otherwise returns 0. */
int test_useful_functions() {
    board b;
    /* A demo squares array: */
    char arr[32] = {0xb5,0x01,0x71,0x01,0x05,0x01,0x01,0xb1,0x01,0x01,0x91,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x01,0x01,0x05,0xb5,0x01,0x01,0x01};
    
    int i;

    /* Copy arr to to board: */
    for (i = 0; i < 32; i++)
        b.squares[i] = arr[i];
    b.can_black_castle_short = 1;
    b.can_white_castle_short = 1;
    b.can_black_castle_long = 1;
    b.can_white_castle_long = 1;


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

    /* Test create_a_move: */
    if (create_a_move(1,2,3,1,0) != 0x7081) {
        printf("Error in create_a_move.");
        return 1;
    }

    move m = create_a_move(1,2,3,1,0);

    /* Test get_src_square */
    if (get_src_square(m) != 1) {
        printf("Error in get_src_square.");
        return -1;
    }

    /* Test get_dst_square */
    if (get_dst_square(m) != 2) {
        printf("Error in get_dst_square.");
        return -1;
    }

    /* Test get_promotion_choice */
    if (get_promotion_choice(m) != 3) {
        printf("Error in get_promotion_choice.%d", get_promotion_choice(m));
        return -1;
    }

    /* Test get_is_long_castle */
    if (get_is_long_castle(m) != 1) {
        printf("Error in get_is_long_castle.");
        return -1;
    }

    /* Test get_is_short_castle */
    if (get_is_short_castle(m) != 0) {
        printf("Error in get_is_short_castle.");
        return -1;
    }

    return 0;
}
