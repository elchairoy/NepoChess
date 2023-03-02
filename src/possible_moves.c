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

char pass_up_left(char src){
    if(pass_up(src) || pass_left(src))
        return 1;
    return 0;
}

char pass_up_right(char src){
    if(pass_up(src) || pass_right(src))
        return 1;
    return 0;
}

char pass_down_left(char src){
    if(pass_down(src) || pass_left(src))
        return 1;
    return 0;
}

char pass_down_right(char src){
    if(pass_down(src) || pass_right(src))
        return 1;
    return 0;
}

/*check if peice will get on a square that an ally is on which means he can't*/
char colid_with_allay(char square, board *the_board, char color)
{
    char piece = get_piece_in_square(the_board, square);
    if(color)
    {
        if (piece != 0 && piece <= NUM_OF_WHITE_PIECES)
            return 1;
        return 0;
    }
    if (piece > NUM_OF_WHITE_PIECES)
        return 1;
    return 0;
}

/*check if peice is on a square that an enemy is on which means he can't continue*/
char colid_with_enemy(char square, board *the_board, char color){
    char piece = get_piece_in_square(the_board, square);
    if(color)
    {
        if (piece > NUM_OF_WHITE_PIECES)
            return 1;
        return 0;
    }
    if (piece!=0 && piece <= NUM_OF_WHITE_PIECES)
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
    if(colid_with_allay(src + UP, the_board, color))
        return 0;
    return 1;
}


char move_down(char src, board *the_board, char color){
    if(colid_with_enemy(src, the_board, color) || pass_down(src))
        return 0;
    if(colid_with_allay(src + DOWN, the_board, color))
        return 0;
    return 1;
}


char move_left(char src, board *the_board, char color){
    if(colid_with_enemy(src, the_board, color) || pass_left(src))
        return 0;
    if(colid_with_allay(src + LEFT, the_board, color))
        return 0;
    return 1;
}


char move_right(char src, board *the_board, char color){
    if(colid_with_enemy(src, the_board, color) || pass_right(src))
        return 0;
    if(colid_with_allay(src + RIGHT, the_board, color))
        return 0;
    return 1;
}


char move_up_left(char src, board *the_board, char color){
    if(colid_with_enemy(src, the_board, color) || pass_up(src) || pass_left(src))
        return 0;
    if(colid_with_allay(src + UP_LEFT, the_board, color))
        return 0;
    return 1;
}


char move_up_right(char src, board *the_board, char color){
    if(colid_with_enemy(src, the_board, color) || pass_up(src) || pass_right(src))
        return 0;
    if(colid_with_allay(src + UP_RIGHT, the_board, color))
        return 0;
    return 1;
}


char move_down_left(char src, board *the_board, char color){
    if(colid_with_enemy(src, the_board, color) || pass_down(src) || pass_left(src))
        return 0;
    if(colid_with_allay(src + DOWN_LEFT, the_board, color))
        return 0;
    return 1;
}


char move_down_right(char src, board *the_board, char color){
    if(colid_with_enemy(src, the_board, color) || pass_down(src) || pass_right(src))
        return 0;
    if(colid_with_allay(src + DOWN_RIGHT, the_board, color))
        return 0;
    return 1;
}

