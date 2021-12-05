#include "possible_moves.h"

/*4 func to cal if peice is getting off board in hes move*/
char pass_left(char src){
    if(get_column(src) == 0)
        return 1;
    return 0;
}


char pass_right(char src){
    if(get_column(src) == 7)
        return 1;
    return 0;
}


char pass_down(char src){
    if(get_row(src) == 0)
        return 1;
    return 0;
}


char pass_up(char src){
    if(get_row(src) == 7)
        return 1;
    return 0;
}

/*check if peice will get on a square that an ally is on which means he can't*/
char colid_with_ally(char dst, board the_board, char color)
{
    char dst_piece = get_piece_in_square(&the_board, dst);
    if(color)
    {
        if(dst_piece <= 6 && dst_piece != 0)
            return 1;
        return 0;
    }
    if(dst_piece > 6)
        return 1;
    return 0;
}

/*check if peice is on a square that an enemy is on which means he can't continue*/
char colid_with_enemy(char src, board the_board, char color){
    char src_piece = get_piece_in_square(&the_board, src);
    if(color)
    {
        if(src_piece > 6)
            return 1;
        return 0;
    }
    if(src_piece <= 6 && src_piece != 0)
        return 1;
    return 0;
}

/*3 func to check if the pawn by his color can move and if so to where*/
char pawn_straight(char src, board the_board, char color){
    if(color){
        if(get_piece_in_square(&the_board, src + UP) == 0)
            return 1;
        return 0;
    }
    if(get_piece_in_square(&the_board, src + DOWN) == 0)
            return 1;
        return 0;
}


char pawn_eat_left(char src, board the_board, char color){
    if(!pass_left(src)){
        if(color)
            return colid_with_enemy(src + UP_LEFT, the_board, color);
        return colid_with_enemy(src + DOWN_LEFT, the_board, color);
    }
    return 0;
}


char pawn_eat_right(char src, board the_board, char color){
    if(!pass_right(src)){
        if(color)
            return colid_with_enemy(src + UP_RIGHT, the_board, color);
        return colid_with_enemy(src + DOWN_RIGHT, the_board, color);
    }
    return 0;
}

/*8 func to return if the peice can move to any of his 8 sides (if the peice itself can of course)*/
char move_up(char src, board the_board, char color){
    if(colid_with_enemy(src, the_board, color) || pass_up(src))
        return 0;
    if(colid_with_ally(src + UP, the_board, color))
        return 0;
    return 1;
}


char move_down(char src, board the_board, char color){
    if(colid_with_enemy(src, the_board, color) || pass_down(src))
        return 0;
    if(colid_with_ally(src + DOWN, the_board, color))
        return 0;
    return 1;
}


char move_left(char src, board the_board, char color){
    if(colid_with_enemy(src, the_board, color) || pass_left(src))
        return 0;
    if(colid_with_ally(src + LEFT, the_board, color))
        return 0;
    return 1;
}


char move_right(char src, board the_board, char color){
    if(colid_with_enemy(src, the_board, color) || pass_right(src))
        return 0;
    if(colid_with_ally(src + RIGHT, the_board, color))
        return 0;
    return 1;
}


char move_up_left(char src, board the_board, char color){
    if(colid_with_enemy(src, the_board, color) || pass_up(src) || pass_left(src))
        return 0;
    if(colid_with_ally(src + UP_LEFT, the_board, color))
        return 0;
    return 1;
}


char move_up_right(char src, board the_board, char color){
    if(colid_with_enemy(src, the_board, color) || pass_up(src) || pass_right(src))
        return 0;
    if(colid_with_ally(src + UP_RIGHT, the_board, color))
        return 0;
    return 1;
}


char move_down_left(char src, board the_board, char color){
    if(colid_with_enemy(src, the_board, color) || pass_down(src) || pass_left(src))
        return 0;
    if(colid_with_ally(src + DOWN_LEFT, the_board, color))
        return 0;
    return 1;
}


char move_down_right(char src, board the_board, char color){
    if(colid_with_enemy(src, the_board, color) || pass_down(src) || pass_right(src))
        return 0;
    if(colid_with_ally(src + DOWN_RIGHT, the_board, color))
        return 0;
    return 1;
}

