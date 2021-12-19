#include "test_make_moves.h"
void check_make_moves() {
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
    move w = create_a_move(1,8,0,0,0);

    /* Tests for commit_a_move_for_white function */
    commit_a_move_for_white(&b, w);
    if ((get_piece_in_square(&b, 8) != white_pawn) || (get_piece_in_square(&b, 0) != empty ) || (get_piece_in_square(&b, 1) != empty))
    {
        printf("Error in commit_a_move_for_white / en passant.");
        return -1;
    }

    w = create_a_move(3, 11, 0, 0, 0);
    commit_a_move_for_white(&b, w);
    if ((get_piece_in_square(&b, 3) != empty) || (get_piece_in_square(&b, 11) != 1))
    {
        printf("Error in commit_a_move_for_white / normal.");
        return -1;

    }

    w = create_a_move(0,0,0,0,1);
    commit_a_move_for_white(&b, w);
    if (get_piece_in_square(&b, 6) != white_king || get_piece_in_square(&b, 5) != white_rook || get_piece_in_square(&b, 4) != empty || get_piece_in_square(&b, 7) != empty)
    {
        printf("Error in commit_a_move_for_white / short castle");
        return -1;
    }

    w = create_a_move(0,0,0,1,0);
    commit_a_move_for_white(&b, w);
    if (get_piece_in_square(&b, 4) != empty || get_piece_in_square(&b, 0) != empty || get_piece_in_square(&b, 2) != white_king || get_piece_in_square(&b, 5) != white_rook)
    {
        printf("Error in commit_a_move_for_white / long castle");
        return -1;
    }

    w = create_a_move(53,61,0,0,0);
    commit_a_move_for_white(&b, w);
    if (get_piece_in_square(&b, 53) != empty || get_piece_in_square(&b, 61) != white_queen)
    {
        printf("Error in commit_a_move_for_white / promotion");
        return -1;
    }


    /* Tests for commit_a_move_for_black function */
    w = create_a_move(54,47,0,0,0);
    commit_a_move_for_black(&b, w);
    if ((get_piece_in_square(&b, 54) != empty) || (get_piece_in_square(&b, 55) != empty ) || (get_piece_in_square(&b, 47) != black_pawn))
    {
        printf("Error in commit_a_move_for_black / en passant");
        return -1;
    }

    w = create_a_move(0,0,0,0,1);
    commit_a_move_for_black(&b, w);
    if (get_piece_in_square(&b, 62) != black_king || get_piece_in_square(&b, 61) != black_rook || get_piece_in_square(&b, 60) != empty || get_piece_in_square(&b, 63) != empty)
    {
        printf("Error in commit_a_move_for_black / short castle");
        return -1;
    }

    w = create_a_move(0,0,0,1,0);
    commit_a_move_for_black(&b, w);
    if (get_piece_in_square(&b, 58) != black_king || get_piece_in_square(&b, 59) != black_rook || get_piece_in_square(&b, 60) != empty || get_piece_in_square(&b, 56) != empty)
    {
        printf("Error in commit_a_move_for_black / long castle");
        return -1;
    }
    
    w = create_a_move(20, 29, 0, 0, 0);
    commit_a_move_for_black(&b, w);
    if ((get_piece_in_square(&b, 20) != empty) || (get_piece_in_square(&b, 29) != 9))
    {
        printf("Error in commit_a_move_for_white / normal.");
        return -1;

    }

    w = create_a_move(14,6,0,0,0);
    commit_a_move_for_black(&b, w);
    if (get_piece_in_square(&b, 14) != empty || get_piece_in_square(&b, 6) != black_queen)
    {
        printf("Error in commit_a_move_for_black / promotion");
        return -1;
    }
    w = create_a_move(4,5,0,0,0);
    if (b.can_white_castle_short == 1 || b.can_white_castle_long == 1) {
        printf("Error in commit_a_move_for_white / normal / update castling");
        return -1;
    }

    w = create_a_move(63,62,0,0,0);
    if (b.can_black_castle_long == 1) {
        printf("Error in commit_a_move_for_black / normal / update castling");
        return -1;
    }
    board board1;
    char b1[32] = {white_rook << 4|white_knight,white_bishop << 4|white_queen,white_king<<4|white_bishop,white_knight<<4|white_rook,white_pawn << 4|white_pawn,white_pawn<<4|white_pawn,white_pawn<<4|white_pawn,white_pawn<<4|white_pawn,empty,empty,empty,empty,empty,empty,empty,empty,empty,empty,empty,empty,empty,empty,empty,empty,black_pawn << 4|black_pawn,black_pawn<<4|black_pawn,black_pawn<<4|black_pawn,black_pawn<<4|black_pawn,black_rook << 4|black_knight,black_bishop << 4|black_queen,black_king<<4|black_bishop,black_knight<<4|black_rook};
    for (i = 0; i < 32; i++)
        board1.squares[i] = b1[i];

    w = create_a_move(8,24,0,0,0);
    commit_a_move_for_white(&board1,w);

    w = create_a_move(24,32,0,0,0);
    commit_a_move_for_white(&board1,w);

    w = create_a_move(49,33,0,0,0);
    commit_a_move_for_white(&board1,w);

    if (board1.pawn_en_passant_right == 0) {
        printf("Error in commit_a_move_for_black / normal / en passant check");
        return -1;
    }

    w = create_a_move(33,33 - 8,0,0,0);
    if (board1.pawn_en_passant_right == 1) {
        printf("Error in commit_a_move_for_black / normal / en passant updating");
        return -1;
    }
}