/*func to return for the rook and partly for the queen their move list in straight lines - left right up and down*/
int move_in_straight_lines(char square, board *the_board, char color, move *moves, char is_pinned){
    int i = 0;
    int move_num = 0;
    move temp;
    /*rook up*/
    while(move_up(square + i*UP, the_board, color)){
        create_a_move(temp, square, square + (i+1)*UP, 0, 0, 0);
        i++;
        if(!is_pinned || is_move_valid(the_board, temp, color)){ /* If not pinned there is no need to check if valid. */
            moves[move_num] = temp;
            move_num ++;
        }
    }
    /*rook down*/
    i = 0;
    while(move_down(square + i*DOWN, the_board, color)){
        create_a_move(temp, square, square + (i+1)*DOWN, 0, 0, 0);
        i++;
        if(!is_pinned || is_move_valid(the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    /*rook left*/
    i = 0;
    while(move_left(square + i*LEFT, the_board, color)){
        create_a_move(temp, square, square + (i+1)*LEFT, 0, 0, 0);
        i++;
        if(!is_pinned || is_move_valid(the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    /*rook right*/
    i = 0;
    while(move_right(square + i*RIGHT, the_board, color)){
        create_a_move(temp, square, square + (i+1)*RIGHT, 0, 0, 0);
        i++;
        if(!is_pinned || is_move_valid(the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    moves[move_num] = END;
    return move_num;
}

/*this one returns the list of moves in diagonal lines - up_right up_left etc.*/
int move_in_diagonal_lines(char square, board *the_board, char color, move *moves, char is_pinned){
    int i = 0;
    int move_num = 0;
    move temp;
    /* up left*/
    while(move_up_left(square + i*UP_LEFT, the_board, color)){
        create_a_move(temp, square, square + (i+1)*UP_LEFT, 0, 0, 0);
        i++;
        if(!is_pinned || is_move_valid(the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    /* up right*/
    i = 0;
    while(move_up_right(square + i*UP_RIGHT, the_board, color)){
        create_a_move(temp, square, square + (i+1)*UP_RIGHT, 0, 0, 0);
        i++;
        if(!is_pinned || is_move_valid(the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    /* down right*/
    i = 0;
    while(move_down_right(square + i*DOWN_RIGHT, the_board, color)){
        create_a_move(temp, square, square + (i+1)*DOWN_RIGHT, 0, 0, 0);
        i++;
        if(!is_pinned || is_move_valid(the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    /* down left*/
    i = 0;
    while(move_down_left(square + i*DOWN_LEFT, the_board, color)){
        create_a_move(temp, square, square + (i+1)*DOWN_LEFT, 0, 0, 0);
        i++;
        if(!is_pinned || is_move_valid(the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    moves[move_num] = END;
    return move_num;
}

/* This function returns the destination squares in the needed directions of a square: */
int squares_in_directions(board *b, char square, char *dst_squares) {
    int i = 0;
    int squares_num = 0;
        /* MOVE IN DIAGONALS: */

    /* up left*/
    while(!pass_left(square + i*UP_LEFT) && !pass_up(square + i*UP_LEFT)){
        i++;
        if (get_piece_in_square(b, square + i*UP_LEFT)) { /* If it's not empty: */
            dst_squares[squares_num] = square + i*UP_LEFT;
            squares_num++;
            break;
        }
    }
    /* up right*/
    i = 0;
    while(!pass_right(square + i*UP_RIGHT) && !pass_up(square + i*UP_RIGHT)){
        i++;
        if (get_piece_in_square(b, square + i*UP_RIGHT)) { /* If it's not empty: */
            dst_squares[squares_num] = square + i*UP_RIGHT;
            squares_num++;
            break;
        }
    }
    /* down right*/
    i = 0;
    while(!pass_right(square + i*DOWN_RIGHT) && !pass_down(square + i*DOWN_RIGHT)){
        i++;
        if (get_piece_in_square(b, square + i*DOWN_RIGHT)) { /* If it's not empty: */
            dst_squares[squares_num] = square + i*DOWN_RIGHT;
            squares_num++;
            break;
        }
    }
    /* down left*/
    i = 0;
    while(!pass_down(square + i*DOWN_LEFT) && !pass_left(square + i*DOWN_LEFT)){
        i++;
        if (get_piece_in_square(b, square + i*DOWN_LEFT)) { /* If it's not empty: */
            dst_squares[squares_num] = square + i*DOWN_LEFT;
            squares_num++;
            break;
        }
    }

        /* MOVE IN STRAIGHT LINES: */

    /* up*/
    i = 0;
    while(!pass_up(square + i*UP)){
        i++;
        if (get_piece_in_square(b, square + i*UP)) { /* If it's not empty: */
            dst_squares[squares_num] = square + i*UP;
            squares_num++;
            break;
        }
    }
    /* right */
    i = 0;
    while(!pass_right(square + i*RIGHT)){
        i++;
        if (get_piece_in_square(b, square + i*RIGHT)) { /* If it's not empty: */
            dst_squares[squares_num] = square + i*RIGHT;
            squares_num++;
            break;
        }
    }
    /* down */
    i = 0;
    while(!pass_down(square + i*DOWN)){
        i++;
        if (get_piece_in_square(b, square + i*DOWN)) { /* If it's not empty: */
            dst_squares[squares_num] = square + i*DOWN;
            squares_num++;
            break;
        }
    }
    /* left*/
    i = 0;
    while(!pass_left(square + i*LEFT)){
        i++;
        if (get_piece_in_square(b, square + i*LEFT)) { /* If it's not empty: */
            dst_squares[squares_num] = square + i*LEFT;
            squares_num++;
            break;
        }
    }

        /* KNIGHT MOVES: */

    /* Knight up up right*/
    if(get_column(square) < 7 && get_row(square) < 6){
        if (get_piece_in_square(b, square + KNIGHT_UP_UP_RIGHT)) { /* If it's not empty: */
            dst_squares[squares_num] = square + KNIGHT_UP_UP_RIGHT;
            squares_num++;
        }
    }
    /* Knight up up left*/
    if(get_column(square) > 0 && get_row(square) < 6){
        if (get_piece_in_square(b, square + KNIGHT_UP_UP_LEFT)) { /* If it's not empty: */
            dst_squares[squares_num] = square + KNIGHT_UP_UP_LEFT;
            squares_num++;
        }
    }
    /* Knight up right right*/
    if(get_column(square) < 6 && get_row(square) < 7){
        if (get_piece_in_square(b, square + KNIGHT_UP_RIGHT_RIGHT)) { /* If it's not empty: */
            dst_squares[squares_num] = square + KNIGHT_UP_RIGHT_RIGHT;
            squares_num++;
        }
    }
    /* Knight up left left*/
    if(get_column(square) > 1 && get_row(square) < 7){
        if (get_piece_in_square(b, square + KNIGHT_UP_LEFT_LEFT)) { /* If it's not empty: */
            dst_squares[squares_num] = square + KNIGHT_UP_LEFT_LEFT;
            squares_num++;
        }
    }
    /* Knight down down right*/
    if(get_column(square) < 7 && get_row(square) > 1){
        if (get_piece_in_square(b, square + KNIGHT_DOWN_DOWN_RIGHT)) { /* If it's not empty: */
            dst_squares[squares_num] = square + KNIGHT_DOWN_DOWN_RIGHT;
            squares_num++;
        }
    }
    /* Knight down down left*/
    if(get_column(square) > 0 && get_row(square) > 1){
        if (get_piece_in_square(b, square + KNIGHT_DOWN_DOWN_LEFT)) { /* If it's not empty: */
            dst_squares[squares_num] = square + KNIGHT_DOWN_DOWN_LEFT;
            squares_num++;
        }
    }
    /* Knight down right right*/
    if(get_column(square) < 6 && get_row(square) > 0){
        if (get_piece_in_square(b, square + KNIGHT_DOWN_RIGHT_RIGHT)) { /* If it's not empty: */
            dst_squares[squares_num] = square + KNIGHT_DOWN_RIGHT_RIGHT;
            squares_num++;
        }
    }
    /* Knight down left left*/
    if(get_column(square) > 1 && get_row(square) > 0){
        if (get_piece_in_square(b, square + KNIGHT_DOWN_LEFT_LEFT)) { /* If it's not empty: */
            dst_squares[squares_num] = square + KNIGHT_DOWN_LEFT_LEFT;
            squares_num++;
        }
    }

    dst_squares[squares_num] = -1;
    return squares_num;
}

/*returns the rook moves list*/
int rook(char square, board *the_board, char color, move *moves, char *pinned_pieces){
    char i = 0, is_pinned = is_in_array(pinned_pieces, square);
    return move_in_straight_lines(square, the_board, color, moves, is_pinned);
}

/*returns the bishop moves list*/
int bishop(char square, board *the_board, char color, move *moves, char *pinned_pieces){
    char i = 0, is_pinned = is_in_array(pinned_pieces, square);
    return move_in_diagonal_lines(square, the_board, color, moves, is_pinned);
}

/*creats 2 lists 1 for striaght lins and one for diagonal and conects them to one which is the final*/
int queen(char square, board *the_board, char color, move *moves, char *pinned_pieces){
    char i = 0, is_pinned = is_in_array(pinned_pieces, square);
    int len1 = move_in_straight_lines(square, the_board, color, moves, is_pinned);
    int len2 = move_in_diagonal_lines(square, the_board, color, moves+len1, is_pinned);
    moves[len1+len2] = END;
    return len1 + len2;
}

/*checks every possible move of the king out of 8*/
int king(char square, board *the_board, char color, move *moves){
    int move_num = 0;
    move temp;
    if(move_up(square, the_board, color)){
        create_a_move(temp, square, square+UP, 0, 0, 0);
        if(is_move_valid(the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    if(move_down(square, the_board, color)){
        create_a_move(temp, square, square+DOWN, 0, 0, 0);
        if(is_move_valid(the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    if(move_left(square, the_board, color)){
        create_a_move(temp, square, square+LEFT, 0, 0, 0);
        if(is_move_valid(the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    if(move_right(square, the_board, color)){
        create_a_move(temp, square, square+RIGHT, 0, 0, 0);
        if(is_move_valid(the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    if(move_up_right(square, the_board, color)){
        create_a_move(temp, square, square+UP_RIGHT, 0, 0, 0);
        if(is_move_valid(the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    if(move_up_left(square, the_board, color)){
        create_a_move(temp, square, square+UP_LEFT, 0, 0, 0);
        if(is_move_valid(the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    if(move_down_right(square, the_board, color)){
        create_a_move(temp, square, square+DOWN_RIGHT, 0, 0, 0);
        if(is_move_valid(the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    if(move_down_left(square, the_board, color)){
        create_a_move(temp, square, square+DOWN_LEFT, 0, 0, 0);
        if(is_move_valid(the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    moves[move_num] = END;
    return move_num;
}

/*checks every possible move for the knight out of 8*/
int knight(char square, board *the_board, char color, move *moves, char *pinned_pieces){
    int move_num = 0;
    move temp;
    char i = 0;
    char is_pinned = is_in_array(pinned_pieces, square);
    /*knight up up right*/
    if(get_column(square) < 7 && get_row(square) < 6){
        if(!colid_with_allay(square+KNIGHT_UP_UP_RIGHT, the_board, color)){
            create_a_move(temp, square, square+KNIGHT_UP_UP_RIGHT, 0, 0, 0);
            if(!is_pinned || is_move_valid(the_board, temp, color)){ /* If not pinned there is no need to check if valid. */
                moves[move_num] = temp;
                move_num ++;
            }
        }
    }
    /*knight up up left*/
    if(get_column(square) > 0 && get_row(square) < 6){
        if(!colid_with_allay(square+KNIGHT_UP_UP_LEFT, the_board, color)){
            create_a_move(temp, square, square+KNIGHT_UP_UP_LEFT, 0, 0, 0);
            if(!is_pinned || is_move_valid(the_board, temp, color)){
                moves[move_num] = temp;
                move_num ++;
            }
        }
    }
    /*knight up right right*/
    if(get_column(square) < 6 && get_row(square) < 7){
        if(!colid_with_allay(square+KNIGHT_UP_RIGHT_RIGHT, the_board, color)){
            create_a_move(temp, square, square+KNIGHT_UP_RIGHT_RIGHT, 0, 0, 0);
            if(!is_pinned || is_move_valid(the_board, temp, color)){
                moves[move_num] = temp;
                move_num ++;
            }
        }
    }
    /*knight up left left*/
    if(get_column(square) > 1 && get_row(square) < 7){
        if(!colid_with_allay(square+KNIGHT_UP_LEFT_LEFT, the_board, color)){
            create_a_move(temp, square, square+KNIGHT_UP_LEFT_LEFT, 0, 0, 0);
            if(!is_pinned || is_move_valid(the_board, temp, color)){
                moves[move_num] = temp;
                move_num ++;
            }
        }
    }
    /*knight down down right*/
    if(get_column(square) < 7 && get_row(square) > 1){
        if(!colid_with_allay(square+KNIGHT_DOWN_DOWN_RIGHT, the_board, color)){
            create_a_move(temp, square, square+KNIGHT_DOWN_DOWN_RIGHT, 0, 0, 0);
            if(!is_pinned || is_move_valid(the_board, temp, color)){
                moves[move_num] = temp;
                move_num ++;
            }
        }
    }
    /*knight down down left*/
    if(get_column(square) > 0 && get_row(square) > 1){
        if(!colid_with_allay(square+KNIGHT_DOWN_DOWN_LEFT, the_board, color)){
            create_a_move(temp, square, square+KNIGHT_DOWN_DOWN_LEFT, 0, 0, 0);
            if(!is_pinned || is_move_valid(the_board, temp, color)){
                moves[move_num] = temp;
                move_num ++;
            }
        }
    }
    /*knight down right right*/
    if(get_column(square) < 6 && get_row(square) > 0){
        if(!colid_with_allay(square+KNIGHT_DOWN_RIGHT_RIGHT, the_board, color)){
            create_a_move(temp, square, square+KNIGHT_DOWN_RIGHT_RIGHT, 0, 0, 0);
            if(!is_pinned || is_move_valid(the_board, temp, color)){
                moves[move_num] = temp;
                move_num ++;
            }
        }
    }
    /*knight down left left*/
    if(get_column(square) > 1 && get_row(square) > 0){
        if(!colid_with_allay(square+KNIGHT_DOWN_LEFT_LEFT, the_board, color)){
            create_a_move(temp, square, square+KNIGHT_DOWN_LEFT_LEFT, 0, 0, 0);
            if(!is_pinned || is_move_valid(the_board, temp, color)){
                moves[move_num] = temp;
                move_num ++;
            }
        }
    }
    moves[move_num] = END;
    return move_num;
}

/* Checks every special move the pawn can do exept for the usual on which also gets checked but its minor, anyway there is 2 func
because the pawn for each color moves only in one diriction and its the exact oppised of the other. */
int whitepawn(char square, board *the_board, move *moves, char *pinned_pieces){
    int move_num = 0;
    int crown;
    int x = 0;
    move temp;
    char i = 0;
    char is_pinned = is_in_array(pinned_pieces, square);

    if(get_row(square) == 6)
        x = 3;

    if(get_row(square) == 1){
        if(pawn_straight(square, the_board, WHITE)){
            if(pawn_straight(square+UP, the_board, WHITE)){
                create_a_move(temp, square, square+(UP*2), 0, 0, 0);
                if(!is_pinned || is_move_valid(the_board, temp, WHITE)){ /* If not pinned there is no need to check if valid. */
                    moves[move_num] = temp;
                    move_num ++;
                }
            }
        }
    }

    for(crown = 0; crown <= x; crown++){
        if(pawn_straight(square, the_board, WHITE)){
            create_a_move(temp, square, square+UP, crown, 0, 0);
            if(!is_pinned || is_move_valid(the_board, temp, WHITE)){
                moves[move_num] = temp;
                move_num ++;
            }
        }
        if(pawn_eat_right(square, the_board, WHITE)){
            create_a_move(temp, square, square+UP_RIGHT, crown, 0, 0);
            if(!is_pinned || is_move_valid(the_board, temp, WHITE)){
                moves[move_num] = temp;
                move_num ++;
            }
        }  
        if(pawn_eat_left(square, the_board, WHITE)){
            create_a_move(temp, square, square+UP_LEFT, crown, 0, 0);
            if(!is_pinned || is_move_valid(the_board, temp, WHITE)){
                moves[move_num] = temp;
                move_num ++;
            }
        }
    }
    moves[move_num] = END;
    return move_num;
}


int blackpawn(char square, board *the_board, move *moves, char *pinned_pieces){
    int move_num = 0;
    move temp;
    char crown;
    int x = 0;
    char is_pinned = is_in_array(pinned_pieces, square);
    if(get_row(square) == 1)
        x = 3;
    if(get_row(square) == 6){
        if(pawn_straight(square, the_board, BLACK)){
            if(pawn_straight(square+DOWN, the_board, BLACK)){
                create_a_move(temp, square, square+(DOWN*2), 0, 0, 0);
                if(!is_pinned || is_move_valid(the_board, temp, BLACK)){ /* If not pinned there is no need to check if valid. */
                    moves[move_num] = temp;
                    move_num ++;
                }
            }
        }
    }
    for(crown = 0; crown <= x; crown++){
        if(pawn_straight(square, the_board, BLACK)){
            create_a_move(temp, square, square+DOWN, crown, 0, 0);
            if(!is_pinned || is_move_valid(the_board, temp, BLACK)){
                moves[move_num] = temp;
                move_num ++;
            }
        }
        if(pawn_eat_right(square, the_board, BLACK)){
            create_a_move(temp, square, square+DOWN_RIGHT, crown, 0, 0);
            if(!is_pinned || is_move_valid(the_board, temp, BLACK)){
                moves[move_num] = temp;
                move_num ++;
            }
        }
        if(pawn_eat_left(square, the_board, BLACK)){
            create_a_move(temp, square, square+DOWN_LEFT, crown, 0, 0);
            if(!is_pinned || is_move_valid(the_board, temp, BLACK)){
                moves[move_num] = temp;
                move_num ++;
            }
        }
    }
    moves[move_num] = END;
    return move_num;
}

/* This function checks if a square is attacked. */
char is_move_valid(board *the_board, move the_move, char color){
    irreversible_move_info inf = get_irrev_move_info(the_board, the_move);
    char whos_turn = the_board->whos_turn; /* Whos turn is it? (needed for advanced get_possible_moves). */
    if(color){
        commit_a_move_for_white(the_board, the_move);
        if(is_attacked_by_black(the_board, find_king_square(the_board, WHITE))) {
            unmake_move(the_board, the_move, inf);
            the_board->whos_turn = whos_turn;
            return 0;
        }
        unmake_move(the_board, the_move, inf);
        the_board->whos_turn = whos_turn;
        return 1;
    } 
    commit_a_move_for_black(the_board, the_move);
    if(is_attacked_by_white(the_board, find_king_square(the_board, BLACK))) {
        unmake_move(the_board, the_move, inf);
        the_board->whos_turn = whos_turn;
        return 0;
    }
    unmake_move(the_board, the_move, inf);
    the_board->whos_turn = whos_turn;
    return 1;  
}


int en_passant_and_castle(board *the_board, move *moves, char color){
    int move_num = 0;
    char square = 0;
    move temp;
    if(the_board->en_passant_pawn){
        if (!pass_left(the_board->en_passant_pawn + LEFT)) { /* En passant right: */
            square = the_board->en_passant_pawn + LEFT; 
            if(color_of_piece(square, the_board) == WHITE && color == WHITE){ /* WHITE: */
                create_a_move(temp, square, square + UP_RIGHT, 0, 0, 0);
                    if(is_move_valid(the_board, temp, WHITE)){
                        moves[move_num] = temp;
                        move_num ++;
                    }
            }
            if(color_of_piece(square, the_board) == BLACK && color == BLACK){ /* BLACK: */
                create_a_move(temp, square, square + DOWN_RIGHT, 0, 0, 0);
                if(is_move_valid(the_board, temp, BLACK)){
                        moves[move_num] = temp;
                        move_num ++;
                    }
            }
        }
        if (!pass_right(the_board->en_passant_pawn + RIGHT)) { /* En passant left: */
            square = the_board->en_passant_pawn + RIGHT;
            if(color_of_piece(square, the_board) == WHITE && color == WHITE){ /* WHITE: */
                create_a_move(temp, square, square + UP_LEFT, 0, 0, 0);
                if(is_move_valid(the_board, temp, WHITE)){
                        moves[move_num] = temp;
                        move_num ++;
                    }
            }
            if(color_of_piece(square, the_board) == BLACK && color == BLACK){ /* BLACK: */
                create_a_move(temp, square, square + DOWN_LEFT, 0, 0, 0);
                if(is_move_valid(the_board, temp, BLACK)){
                        moves[move_num] = temp;
                        move_num ++;
                    }
            }
        }
    }
    if(color){
        if(check_white_long_castle(the_board)){
            create_a_move(temp, DEAFULT_WHITE_KING_SQUARE, DEAFULT_WHITE_KING_SQUARE-2, 0, 1, 0);
            moves[move_num] = temp;
            move_num ++;
        }
        if(check_white_short_castle(the_board)){
            create_a_move(temp, DEAFULT_WHITE_KING_SQUARE, DEAFULT_WHITE_KING_SQUARE+2, 0, 0, 1);
            moves[move_num] = temp;
            move_num ++;
        }
    }
    if(!color){
        if(check_black_long_castle(the_board)){
            create_a_move(temp, DEAFULT_BLACK_KING_SQUARE, DEAFULT_BLACK_KING_SQUARE-2, 0, 1, 0);
            moves[move_num] = temp; 
            move_num ++;
        }
        if(check_black_short_castle(the_board)){
            create_a_move(temp,DEAFULT_BLACK_KING_SQUARE, DEAFULT_BLACK_KING_SQUARE+2, 0, 0, 1);
            moves[move_num] = temp;
            move_num ++;
        }
    }
    moves[move_num] = END;
    return move_num;
}


char color_of_piece(char square, board *the_board){
    char peice = get_piece_in_square(the_board, square);
    if(peice > NUM_OF_WHITE_PIECES)
        return BLACK;
    return WHITE;
}

/*calls the right func for the peice it was asked to check*/
char moves_of_piece(char square, board *the_board, move * moves, char *pinned_pieces){
    char peice = get_piece_in_square(the_board, square);
    switch (peice)
    {
    case white_knight:
        return knight(square, the_board, WHITE, moves, pinned_pieces);
    
    case black_knight:
        return knight(square, the_board, BLACK, moves, pinned_pieces);

    case white_rook:
        return rook(square, the_board, WHITE, moves, pinned_pieces);
    
    case black_rook:
        return rook(square, the_board, BLACK, moves, pinned_pieces);

    case white_queen:
        return queen(square, the_board, WHITE, moves, pinned_pieces);

    case black_queen:
        return queen(square, the_board, BLACK, moves, pinned_pieces);
    
    case white_king:
        return king(square, the_board, WHITE, moves);
    
    case black_king:
        return king(square, the_board, BLACK, moves);

    case white_bishop:
        return bishop(square, the_board, WHITE, moves, pinned_pieces);

    case black_bishop:
        return bishop(square, the_board, BLACK, moves, pinned_pieces);

    case white_pawn:
        return whitepawn(square, the_board, moves, pinned_pieces);
    
    case black_pawn:
        return blackpawn(square, the_board, moves, pinned_pieces);

    default:
        return 0;
    }
    return 1;
}

char get_max_moves_of_piece(char piece) {
    switch (piece)
    {
    case white_rook:
        return ROOK_MAX_MOVES;
    
    case white_king:
        return KING_MAX_MOVES;

    case white_knight:
        return KNIGHT_MAX_MOVES;

    case white_queen:
        return QUEEN_MAX_MOVES;

    case white_pawn:
        return PAWN_MAX_MOVES;
    
    case white_bishop:
        return BISHOP_MAX_MOVES;

    case black_rook:
        return ROOK_MAX_MOVES;
    
    case black_king:
        return KING_MAX_MOVES;

    case black_knight:
        return KNIGHT_MAX_MOVES;

    case black_queen:
        return QUEEN_MAX_MOVES;

    case black_pawn:
        return PAWN_MAX_MOVES;
    
    case black_bishop:
        return BISHOP_MAX_MOVES;
    
    default:
        return 0;
    }
}

char get_pinned_pieces(board *b, char color, char *pinned_pieces) {
    char king_square = find_king_square(b, color);
    char i = 0, j = 0;
    char no_of_pinned_pieces = 0;
    
    while (!pass_up(king_square + i * UP)) {
        i++;
        if (colid_with_allay(king_square + i * UP, b, color)) {
            if (j!=0) {
                break;
            }
            j = king_square + i * UP;
        }
        else if (colid_with_enemy(king_square + i * UP, b, color) && j!=0) {
            if (get_piece_in_square(b, king_square + i * UP) == white_queen || get_piece_in_square(b, king_square + i * UP) == white_rook || get_piece_in_square(b, king_square + i * UP) == black_queen || get_piece_in_square(b, king_square + i * UP) == black_rook) {
                pinned_pieces[no_of_pinned_pieces] = j;
                no_of_pinned_pieces++;
            }
            break;
        }
    }

    i = 0;
    j = 0;
    // make the same thing for the other directions
    while (!pass_down(king_square + i * DOWN)) {
        i++;
        if (colid_with_allay(king_square + i * DOWN, b, color)) {
            if (j!=0) {
                break;
            }
            j = king_square + i * DOWN;
        }
        else if (colid_with_enemy(king_square + i * DOWN, b, color) && j!=0) {
            if (get_piece_in_square(b, king_square + i * DOWN) == white_queen || get_piece_in_square(b, king_square + i * DOWN) == white_rook || get_piece_in_square(b, king_square + i * DOWN) == black_queen || get_piece_in_square(b, king_square + i * DOWN) == black_rook) {
                pinned_pieces[no_of_pinned_pieces] = j;
                no_of_pinned_pieces++;
            }
            break;
        }
    }

    i = 0;
    j = 0;
    while (!pass_right(king_square + i * RIGHT)) {
        i++;
        if (colid_with_allay(king_square + i * RIGHT, b, color)) {
            if (j!=0) {
                break;
            }
            j = king_square + i * RIGHT;
        }
        else if (colid_with_enemy(king_square + i * RIGHT, b, color) && j!=0) {
            if (get_piece_in_square(b, king_square + i * RIGHT) == white_queen || get_piece_in_square(b, king_square + i * RIGHT) == white_rook || get_piece_in_square(b, king_square + i * RIGHT) == black_queen || get_piece_in_square(b, king_square + i * RIGHT) == black_rook) {
                pinned_pieces[no_of_pinned_pieces] = j;
                no_of_pinned_pieces++;
            }
            break;
        }
    }
    
    i = 0;
    j = 0;
    while (!pass_left(king_square + i * LEFT)) {
        i++;
        if (colid_with_allay(king_square + i * LEFT, b, color)) {
            if (j!=0) {
                break;
            }
            j = king_square + i * LEFT;
        }
        else if (colid_with_enemy(king_square + i * LEFT, b, color) && j!=0) {
            if (get_piece_in_square(b, king_square + i * LEFT) == white_queen || get_piece_in_square(b, king_square + i * LEFT) == white_rook || get_piece_in_square(b, king_square + i * LEFT) == black_queen || get_piece_in_square(b, king_square + i * LEFT) == black_rook) {
                pinned_pieces[no_of_pinned_pieces] = j;
                no_of_pinned_pieces++;
            }
            break;
        }
    }
    
    i = 0;
    j = 0;
    /* Check danger form diagonals: */
    while (!pass_up_right(king_square + i * UP_RIGHT)) {
        i++;
        if (colid_with_allay(king_square + i * UP_RIGHT, b, color)) {
            if (j!=0) {
                break;
            }
            j = king_square + i * UP_RIGHT;
        }
        else if (colid_with_enemy(king_square + i * UP_RIGHT, b, color) && j!=0) {
            if (get_piece_in_square(b, king_square + i * UP_RIGHT) == white_queen || get_piece_in_square(b, king_square + i * UP_RIGHT) == white_bishop || get_piece_in_square(b, king_square + i * UP_RIGHT) == black_queen || get_piece_in_square(b, king_square + i * UP_RIGHT) == black_bishop) {
                pinned_pieces[no_of_pinned_pieces] = j;
                no_of_pinned_pieces++;
            }
            break;
        }
    }


    i = 0;
    j = 0;
    while (!pass_up_left(king_square + i * UP_LEFT)) {
        i++;
        if (colid_with_allay(king_square + i * UP_LEFT, b, color)) {
            if (j!=0) {
                break;
            }
            j = king_square + i * UP_LEFT;
        }
        else if (colid_with_enemy(king_square + i * UP_LEFT, b, color) && j!=0) {
            if (get_piece_in_square(b, king_square + i * UP_LEFT) == white_queen || get_piece_in_square(b, king_square + i * UP_LEFT) == white_bishop || get_piece_in_square(b, king_square + i * UP_LEFT) == black_queen || get_piece_in_square(b, king_square + i * UP_LEFT) == black_bishop) {
                pinned_pieces[no_of_pinned_pieces] = j;
                no_of_pinned_pieces++;
            }
            break;
        }
    }

    i = 0;
    j = 0;
    while (!pass_down_right(king_square + i * DOWN_RIGHT)) {
        i++;
        if (colid_with_allay(king_square + i * DOWN_RIGHT, b, color)) {
            if (j!=0) {
                break;
            }
            j = king_square + i * DOWN_RIGHT;
        }
        else if (colid_with_enemy(king_square + i * DOWN_RIGHT, b, color) && j!=0) {
            if (get_piece_in_square(b, king_square + i * DOWN_RIGHT) == white_queen || get_piece_in_square(b, king_square + i * DOWN_RIGHT) == white_bishop || get_piece_in_square(b, king_square + i * DOWN_RIGHT) == black_queen || get_piece_in_square(b, king_square + i * DOWN_RIGHT) == black_bishop) {
                pinned_pieces[no_of_pinned_pieces] = j;
                no_of_pinned_pieces++;
            }
            break;
        }
    }

    i = 0;
    j = 0;
    while (!pass_down_left(king_square + i * DOWN_LEFT)) {
        i++;
        if (colid_with_allay(king_square + i * DOWN_LEFT, b, color)) {
            if (j!=0) {
                break;
            }
            j = king_square + i * DOWN_LEFT;
        }
        else if (colid_with_enemy(king_square + i * DOWN_LEFT, b, color) && j!=0) {
            if (get_piece_in_square(b, king_square + i * DOWN_LEFT) == white_queen || get_piece_in_square(b, king_square + i * DOWN_LEFT) == white_bishop || get_piece_in_square(b, king_square + i * DOWN_LEFT) == black_queen || get_piece_in_square(b, king_square + i * DOWN_LEFT) == black_bishop) {
                pinned_pieces[no_of_pinned_pieces] = j;
                no_of_pinned_pieces++;
            }
            break;
        }
    }
    pinned_pieces[no_of_pinned_pieces] = -1;
    return no_of_pinned_pieces;
}

void get_possible_moves(board *the_board, move *new_all_moves ,move *all_moves, move last_move, irreversible_move_info inf){
    char pieces_to_recalculate[40]; /* The squares of the pieces that needs recalculation. */
    char no_pieces_to_recalculate = 2;
    unsigned char i,j,k,n, src, no_white_moves = 0, no_black_moves = 0;
    move all_moves_copy[MAX_POSSIBLE_MOVES];
    if (all_moves == 0 || all_moves[0] == END) { /* If there aren't any moves in all_moves... */
        get_all_moves(the_board, new_all_moves); /* Get the moves the long way. */
        return;
    }

    /* COPY ALL MOVES */
    for (k = 0; all_moves[k] != END; k++) {
        all_moves_copy[k] = all_moves[k];
    }
    all_moves_copy[k] = END;
    for (k = MAX_POSSIBLE_MOVES/2; all_moves[k] != END; k++) {
        all_moves_copy[k] = all_moves[k];
    }
    all_moves_copy[k] = END;

    /* IS IT CHECK? */
    if (the_board->whos_turn == WHITE) {
        if (is_attacked_by_black(the_board,find_king_square(the_board, WHITE))) {
            get_all_moves(the_board, new_all_moves); /* Get the moves the long way. */
            return;
        }
    }
    if (the_board->whos_turn == BLACK) {
        if (is_attacked_by_white(the_board,find_king_square(the_board, BLACK))) {
            get_all_moves(the_board, new_all_moves); /* Get the moves the long way. */
            return;
        }
    }
    pieces_to_recalculate[0] = get_dst_square(last_move); /* Adding the moving piece to recalculate. */
    pieces_to_recalculate[1] = find_king_square(the_board, the_board->whos_turn); /* Adding the king to recalculate. */

    no_pieces_to_recalculate += squares_in_directions(the_board, get_dst_square(last_move), pieces_to_recalculate + 2); /* Get the pieces to recalcule from this move.*/
    
    unmake_move(the_board, last_move, inf); /* UNDO move. */
    /* IS LAST MOVE CHECK? */
    if (the_board->whos_turn == WHITE) {
        if (is_attacked_by_black(the_board,find_king_square(the_board, WHITE))) {
            commit_a_move_for_white(the_board,last_move);
            get_all_moves(the_board, new_all_moves); /* Get the moves the long way. */
            return;
        }
    }
    if (the_board->whos_turn == BLACK) {
        if (is_attacked_by_white(the_board,find_king_square(the_board, BLACK))) {
            commit_a_move_for_black(the_board,last_move);
            get_all_moves(the_board, new_all_moves); /* Get the moves the long way. */
            return;
        }
    }
    no_pieces_to_recalculate += squares_in_directions(the_board, get_src_square(last_move), pieces_to_recalculate + no_pieces_to_recalculate); /* Get the pieces to recalcule from last move.*/
    /* REDO move. */
    if (the_board->whos_turn == 1)
        commit_a_move_for_white(the_board,last_move);
    else
        commit_a_move_for_black(the_board,last_move);

    /* Recalculates the moves for needed pieces. Removes the previous moves of those pieces. 
            Copies everything back to the origional array. */
    char pinned_pieces[40];
    get_pinned_pieces(the_board, the_board->whos_turn, pinned_pieces);
    /* Recalculates the moves. */
    for (i = 0, j = 0, n = 0; i + j + n< no_pieces_to_recalculate;) { /* ('i' - the white moves index, 'j' - black, 'n' - number of duplicated moves so far). */
        for (k = 0; k < i + j + n; k++) {
            if (pieces_to_recalculate[i+j+n] == pieces_to_recalculate[k]) { /* If there is a duplicated move. */
                n++;
                break;
            }
        }
        if (k != i + j + n) { /* If it was a duplication. */
            continue;
        }

        if (is_white(get_piece_in_square(the_board, pieces_to_recalculate[i+j+n]))) {
            no_white_moves += moves_of_piece(pieces_to_recalculate[i+j+n], the_board, new_all_moves+no_white_moves, pinned_pieces);
            i++;
        }
        else {
            no_black_moves += moves_of_piece(pieces_to_recalculate[i+j+n], the_board, new_all_moves+(no_black_moves+MAX_POSSIBLE_MOVES/2), pinned_pieces); /* The black moves start from the second half. */
            j++;
        }
    }
    no_white_moves += en_passant_and_castle(the_board, new_all_moves+no_white_moves, WHITE);
    no_black_moves += en_passant_and_castle(the_board, new_all_moves+(no_black_moves+MAX_POSSIBLE_MOVES/2), BLACK);
    

    i = no_white_moves;
    j = no_black_moves;
    /* COPY ALL WHITE MOVES */
    for (k = 0; all_moves_copy[k] != 0; k++) {
        if (all_moves_copy[k] == -1)
            continue;
        src = get_src_square(all_moves_copy[k]);
        /* Remove the moves of the re-calculated pieces: */
        for (n = 0; pieces_to_recalculate[n] != -1; n++) { 
            if (src == pieces_to_recalculate[n] || src == get_src_square(last_move)) {
                all_moves_copy[k] = -1;
                break;
            }
        }
        if (pieces_to_recalculate[n] != -1) {
            continue;
        }
        if (get_piece_in_square(the_board,get_src_square(all_moves_copy[k])) == white_king && is_attacked_by_black(the_board,get_dst_square(all_moves_copy[k]))) { /* If the king will go into check. */
            all_moves_copy[k] = -1;
            continue;
        }

        new_all_moves[i] = all_moves_copy[k];
        i++;
    }
    new_all_moves[i] = END;
    /* COPY ALL BLACK MOVES */
    for (k = MAX_POSSIBLE_MOVES/2; all_moves_copy[k] != 0; k++) {
        if (all_moves_copy[k] == -1)
            continue;
        src = get_src_square(all_moves_copy[k]);
        /* Remove the moves of the recalculated pieces: */
        for (n = 0; pieces_to_recalculate[n] != -1; n++) { 
            if (src == pieces_to_recalculate[n] || src == get_src_square(last_move)) {
                all_moves_copy[k] = -1;
                break;
            }
        }
        if (pieces_to_recalculate[n] != -1) {
            continue;
        }
        if (get_piece_in_square(the_board,get_src_square(all_moves_copy[k])) == black_king && is_attacked_by_white(the_board,get_dst_square(all_moves_copy[k]))) { /* If the king will go into check. */
            all_moves_copy[k] = -1;
            continue;
        }
        new_all_moves[j + MAX_POSSIBLE_MOVES/2] = all_moves_copy[k];
        j++;
    }
    new_all_moves[j + MAX_POSSIBLE_MOVES/2] = END;
}

/* This function gets the move the long way (calculates the moves of everything). */
void get_all_moves(board *the_board,move *all_moves){
    char color = BLACK; /* Needed for the loop, DO NOT TOUCH */
    char piece;
    int i, j, len = 0, move_num = 0;
    char pinned_pieces[65];

    /* If it's a check - make all pieces of the checked player pinned: */
    if ((the_board->whos_turn == WHITE && is_attacked_by_black(the_board, find_king_square(the_board, WHITE))) || (the_board->whos_turn == BLACK && is_attacked_by_white(the_board, find_king_square(the_board, BLACK)))) {
        for (i = 0, j = 0; i < 64; i++) {
            if (color_of_piece(i, the_board) == the_board->whos_turn) {
                pinned_pieces[j] = i;
                j++;
            }
        }
        pinned_pieces[j] = -1;
    }
    else 
        get_pinned_pieces(the_board, the_board->whos_turn, pinned_pieces); /* Gets the pinned pieces. */


    for (j = 0; j < 2; j++) {
        move_num = j * MAX_POSSIBLE_MOVES / 2; /* First of all gets white's moves, than black's (in the middle of the array)*/
        color = !color;
        for(i = 0; i<NUMBER_OF_SQUARES; i++){
            if(color_of_piece(i, the_board) == color && get_piece_in_square(the_board, i) != empty){
                len = moves_of_piece(i, the_board, all_moves+move_num, pinned_pieces);
                move_num+=len;
            }
        }

        len = en_passant_and_castle(the_board, all_moves+move_num, color);
        move_num+=len;
        
        all_moves[move_num] = END;
    }
}