/*func to return for the rook and partly for the queen their move list in straight lines - left right up and down*/
void move_in_straight_lines(char square, board the_board, char color, move *moves){
    int i, move_num = 0;
    /*rook up*/
    for(i = 0; i < MAX_MOVES;i++){
        if(move_up(square + i*UP, the_board, color)){
            moves[move_num] = create_a_move(square, square + (i+1)*UP, 0, 0, 0);
            move_num ++;
        }
        else break;
    }
    /*rook down*/
    for(i = 0; i < MAX_MOVES;i++){
        if(move_down(square + i*DOWN, the_board, color)){
            moves[move_num] = create_a_move(square, square + (i+1)*DOWN, 0, 0, 0);
            move_num ++;
        }
        else break;
    }
    /*rook left*/
    for(i = 0; i < MAX_MOVES;i++){
        if(move_left(square + i*LEFT, the_board, color)){
            moves[move_num] = create_a_move(square, square + (i+1)*LEFT, 0, 0, 0);
            move_num ++;
        }
        else break;
    }
    /*rook right*/
    for(i = 0; i < MAX_MOVES;i++){
        if(move_right(square + i*RIGHT, the_board, color)){
            moves[move_num] = create_a_move(square, square + (i+1)*RIGHT, 0, 0, 0);
            move_num ++;
        }
        else break;
    }
    moves[move_num] = END;
}

/*this one returns the list of moves in diagonal lines - up_right up_left etc.*/
void move_in_diagonal_lines(char square, board the_board, char color, move *moves){
    int i, move_num = 0;
    /*bishop up left*/
    for(i = 0; i < MAX_MOVES;i++){
        if(move_up_left(square + i*UP_LEFT, the_board, color)){
            moves[move_num] = create_a_move(square, square + (i+1)*UP_LEFT, 0, 0, 0);
            move_num ++;
        }
        else break;
    }
    /*bishop up right*/
    for(i = 0; i < MAX_MOVES;i++){
        if(move_up_right(square + i*UP_RIGHT, the_board, color)){
            moves[move_num] = create_a_move(square, square + (i+1)*UP_RIGHT, 0, 0, 0);
            move_num ++;
        }
        else break;
    }
    /*bishop down right*/
    for(i = 0; i < MAX_MOVES;i++){
        if(move_down_right(square + i*DOWN_RIGHT, the_board, color)){
            moves[move_num] = create_a_move(square, square + (i+1)*DOWN_RIGHT, 0, 0, 0);
            move_num ++;
        }
        else break;
    }
    /*bishop down left*/
    for(i = 0; i < MAX_MOVES;i++){
        if(move_down_left(square + i*DOWN_LEFT, the_board, color)){
            moves[move_num] = create_a_move(square, square + (i+1)*DOWN_LEFT, 0, 0, 0);
            move_num ++;
        }
        else break;
    }
    moves[move_num] = END;
}

/*returns the rook moves list*/
void rook(char square, board the_board, char color, move *moves){
    move_in_straight_lines(square, the_board, color, moves);
}

/*returns the bishop moves list*/
void bishop(char square, board the_board, char color, move *moves){
    move_in_diagonal_lines(square, the_board, color, moves);
}

/*creats 2 lists 1 for striaght lins and one for diagonal and conects them to one which is the final*/
void queen(char square, board the_board, char color, move *moves){
    move array1 [ROOK_MAX_MOVES + 1];
    move array2 [BISHOP_MAX_MOVES + 1];
    int i = 0;
    int move_num = 0;
    move_in_straight_lines(square, the_board, color, array1);
    move_in_diagonal_lines(square, the_board, color, array2);
    while(array1[i] != END){
        moves[move_num] = array1[i];
        move_num ++;
        i ++;
    }
    i = 0;
    while(array2[i] != END){
        moves[move_num] = array2[i];
        move_num ++;
        i ++;
    }
    moves[move_num] = END;
}

