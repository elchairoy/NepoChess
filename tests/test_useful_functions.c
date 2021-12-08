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

    move w = create_a_move(1,8,0,0,0);
    /* Tests for commit_a_move_for_white function */
    commit_a_regular_move_for_white(&b, w);
    if ((get_piece_in_square(&b, 8) != white_pawn) || (get_piece_in_square(&b, 0) != empty ) || (get_piece_in_square(&b, 1) != empty))
    {
        printf("Error in commit_a_move_for_white / en passant.");
        return -1;
    }

    w = create_a_move(3, 11, 0, 0, 0);
    commit_a_regular_move_for_white(&b, w);
    if ((get_piece_in_square(&b, 3) != empty) || (get_piece_in_square(&b, 11) != 1))
    {
        printf("Error in commit_a_move_for_white / normal.");
        return -1;

    }

    w = create_a_move(0,0,0,0,1);
    commit_a_regular_move_for_white(&b, w);
    if (get_piece_in_square(&b, 6) != white_king || get_piece_in_square(&b, 5) != white_rook || get_piece_in_square(&b, 4) != empty || get_piece_in_square(&b, 7) != empty)
    {
        printf("Error in commit_a_move_for_white / short castle");
        return -1;
    }

    w = create_a_move(0,0,0,1,0);
    commit_a_regular_move_for_white(&b, w);
    if (get_piece_in_square(&b, 4) != empty || get_piece_in_square(&b, 0) != empty || get_piece_in_square(&b, 2) != white_king || get_piece_in_square(&b, 5) != white_rook)
    {
        printf("Error in commit_a_move_for_white / long castle");
        return -1;
    }

    w = create_a_move(53,61,0,0,0);
    commit_a_regular_move_for_white(&b, w);
    if (get_piece_in_square(&b, 53) != empty || get_piece_in_square(&b, 61) != white_queen)
    {
        printf("Error in commit_a_move_for_white / promotion");
        return -1;
    }


    /* Tests for commit_a_move_for_black function */
    w = create_a_move(54,47,0,0,0);
    commit_a_regular_move_for_black(&b, w);
    if ((get_piece_in_square(&b, 54) != empty) || (get_piece_in_square(&b, 55) != empty ) || (get_piece_in_square(&b, 47) != black_pawn))
    {
        printf("Error in commit_a_move_for_black / en passant");
        return -1;
    }

    w = create_a_move(0,0,0,0,1);
    commit_a_regular_move_for_black(&b, w);
    if (get_piece_in_square(&b, 62) != black_king || get_piece_in_square(&b, 61) != black_rook || get_piece_in_square(&b, 60) != empty || get_piece_in_square(&b, 63) != empty)
    {
        printf("Error in commit_a_move_for_black / short castle");
        return -1;
    }

    w = create_a_move(0,0,0,1,0);
    commit_a_regular_move_for_black(&b, w);
    if (get_piece_in_square(&b, 58) != black_king || get_piece_in_square(&b, 59) != black_rook || get_piece_in_square(&b, 60) != empty || get_piece_in_square(&b, 56) != empty)
    {
        printf("Error in commit_a_move_for_black / long castle");
        return -1;
    }
    
    w = create_a_move(20, 29, 0, 0, 0);
    commit_a_regular_move_for_black(&b, w);
    if ((get_piece_in_square(&b, 20) != empty) || (get_piece_in_square(&b, 29) != 9))
    {
        printf("Error in commit_a_move_for_white / normal.");
        return -1;

    }

    w = create_a_move(14,6,0,0,0);
    commit_a_regular_move_for_black(&b, w);
    if (get_piece_in_square(&b, 14) != empty || get_piece_in_square(&b, 6) != black_queen)
    {
        printf("Error in commit_a_move_for_black / promotion");
        return -1;
    }

    return 0;
}
