#include "../include/play_minigame.h"

#define get_square_number(column,row) ((row - '0' - 1) * 8 + (column - 'a'))


move generate_random(board *the_board){
    move *all_moves = get_all_moves(the_board);
    int len = 0;
    while(all_moves[len] != END)
        len++;
    return all_moves[rand() % len];
}

void scanner(char * move, int src_dst)
{
    char row;
    char column;
    char trash;
    if(src_dst)
        printf("enter src: ");
    else
        printf("enter dst: ");
    while (scanf(" %c %c%c", &column, &row, &trash) == 3 &&
           trash != '\r' && trash != '\n')
    {
        char buffer[4096];
        if (scanf("%4095[^\n]", buffer) == EOF)
            break;
        printf("too long\n");
        if(src_dst)
            printf("enter src: ");
        else
            printf("enter dst: ");
    }
    if(column < 'a' || column > 'h' || row < '1' || row > '8'){
        printf("invalid square\n");
        scanner(move, src_dst);
    }
    else{
        move[0] = column;
        move[1] = row;
    }
}

int white_move(board *the_board){
    int i = 0, row, promotion = 4;
    char temp[3];
    move *all_moves;
    char column, src_square, dst_square;
    while(1){
        scanner(temp, 1);
        src_square = get_square_number(temp[0], temp[1]);
        if(check_src(the_board, src_square, WHITE))
        {
            scanner(temp, 0);
            dst_square = get_square_number(temp[0], temp[1]);
            all_moves = get_all_moves(the_board);
            i = 0;
            while(all_moves[i] != END)
            {
                if(src_square == get_src_square(all_moves[i]) && dst_square == get_dst_square(all_moves[i]))
                {
                    if(get_piece_in_square(the_board, src_square) == white_pawn && get_row(src_square) == 6){
                        while(promotion > 3){
                            system("clear");
                            printf("promot to? (0=Q,1=R,2=B,3=N): ");
                            scanf("%d", &promotion);
                        }
                        commit_a_move_for_white(the_board, create_a_move(src_square, dst_square, promotion, 0, 0));
                        free(all_moves);
                        return 0;
                    }
                    commit_a_move_for_white(the_board, all_moves[i]);
                    free(all_moves);
                    return 0;
                }
                i++;    
            }
            free(all_moves);
        }
        printf("invalid move\n");
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
        system("clear");
        print_board(the_board);
        if(get_all_moves(the_board)[0] == END){
            if(isAttacked_by_white(the_board, find_king_square(the_board, BLACK))){
                printf("CHECKMATE 1-0\n");
                return 0;
            }
            printf("STALMATE 0.5-0.5\n");
            return 0;
        }
        commit_a_move_for_black(the_board ,get_best_move_black(the_board,4,3));
        system("clear");
    }
    return 0;
}

int check_src(board *the_board, char src, char the_move){
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
    START_BOARD.whos_turn=WHITE;

    int i;
    for(i = 0;i<32;i++)
    {
        START_BOARD.squares[i] = initial_board[i];
    }
    print_board(&START_BOARD);
    char move[3];
    system("clear");
    game(&START_BOARD);
    return 0;
}