/*checks every possible move of the king out of 8*/
void king(char square, board the_board, char color, move *moves){
    int move_num = 0;
    if(move_up(square, the_board, color)){
        moves[move_num] = create_a_move(square, square+UP, 0, 0, 0);
        move_num ++;
    }
    if(move_down(square, the_board, color)){
        moves[move_num] = create_a_move(square, square+DOWN, 0, 0, 0);
        move_num ++;
    }
    if(move_left(square, the_board, color)){
        moves[move_num] = create_a_move(square, square+LEFT, 0, 0, 0);
        move_num ++;
    }
    if(move_right(square, the_board, color)){
        moves[move_num] = create_a_move(square, square+RIGHT, 0, 0, 0);
        move_num ++;
    }
    if(move_up_right(square, the_board, color)){
        moves[move_num] = create_a_move(square, square+UP_RIGHT, 0, 0, 0);
        move_num ++;
    }
    if(move_up_left(square, the_board, color)){
        moves[move_num] = create_a_move(square, square+UP_LEFT, 0, 0, 0);
        move_num ++;
    }
    if(move_down_right(square, the_board, color)){
        moves[move_num] = create_a_move(square, square+DOWN_RIGHT, 0, 0, 0);
        move_num ++;
    }
    if(move_down_left(square, the_board, color)){
        moves[move_num] = create_a_move(square, square+DOWN_LEFT, 0, 0, 0);
        move_num ++;
    }
    moves[move_num] = END;
}

/*checks every possible move for the knight out of 8*/
void knight(char square, board the_board, char color, move *moves){
    int move_num = 0;
    /*knight up up right*/
    if(get_column(square) < 7 && get_row(square) < 6){
        if(!colid_with_ally(square+N_UP_UP_RIGHT, the_board, color)){
            moves[move_num] = create_a_move(square, square+N_UP_UP_RIGHT, 0, 0, 0);
            move_num ++;
        }
    }
    /*knight up up left*/
    if(get_column(square) > 0 && get_row(square) < 6){
        if(!colid_with_ally(square+N_UP_UP_LEFT, the_board, color)){
            moves[move_num] = create_a_move(square, square+N_UP_UP_LEFT, 0, 0, 0);
            move_num ++;
        }
    }
    /*knight up right right*/
    if(get_column(square) < 6 && get_row(square) < 7){
        if(!colid_with_ally(square+N_UP_RIGHT_RIGHT, the_board, color)){
            moves[move_num] = create_a_move(square, square+N_UP_RIGHT_RIGHT, 0, 0, 0);
            move_num ++;
        }
    }
    /*knight up left left*/
    if(get_column(square) > 1 && get_row(square) < 7){
        if(!colid_with_ally(square+N_UP_LEFT_LEFT, the_board, color)){
            moves[move_num] = create_a_move(square, square+N_UP_LEFT_LEFT, 0, 0, 0);
            move_num ++;
        }
    }
    /*knight down down right*/
    if(get_column(square) < 7 && get_row(square) > 1){
        if(!colid_with_ally(square+N_DOWN_DOWN_RIGHT, the_board, color)){
            moves[move_num] = create_a_move(square, square+N_DOWN_DOWN_RIGHT, 0, 0, 0);
            move_num ++;
        }
    }
    /*knight down down left*/
    if(get_column(square) > 0 && get_row(square) > 1){
        if(!colid_with_ally(square+N_DOWN_DOWN_LEFT, the_board, color)){
            moves[move_num] = create_a_move(square, square+N_DOWN_DOWN_LEFT, 0, 0, 0);
            move_num ++;
        }
    }
    /*knight down right right*/
    if(get_column(square) < 6 && get_row(square) > 0){
        if(!colid_with_ally(square+N_DOWN_RIGHT_RIGHT, the_board, color)){
            moves[move_num] = create_a_move(square, square+N_DOWN_RIGHT_RIGHT, 0, 0, 0);
            move_num ++;
        }
    }
    /*knight down left left*/
    if(get_column(square) > 1 && get_row(square) > 0){
        if(!colid_with_ally(square+N_DOWN_LEFT_LEFT, the_board, color)){
            moves[move_num] = create_a_move(square, square+N_DOWN_LEFT_LEFT, 0, 0, 0);
            move_num ++;
        }
    }
    moves[move_num] = END;
}

