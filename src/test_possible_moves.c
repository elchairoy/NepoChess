#include "test_possible_moves.h"
int game(board *the_board){
    int src, dst, i = 0;
    move *all_moves;
    char the_move = WHITE;
    while(1)
    {
        if(get_all_moves(the_board, the_move)[0] == END){
            print_board(the_board);
            printf("CHECKMATE!!!");
            break;
        }
        printf("\n1 for white and 0 for black: %d\n", the_move);
        print_board(the_board);
        printf("enter src: ");
        scanf("%d", &src);
        if(check_src(the_board, src, the_move))
        {
            printf("enter dst: ");
            scanf("%d", &dst);
            if(dst <= 63 || dst >= 0)
            {
                all_moves = get_all_moves(the_board, the_move);
                i = 0;
                while(all_moves[i] != END)
                {
                    if(src == get_src_square(all_moves[i]) && dst == get_dst_square(all_moves[i]))
                    {
                        if(the_move)
                            commit_a_move_for_white(the_board, all_moves[i]);
                        else
                            commit_a_move_for_black(the_board, all_moves[i]);
                        the_move = !the_move;
                        break;
                    }
                    i++;    
                }
            }
        }
    }
    return 0;
}

int check_src(board *the_board, char src, char the_move){
    if(src > 63 || src < 0)
        return 0;
    if(get_piece_in_square(the_board, src) == empty)
        return 0;
    if(color_of_piece(src, the_board) != the_move)
        return 0;
    return 1;
}


int check(){
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
    int i;
    for(i = 0;i<32;i++)
    {
        START_BOARD.squares[i] = initial_board[i];
    }
    all_moves = get_all_moves(&START_BOARD, WHITE);
    i = 0;
    while(all_moves[i] != END){
        printf("from %d to %d\n", get_src_square(all_moves[i]), get_dst_square(all_moves[i]));
        i++;
    }
    game(&START_BOARD);
    return 0;
}