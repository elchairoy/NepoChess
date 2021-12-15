#include "../include/possible_moves.h"
#include <syscall.h>

/*4 func to cal if peice is getting off board in hes move*/
char pass_left(char src){
    if(get_column(src) == 0)
        return 1;
    return 0;
}


char pass_right(char src){
    if(get_column(src) == NUMBER_OF_COLUMNS - 1)
        return 1;
    return 0;
}


char pass_down(char src){
    if(get_row(src) == 0)
        return 1;
    return 0;
}


char pass_up(char src){
    if(get_row(src) == NUMBER_OF_ROWS - 1)
        return 1;
    return 0;
}

/*check if peice will get on a square that an ally is on which means he can't*/
char colid_with_ally(char dst, board *the_board, char color)
{
    char dst_piece = get_piece_in_square(the_board, dst);
    if(color)
    {
        if(dst_piece <= NUM_OF_WHITE_PIECES && dst_piece != 0)
            return 1;
        return 0;
    }
    if(dst_piece > NUM_OF_WHITE_PIECES)
        return 1;
    return 0;
}

/*check if peice is on a square that an enemy is on which means he can't continue*/
char colid_with_enemy(char src, board *the_board, char color){
    char src_piece = get_piece_in_square(the_board, src);
    if(color)
    {
        if(src_piece > NUM_OF_WHITE_PIECES)
            return 1;
        return 0;
    }
    if(src_piece <= NUM_OF_WHITE_PIECES && src_piece != 0)
        return 1;
    return 0;
}

/*3 func to check if the pawn by his color can move and if so to where*/
char pawn_straight(char src, board *the_board, char color){
    if(color){
        if(get_piece_in_square(the_board, src + UP) == 0)
            return 1;
        return 0;
    }
    if(get_piece_in_square(the_board, src + DOWN) == 0)
            return 1;
        return 0;
}


char pawn_eat_left(char src, board *the_board, char color){
    if(!pass_left(src)){
        if(color)
            return colid_with_enemy(src + UP_LEFT, the_board, color);
        return colid_with_enemy(src + DOWN_LEFT, the_board, color);
    }
    return 0;
}


char pawn_eat_right(char src, board *the_board, char color){
    if(!pass_right(src)){
        if(color)
            return colid_with_enemy(src + UP_RIGHT, the_board, color);
        return colid_with_enemy(src + DOWN_RIGHT, the_board, color);
    }
    return 0;
}

/*8 func to return if the peice can move to any of his 8 sides (if the peice itself can of course)*/
char move_up(char src, board *the_board, char color){
    if(colid_with_enemy(src, the_board, color) || pass_up(src))
        return 0;
    if(colid_with_ally(src + UP, the_board, color))
        return 0;
    return 1;
}


char move_down(char src, board *the_board, char color){
    if(colid_with_enemy(src, the_board, color) || pass_down(src))
        return 0;
    if(colid_with_ally(src + DOWN, the_board, color))
        return 0;
    return 1;
}


char move_left(char src, board *the_board, char color){
    if(colid_with_enemy(src, the_board, color) || pass_left(src))
        return 0;
    if(colid_with_ally(src + LEFT, the_board, color))
        return 0;
    return 1;
}


char move_right(char src, board *the_board, char color){
    if(colid_with_enemy(src, the_board, color) || pass_right(src))
        return 0;
    if(colid_with_ally(src + RIGHT, the_board, color))
        return 0;
    return 1;
}


char move_up_left(char src, board *the_board, char color){
    if(colid_with_enemy(src, the_board, color) || pass_up(src) || pass_left(src))
        return 0;
    if(colid_with_ally(src + UP_LEFT, the_board, color))
        return 0;
    return 1;
}


char move_up_right(char src, board *the_board, char color){
    if(colid_with_enemy(src, the_board, color) || pass_up(src) || pass_right(src))
        return 0;
    if(colid_with_ally(src + UP_RIGHT, the_board, color))
        return 0;
    return 1;
}


char move_down_left(char src, board *the_board, char color){
    if(colid_with_enemy(src, the_board, color) || pass_down(src) || pass_left(src))
        return 0;
    if(colid_with_ally(src + DOWN_LEFT, the_board, color))
        return 0;
    return 1;
}