/*checks every special move the pawn can do exept for the usual on which also gets checked but its minor, anyway there is 2 func
because the pawn for each color moves only in one diriction and its the exact oppised of the other*/
void whitepawn(char square, board the_board, move *moves, char crown){
    int move_num = 0;
    if(get_row(square) != 7)
            crown = 0;
    if(pawn_straight(square, the_board, WHITE)){
        if(get_row(square) == 1){
            if(pawn_straight(square+UP, the_board, WHITE)){
                moves[move_num] = create_a_move(square, square+(UP*2), 0, 0, 0);
                move_num++;
            }
        }
        moves[move_num] = create_a_move(square, square+UP, crown, 0, 0);
        move_num++;
    }
    if(pawn_eat_right(square, the_board, WHITE)){
        moves[move_num] = create_a_move(square, square+UP_RIGHT, crown, 0, 0);
        move_num++;
    }
    if(pawn_eat_left(square, the_board, WHITE)){
        moves[move_num] = create_a_move(square, square+UP_LEFT, crown, 0, 0);
        move_num++;
    }
    moves[move_num] = END;
}


void blackpawn(char square, board the_board, move *moves, char crown){
    int move_num = 0;
    if(get_row(square) != 1)
            crown = 0;
    if(pawn_straight(square, the_board, BLACK)){
        if(get_row(square) == 7){
            if(pawn_straight(square+DOWN, the_board, BLACK)){
                moves[move_num] = create_a_move(square, square+(DOWN*2), 0, 0, 0);
                move_num++;
            }
        }
        moves[move_num] = create_a_move(square, square+DOWN, crown, 0, 0);
        move_num++;
    }
    if(pawn_eat_right(square, the_board, BLACK)){
        moves[move_num] = create_a_move(square, square+DOWN_RIGHT, crown, 0, 0);
        move_num++;
    }
    if(pawn_eat_left(square, the_board, BLACK)){
        moves[move_num] = create_a_move(square, square+DOWN_LEFT, crown, 0, 0);
        move_num++;
    }
    moves[move_num] = END;
}

/*returns the name of the peice in a letter*/
char return_piece(char square, board the_board){
    short int piece = get_piece_in_square(&the_board, square);
    return PIECES[piece];
}

/*calls the right func for the peice it was asked to check*/
char moves_of_piece(char square, board the_board, move * moves, char crown){
    char peice = return_piece(square, the_board);
    printf("peice: %c\n", peice);
    switch (peice)
    {
    case 'N':
        knight(square, the_board, WHITE, moves);
        break;
    
    case 'n':
        knight(square, the_board, BLACK, moves);
        break;

    case 'R':
        rook(square, the_board, WHITE, moves);
        break;
    
    case 'r':
        rook(square, the_board, BLACK, moves);
        break;

    case 'Q':
        queen(square, the_board, WHITE, moves);
        break;

    case 'q':
        queen(square, the_board, BLACK, moves);
        break;
    
    case 'K':
        king(square, the_board, WHITE, moves);
        break;
    
    case 'k':
        king(square, the_board, BLACK, moves);
        break;

    case 'B':
        bishop(square, the_board, WHITE, moves);
        break;

    case 'b':
        bishop(square, the_board, BLACK, moves);
        break;
    
    case 'P':
        whitepawn(square, the_board, moves, crown);
        break;
    
    case 'p':
        blackpawn(square, the_board, moves, crown);
        break;

    default:
        return 0;
    }
    return 1;
}

/*main function*/
int func(){
    board START_BOARD;
    move moves [28];
    char initial_board[32] = {white_rook << 4|white_knight,white_bishop << 4|white_queen,white_king<<4|
    white_bishop,white_knight<<4|white_rook,white_pawn << 4|white_pawn,white_pawn<<4|white_pawn,white_pawn<<4|
    white_pawn,white_pawn<<4|white_pawn,empty,empty<<4|white_pawn,empty,empty,empty,empty,empty,empty,empty,empty,white_queen<<4|empty,empty
    ,empty,empty,empty,empty,empty << 4|black_pawn,black_pawn<<4|black_pawn,black_pawn<<4|black_pawn,black_pawn<<4|
    black_pawn,black_rook << 4|black_knight,black_bishop << 4|black_queen,black_king<<4|black_bishop,black_knight<<4|black_rook};
    int i;
    char crown = 1;
    for(i = 0;i<32;i++)
    {
        START_BOARD.squares[i] = initial_board[i];
    }
    moves_of_piece(36, START_BOARD, moves, crown);
    i = 0;
    while(moves[i] != END){
        printf("from %d to %d\n", get_src_square(moves[i]), get_dst_square(moves[i]));
        i++;
    }
    return 0;
}