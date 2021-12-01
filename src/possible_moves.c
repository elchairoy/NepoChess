#include "possible_moves.h"

int func(){
    board start_board;
    char pieces[13] = {empty,white_knight,white_rook,white_queen,white_king,white_pawn,white_bishop,black_knight,black_rook,black_queen,black_king,black_pawn,black_bishop};
    char initial_board[32] = {white_rook << 4|white_knight,white_bishop << 4|white_queen,white_king<<4|
    white_bishop,white_knight<<4|white_rook,white_pawn << 4|white_pawn,white_pawn<<4|white_pawn,white_pawn<<4|
    white_pawn,white_pawn<<4|white_pawn,empty,empty,empty,empty,empty,empty,empty,empty,empty,empty,empty,empty
    ,empty,empty,empty,empty,black_pawn << 4|black_pawn,black_pawn<<4|black_pawn,black_pawn<<4|black_pawn,black_pawn<<4|
    black_pawn,black_rook << 4|black_knight,black_bishop << 4|black_queen,black_king<<4|black_bishop,black_knight<<4|black_rook};
    int i = 0;
    for(i;i<32;i++)
        start_board.squares[i] = initial_board[i];
    int piece = get_piece_in_square(&start_board, 1);
    printf("%c", pieces[piece]);
    return 0;
}