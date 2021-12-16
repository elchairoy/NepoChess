#include "../include/test_possible_moves.h"

#define get_square_number(column,row) ((row - '0' - 1) * 8 + (column - 'a'))


move generate_random(board *the_board){
    move *all_moves = get_all_moves(the_board);
    int len = 0;
    while(all_moves[len] != END)
        len++;
    return all_moves[rand() % len];
}


int white_move(board *the_board){
    int i = 0, row;
    char temp[3];
    move *all_moves;
    char column, src_square, dst_square;
    while(1){
        printf("enter src: ");
        scanf("%s", temp);
        src_square = get_square_number(temp[0], temp[1]);
        if(check_src(the_board, src_square, WHITE))
        {
            printf("enter dst: ");
            scanf("%s", temp);
            dst_square = get_square_number(temp[0], temp[1]);
            if(dst_square <= 63 || dst_square >= 0)
            {
                all_moves = get_all_moves(the_board);
                i = 0;
                while(all_moves[i] != END)
                {
                    if(src_square == get_src_square(all_moves[i]) && dst_square == get_dst_square(all_moves[i]))
                    {
                        commit_a_move_for_white(the_board, all_moves[i]);
                        return 0;
                    }
                    i++;    
                }
            }
        }
        system("clear");
        print_board(the_board);
    }
}


int game(board *the_board){
    while(1)
    {
        print_board(the_board);
        if(get_all_moves(the_board)[0] == END){
            if(isAttacked_by_black(the_board, find_king_square(the_board, WHITE))){
                printf("CHECKMATE 0-1\n");
                return 0;
            }
            printf("STALMATE 0.5-0.5\n");
            return 0;
        }
        white_move(the_board);
        print_board(the_board);
        if(get_all_moves(the_board)[0] == END){
            if(isAttacked_by_white(the_board, find_king_square(the_board, BLACK))){
                printf("CHECKMATE 1-0\n");
                return 0;
            }
            printf("STALMATE 0.5-0.5\n");
            return 0;
        }
        commit_a_move_for_black(the_board ,minimax_for_black(the_board,3));
        system("clear");
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
    START_BOARD.whose_turn=WHITE;


    int i;
    for(i = 0;i<32;i++)
    {
        START_BOARD.squares[i] = initial_board[i];
    }
    all_moves = get_all_moves(&START_BOARD);
    i = 0;
    while(all_moves[i] != END){
        printf("from %d to %d\n", get_src_square(all_moves[i]), get_dst_square(all_moves[i]));
        i++;
    }
    /*system("clear");
    game(&START_BOARD);*/
    return 0;
}