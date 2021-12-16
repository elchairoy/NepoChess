#include <stdio.h>
#include "../include/test_minimax.h"

/*
  Created by Elchairoy Meir on 29/11/2021.
*/

extern long int number_of_moves;

int main() {
    board START_BOARD;
    move *all_moves;
    char initial_board[32] = {empty<<4|empty,empty<<4|black_rook,empty,empty,empty<<4|empty,empty<<4|empty,empty<<4|empty,
                              empty<<4|white_king,empty,empty,empty,empty,white_rook<<4|empty,
                              empty<<4|black_bishop,black_king<<4|empty,empty,empty<<4|empty,empty,
                              empty<<4|empty,empty<<4|empty,empty,empty,empty<<4|empty,
                              empty<<4|empty,empty,empty<<4|empty,empty,
                              empty<<4|empty,empty,empty,empty,empty
                              };
    START_BOARD.can_black_castle_long = 0;
    START_BOARD.can_black_castle_short = 0;
    START_BOARD.can_white_castle_long = 0;
    START_BOARD.can_white_castle_short = 0;
    START_BOARD.pawn_en_passant_left = 0;
    START_BOARD.pawn_en_passant_right = 0;
    START_BOARD.whose_turn = 0;
    int i;
    for(i = 0;i<32;i++)
    {
        START_BOARD.squares[i] = initial_board[i];
    }

    move m = minimax_for_black(&START_BOARD,4);
    printf("from %d to %d\n",get_src_square(m),get_dst_square(m));

    printf("%ld\n",number_of_moves);

    return 0;
}
