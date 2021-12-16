#include <stdio.h>
#include "../include/test_possible_moves.h"

/*
  Created by Elchairoy Meir on 29/11/2021.
*/

extern long int number_of_moves;

int main() {
  /*
    board START_BOARD;
    move *all_moves;
    char initial_board[32] = {white_rook << 4|white_knight,white_bishop << 4|white_queen,white_king<<4|
    white_bishop,white_knight<<4|white_rook,white_pawn << 4|white_pawn,white_pawn<<4|white_pawn,white_pawn<<4|
    white_pawn,white_pawn<<4|white_pawn,empty,empty,empty,empty,empty,empty,empty,empty,empty,empty,empty,empty
    ,empty,empty,empty,empty,black_pawn << 4|black_pawn,black_pawn<<4|black_pawn,black_pawn<<4|black_pawn,black_pawn<<4|
    black_pawn,black_rook << 4|black_knight,black_bishop << 4|black_queen,black_king<<4|black_bishop,black_knight<<4|black_rook};
    START_BOARD.can_black_castle_long = 1;
    START_BOARD.can_black_castle_short = 1;
    START_BOARD.can_white_castle_long = 1;
    START_BOARD.can_white_castle_short = 1;
    START_BOARD.pawn_en_passant_left = 0;
    START_BOARD.pawn_en_passant_right = 0;
    START_BOARD.whose_turn=1;

    int i;
    for(i = 0;i<32;i++)
    {
        START_BOARD.squares[i] = initial_board[i];
    }

    commit_a_move_for_white(&START_BOARD,create_a_move(3,21,0,0,0));
    commit_a_move_for_black(&START_BOARD,create_a_move(48,40,0,0,0));
    commit_a_move_for_white(&START_BOARD,create_a_move(12,20,0,0,0));
    commit_a_move_for_black(&START_BOARD,create_a_move(40,32,0,0,0));
    commit_a_move_for_white(&START_BOARD,create_a_move(5,26,0,0,0));
    commit_a_move_for_black(&START_BOARD,create_a_move(32,24,0,0,0));

    print_board(&START_BOARD);
    move m = minimax_for_white(&START_BOARD,2);
    printf("%d\n",m);
    printf("from %d to %d\n",get_src_square(m),get_dst_square(m));

    printf("%ld\n",number_of_moves);*/
    check();

    return 0;
}
