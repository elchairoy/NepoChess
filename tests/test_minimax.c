#include "../include/test_minimax.h"
void check_miminax() {
    /* Sets up the board: */

    board START_BOARD;
    move *all_moves;
    char initial_board[32] = {white_rook << 4|white_knight,white_bishop << 4|white_queen,white_king<<4|white_bishop,white_knight<<4|white_rook,white_pawn << 4|white_pawn,white_pawn<<4|white_pawn,white_pawn<<4|white_pawn,white_pawn<<4|white_pawn,empty,empty,empty,empty,empty,empty,empty,empty,empty,empty,empty,empty,empty,empty,empty,empty,black_pawn << 4|black_pawn,black_pawn<<4|black_pawn,black_pawn<<4|black_pawn,black_pawn<<4|black_pawn,black_rook << 4|black_knight,black_bishop << 4|black_queen,black_king<<4|black_bishop,black_knight<<4|black_rook};
    START_BOARD.can_black_castle_long = 1;
    START_BOARD.can_black_castle_short = 1;
    START_BOARD.can_white_castle_long = 1;
    START_BOARD.can_white_castle_short = 1;
    START_BOARD.pawn_en_passant_left = 1;
    START_BOARD.pawn_en_passant_right = 1;
    START_BOARD.whos_turn=1;

    int i;
    for(i = 0;i<32;i++)
    {
        START_BOARD.squares[i] = initial_board[i];
    }
    commit_a_move_for_white(&START_BOARD,create_a_move(3,21,0,0,0));
    commit_a_move_for_black(&START_BOARD,create_a_move(48,40,0,0,0));
    commit_a_move_for_white(&START_BOARD,create_a_move(12,28,0,0,0));
    commit_a_move_for_black(&START_BOARD,create_a_move(40,32,0,0,0));
    commit_a_move_for_white(&START_BOARD,create_a_move(11,19,0,0,0));
    commit_a_move_for_black(&START_BOARD,create_a_move(32,24,0,0,0));
    commit_a_move_for_white(&START_BOARD,create_a_move(5,26,0,0,0));
    commit_a_move_for_black(&START_BOARD,create_a_move(62,47,0,0,0));
    print_board(&START_BOARD);
    HashTable ht;
    ht_setup(&ht,sizeof(board),sizeof(double *),100000000);
    move m = get_best_move_white(&START_BOARD,5,4,&ht);
    printf("from %d to %d\n",get_src_square(m),get_dst_square(m));
}
/* RECORD: (outdated)
        4 - 1000ms, 787k
            4,3 - 300ms, 158k (without hash)
            4,3 - ?, 41k (with hash)
        5 - 1.7s, 4M
            5,4 - 3s, 248k
            5,3 - 3s, 248k
        
         */