char move_down_right(char src, board *the_board, char color){
    if(colid_with_enemy(src, the_board, color) || pass_down(src) || pass_right(src))
        return 0;
    if(colid_with_ally(src + DOWN_RIGHT, the_board, color))
        return 0;
    return 1;
}

/*func to return for the rook and partly for the queen their move list in straight lines - left right up and down*/
void move_in_straight_lines(char square, board *the_board, char color, move *moves){
    int i = 0;
    int move_num = 0;
    move temp;
    /*rook up*/
    while(move_up(square + i*UP, the_board, color)){
        temp = create_a_move(square, square + (i+1)*UP, 0, 0, 0);
        i++;
        if(is_move_valid(*the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    /*rook down*/
    i = 0;
    while(move_down(square + i*DOWN, the_board, color)){
        temp = create_a_move(square, square + (i+1)*DOWN, 0, 0, 0);
        i++;
        if(is_move_valid(*the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    /*rook left*/
    i = 0;
    while(move_left(square + i*LEFT, the_board, color)){
        temp = create_a_move(square, square + (i+1)*LEFT, 0, 0, 0);
        i++;
        if(is_move_valid(*the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    /*rook right*/
    i = 0;
    while(move_right(square + i*RIGHT, the_board, color)){
        temp = create_a_move(square, square + (i+1)*RIGHT, 0, 0, 0);
        i++;
        if(is_move_valid(*the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    moves[move_num] = END;
}

/*this one returns the list of moves in diagonal lines - up_right up_left etc.*/
void move_in_diagonal_lines(char square, board *the_board, char color, move *moves){
    int i = 0;
    int move_num = 0;
    move temp;
    /*bishop up left*/
    while(move_up_left(square + i*UP_LEFT, the_board, color)){
        temp = create_a_move(square, square + (i+1)*UP_LEFT, 0, 0, 0);
        i++;
        if(is_move_valid(*the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    /*bishop up right*/
    i = 0;
    while(move_up_right(square + i*UP_RIGHT, the_board, color)){
        temp = create_a_move(square, square + (i+1)*UP_RIGHT, 0, 0, 0);
        i++;
        if(is_move_valid(*the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    /*bishop down right*/
    i = 0;
    while(move_down_right(square + i*DOWN_RIGHT, the_board, color)){
        temp = create_a_move(square, square + (i+1)*DOWN_RIGHT, 0, 0, 0);
        i++;
        if(is_move_valid(*the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    /*bishop down left*/
    i = 0;
    while(move_down_left(square + i*DOWN_LEFT, the_board, color)){
        temp = create_a_move(square, square + (i+1)*DOWN_LEFT, 0, 0, 0);
        i++;
        if(is_move_valid(*the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    moves[move_num] = END;
}

/*returns the rook moves list*/
void rook(char square, board *the_board, char color, move *moves){
    move_in_straight_lines(square, the_board, color, moves);
}

/*returns the bishop moves list*/
void bishop(char square, board *the_board, char color, move *moves){
    move_in_diagonal_lines(square, the_board, color, moves);
}

/*creats 2 lists 1 for striaght lins and one for diagonal and conects them to one which is the final*/
void queen(char square, board *the_board, char color, move *moves){
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
void king(char square, board *the_board, char color, move *moves){
    int move_num = 0;
    move temp;
    if(move_up(square, the_board, color)){
        temp = create_a_move(square, square+UP, 0, 0, 0);
        if(is_move_valid(*the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    if(move_down(square, the_board, color)){
        temp = create_a_move(square, square+DOWN, 0, 0, 0);
        if(is_move_valid(*the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    if(move_left(square, the_board, color)){
        temp = create_a_move(square, square+LEFT, 0, 0, 0);
        if(is_move_valid(*the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    if(move_right(square, the_board, color)){
        temp = create_a_move(square, square+RIGHT, 0, 0, 0);
        if(is_move_valid(*the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    if(move_up_right(square, the_board, color)){
        temp = create_a_move(square, square+UP_RIGHT, 0, 0, 0);
        if(is_move_valid(*the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    if(move_up_left(square, the_board, color)){
        temp = create_a_move(square, square+UP_LEFT, 0, 0, 0);
        if(is_move_valid(*the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    if(move_down_right(square, the_board, color)){
        temp = create_a_move(square, square+DOWN_RIGHT, 0, 0, 0);
        if(is_move_valid(*the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    if(move_down_left(square, the_board, color)){
        temp = create_a_move(square, square+DOWN_LEFT, 0, 0, 0);
        if(is_move_valid(*the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    moves[move_num] = END;
}

/*checks every possible move for the knight out of 8*/
void knight(char square, board *the_board, char color, move *moves){
    int move_num = 0;
    move temp;
    /*knight up up right*/
    if(get_column(square) < 7 && get_row(square) < 6){
        if(!colid_with_ally(square+KNIGHT_UP_UP_RIGHT, the_board, color)){
            temp = create_a_move(square, square+KNIGHT_UP_UP_RIGHT, 0, 0, 0);
            if(is_move_valid(*the_board, temp, color)){
                moves[move_num] = temp;
                move_num ++;
            }
        }
    }
    /*knight up up left*/
    if(get_column(square) > 0 && get_row(square) < 6){
        if(!colid_with_ally(square+KNIGHT_UP_UP_LEFT, the_board, color)){
            temp = create_a_move(square, square+KNIGHT_UP_UP_LEFT, 0, 0, 0);
            if(is_move_valid(*the_board, temp, color)){
                moves[move_num] = temp;
                move_num ++;
            }
        }
    }
    /*knight up right right*/
    if(get_column(square) < 6 && get_row(square) < 7){
        if(!colid_with_ally(square+KNIGHT_UP_RIGHT_RIGHT, the_board, color)){
            temp = create_a_move(square, square+KNIGHT_UP_RIGHT_RIGHT, 0, 0, 0);
            if(is_move_valid(*the_board, temp, color)){
                moves[move_num] = temp;
                move_num ++;
            }
        }
    }
    /*knight up left left*/
    if(get_column(square) > 1 && get_row(square) < 7){
        if(!colid_with_ally(square+KNIGHT_UP_LEFT_LEFT, the_board, color)){
            temp = create_a_move(square, square+KNIGHT_UP_LEFT_LEFT, 0, 0, 0);
            if(is_move_valid(*the_board, temp, color)){
                moves[move_num] = temp;
                move_num ++;
            }
        }
    }
    /*knight down down right*/
    if(get_column(square) < 7 && get_row(square) > 1){
        if(!colid_with_ally(square+KNIGHT_DOWN_DOWN_RIGHT, the_board, color)){
            temp = create_a_move(square, square+KNIGHT_DOWN_DOWN_RIGHT, 0, 0, 0);
            if(is_move_valid(*the_board, temp, color)){
                moves[move_num] = temp;
                move_num ++;
            }
        }
    }
    /*knight down down left*/
    if(get_column(square) > 0 && get_row(square) > 1){
        if(!colid_with_ally(square+KNIGHT_DOWN_DOWN_LEFT, the_board, color)){
            temp = create_a_move(square, square+KNIGHT_DOWN_DOWN_LEFT, 0, 0, 0);
            if(is_move_valid(*the_board, temp, color)){
                moves[move_num] = temp;
                move_num ++;
            }
        }
    }
    /*knight down right right*/
    if(get_column(square) < 6 && get_row(square) > 0){
        if(!colid_with_ally(square+KNIGHT_DOWN_RIGHT_RIGHT, the_board, color)){
            temp = create_a_move(square, square+KNIGHT_DOWN_RIGHT_RIGHT, 0, 0, 0);
            if(is_move_valid(*the_board, temp, color)){
                moves[move_num] = temp;
                move_num ++;
            }
        }
    }
    /*knight down left left*/
    if(get_column(square) > 1 && get_row(square) > 0){
        if(!colid_with_ally(square+KNIGHT_DOWN_LEFT_LEFT, the_board, color)){
            temp = create_a_move(square, square+KNIGHT_DOWN_LEFT_LEFT, 0, 0, 0);
            if(is_move_valid(*the_board, temp, color)){
                moves[move_num] = temp;
                move_num ++;
            }
        }
    }
    moves[move_num] = END;
}

/*checks every special move the pawn can do exept for the usual on which also gets checked but its minor, anyway there is 2 func
because the pawn for each color moves only in one diriction and its the exact oppised of the other*/
void whitepawn(char square, board *the_board, move *moves){
    int move_num = 0;
    int crown;
    int x = 0;
    move temp;

    if(get_row(square) == 6)
        x = 3;

    for(crown = 0; crown <= x; crown++){
        if(pawn_straight(square, the_board, WHITE)){
            if(get_row(square) == 1){
                if(pawn_straight(square+UP, the_board, WHITE)){
                    temp = create_a_move(square, square+(UP*2), 0, 0, 0);
                    if(is_move_valid(*the_board, temp, WHITE)){
                        moves[move_num] = temp;
                        move_num ++;
                    }
                }
            }
            temp = create_a_move(square, square+UP, crown, 0, 0);
            if(is_move_valid(*the_board, temp, WHITE)){
                moves[move_num] = temp;
                move_num ++;
            }
        }
        if(pawn_eat_right(square, the_board, WHITE)){
            temp = create_a_move(square, square+UP_RIGHT, crown, 0, 0);
            if(is_move_valid(*the_board, temp, WHITE)){
                moves[move_num] = temp;
                move_num ++;
            }
        }  
        if(pawn_eat_left(square, the_board, WHITE)){
            temp = create_a_move(square, square+UP_LEFT, crown, 0, 0);
            if(is_move_valid(*the_board, temp, WHITE)){
                moves[move_num] = temp;
                move_num ++;
            }
        }
    }
    moves[move_num] = END;
}


void blackpawn(char square, board *the_board, move *moves){
    int move_num = 0;
    move temp;
    char crown;
    int x = 0;
    if(get_row(square) == 1)
        x = 3;
    for(crown = 0; crown <= x; crown++){
        if(pawn_straight(square, the_board, BLACK)){
            if(get_row(square) == 6){
                if(pawn_straight(square+DOWN, the_board, BLACK)){
                    temp = create_a_move(square, square+(DOWN*2), 0, 0, 0);
                    if(is_move_valid(*the_board, temp, BLACK)){
                        moves[move_num] = temp;
                        move_num ++;
                    }
                }
            }
            temp = create_a_move(square, square+DOWN, crown, 0, 0);
            if(is_move_valid(*the_board, temp, BLACK)){
                moves[move_num] = temp;
                move_num ++;
            }
        }
        if(pawn_eat_right(square, the_board, BLACK)){
            temp = create_a_move(square, square+DOWN_RIGHT, crown, 0, 0);
            if(is_move_valid(*the_board, temp, BLACK)){
                moves[move_num] = temp;
                move_num ++;
            }
        }
        if(pawn_eat_left(square, the_board, BLACK)){
            temp = create_a_move(square, square+DOWN_LEFT, crown, 0, 0);
            if(is_move_valid(*the_board, temp, BLACK)){
                moves[move_num] = temp;
                move_num ++;
            }
        }
    }
    moves[move_num] = END;
}

/* This function checks if a square is attacked. */


char is_move_valid(board the_board, move the_move, char color){
    if(color){
         commit_a_move_for_white(&the_board, the_move);
         if(isAttacked_by_black(&the_board, find_king_square(&the_board, WHITE)))
            return 0;
        return 1;
    } 
    commit_a_move_for_black(&the_board, the_move);
    if(isAttacked_by_white(&the_board, find_king_square(&the_board, BLACK)))
        return 0;
    return 1;  
}


void en_passant_and_castle(board *the_board, move *moves, char color){
    int move_num = 0;
    char square = 0;
    move temp;
    if(the_board->pawn_en_passant_right){
        square = the_board->pawn_en_passant_right;
        if(color_of_piece(square, the_board) == WHITE && color == WHITE){
            temp = create_a_move(square, square + UP_RIGHT, 0, 0, 0);
                if(is_move_valid(*the_board, temp, WHITE)){
                    moves[move_num] = temp;
                    move_num ++;
                }
        }
        if(color_of_piece(square, the_board) == BLACK && color == BLACK){
            temp = create_a_move(square, square + DOWN_RIGHT, 0, 0, 0);
            if(is_move_valid(*the_board, temp, BLACK)){
                    moves[move_num] = temp;
                    move_num ++;
                }
        }
    }
    if(the_board->pawn_en_passant_left){
        square = the_board->pawn_en_passant_left;
        if(color_of_piece(square, the_board) == WHITE && color == WHITE){
            temp = create_a_move(square, square + UP_LEFT, 0, 0, 0);
            if(is_move_valid(*the_board, temp, WHITE)){
                    moves[move_num] = temp;
                    move_num ++;
                }
        }
        if(color_of_piece(square, the_board) == BLACK && color == BLACK){
            temp = create_a_move(square, square + DOWN_LEFT, 0, 0, 0);
            if(is_move_valid(*the_board, temp, BLACK)){
                    moves[move_num] = temp;
                    move_num ++;
                }
        }
    }
    if(color){
        if(check_white_long_castle(the_board)){
            moves[move_num] = create_a_move(DEAFULT_WHITE_KING_SQUARE, DEAFULT_WHITE_KING_SQUARE-2, 0, 1, 0);
            move_num ++;
        }
        if(check_white_short_castle(the_board)){
            moves[move_num] = create_a_move(DEAFULT_WHITE_KING_SQUARE, DEAFULT_WHITE_KING_SQUARE+2, 0, 0, 1);
            move_num ++;
        }
    }
    if(!color){
        if(check_black_long_castle(the_board)){
            moves[move_num] = create_a_move(DEAFULT_BLACK_KING_SQUARE, DEAFULT_BLACK_KING_SQUARE-2, 0, 1, 0);
            move_num ++;
        }
        if(check_black_short_castle(the_board)){
            moves[move_num] = create_a_move(DEAFULT_BLACK_KING_SQUARE, DEAFULT_BLACK_KING_SQUARE+2, 0, 0, 1);
            move_num ++;
        }
    }
    moves[move_num] = END;
}





char color_of_piece(char square, board *the_board){
    char peice = get_piece_in_square(the_board, square);
    if(peice > NUM_OF_WHITE_PIECES)
        return BLACK;
    return WHITE;
}

/*calls the right func for the peice it was asked to check*/
char moves_of_piece(char square, board *the_board, move * moves){
    char peice = get_piece_in_square(the_board, square);
    switch (peice)
    {
    case white_knight:
        knight(square, the_board, WHITE, moves);
        break;
    
    case black_knight:
        knight(square, the_board, BLACK, moves);
        break;

    case white_rook:
        rook(square, the_board, WHITE, moves);
        break;
    
    case black_rook:
        rook(square, the_board, BLACK, moves);
        break;

    case white_queen:
        queen(square, the_board, WHITE, moves);
        break;

    case black_queen:
        queen(square, the_board, BLACK, moves);
        break;
    
    case white_king:
        king(square, the_board, WHITE, moves);
        break;
    
    case black_king:
        king(square, the_board, BLACK, moves);
        break;

    case white_bishop:
        bishop(square, the_board, WHITE, moves);
        break;

    case black_bishop:
        bishop(square, the_board, BLACK, moves);
        break;
    
    case white_pawn:
        whitepawn(square, the_board, moves);
        break;
    
    case black_pawn:
        blackpawn(square, the_board, moves);
        break;

    default:
        return 0;
    }
    return 1;
}

/*main function*/
void connect_arrays(move * array, move * array1){
    int len = 0, i = 0;
    while(array[len] != END)
        len++;
    while(array1[i] != END){
        array[len] = array1[i];
        len ++;
        i ++;
    }
    array[len] = END;
}


move* get_all_moves(board *the_board){
    char color = the_board->whose_turn;
    int i = 0, x = 0, len = 1;
    move *all_moves;
    move moves[28];
    for(i = 0; i<NUMBER_OF_SQUARES; i++){
        if(color_of_piece(i, the_board) == color && get_piece_in_square(the_board, i) != empty){
            moves_of_piece(i, the_board, moves);
            while(moves[x] != END)
                x++;
            len += x;
            x = 0;
        }
    }
    en_passant_and_castle(the_board, moves, color);
    while(moves[x] != END)
        x++;
    len += x;
    all_moves = malloc(len * sizeof(move));
    if (all_moves == 0) {
        printf("no memory");
        exit(1);
    }
    all_moves[0] = END;
    for(i = 0; i<NUMBER_OF_SQUARES; i++){
        if(color_of_piece(i, the_board) == color && get_piece_in_square(the_board, i) != empty){
            moves_of_piece(i, the_board, moves);
            connect_arrays(all_moves, moves);
        }
    }
    en_passant_and_castle(the_board, moves, color);
    connect_arrays(all_moves, moves);
    return all_moves;
}