#include "../include/test_minimax.h"

void check_miminax() {
    board START_BOARD;
    move *all_moves;
    char initial_board[32] = {white_rook << 4|white_knight,white_bishop << 4|white_queen,
                              white_king<<4|white_bishop,white_knight<<4|white_rook,white_pawn << 4|white_pawn,
                              white_pawn<<4|white_pawn,white_pawn<<4|white_pawn,white_pawn<<4|white_pawn,black_rook,
                              empty,empty,empty,empty,empty,empty,empty,empty,empty,
                              empty,empty,empty,empty,empty,empty,black_pawn << 4|black_pawn,
                              black_pawn<<4|black_pawn,black_pawn<<4|black_pawn,black_pawn<<4|black_pawn,
                              black_rook << 4|black_knight,black_bishop << 4|black_queen,black_king<<4|black_bishop,
                              black_knight<<4|empty};
    START_BOARD.can_black_castle_long = 1;
    START_BOARD.can_black_castle_short = 1;
    START_BOARD.can_white_castle_long = 1;
    START_BOARD.can_white_castle_short = 1;
    START_BOARD.pawn_en_passant_left = 0;
    START_BOARD.pawn_en_passant_right = 0;
    int i;
    for(i = 0;i<32;i++)
    {
        START_BOARD.squares[i] = initial_board[i];
    }

    if (evaluate_minimax_for_white(START_BOARD,2) != create_a_move(9,16,0,0,0))
        printf("error in minimax");
}