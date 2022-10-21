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
int move_in_straight_lines(char square, board *the_board, char color, move *moves){
    int i = 0;
    int move_num = 0;
    move temp;
    /*rook up*/
    while(move_up(square + i*UP, the_board, color)){
        create_a_move(temp, square, square + (i+1)*UP, 0, 0, 0);
        i++;
        if(is_move_valid(the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    /*rook down*/
    i = 0;
    while(move_down(square + i*DOWN, the_board, color)){
        create_a_move(temp, square, square + (i+1)*DOWN, 0, 0, 0);
        i++;
        if(is_move_valid(the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    /*rook left*/
    i = 0;
    while(move_left(square + i*LEFT, the_board, color)){
        create_a_move(temp, square, square + (i+1)*LEFT, 0, 0, 0);
        i++;
        if(is_move_valid(the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    /*rook right*/
    i = 0;
    while(move_right(square + i*RIGHT, the_board, color)){
        create_a_move(temp, square, square + (i+1)*RIGHT, 0, 0, 0);
        i++;
        if(is_move_valid(the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    moves[move_num] = END;
    return move_num;
}

/*this one returns the list of moves in diagonal lines - up_right up_left etc.*/
int move_in_diagonal_lines(char square, board *the_board, char color, move *moves){
    int i = 0;
    int move_num = 0;
    move temp;
    /* up left*/
    while(move_up_left(square + i*UP_LEFT, the_board, color)){
        create_a_move(temp, square, square + (i+1)*UP_LEFT, 0, 0, 0);
        i++;
        if(is_move_valid(the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    /* up right*/
    i = 0;
    while(move_up_right(square + i*UP_RIGHT, the_board, color)){
        create_a_move(temp, square, square + (i+1)*UP_RIGHT, 0, 0, 0);
        i++;
        if(is_move_valid(the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    /* down right*/
    i = 0;
    while(move_down_right(square + i*DOWN_RIGHT, the_board, color)){
        create_a_move(temp, square, square + (i+1)*DOWN_RIGHT, 0, 0, 0);
        i++;
        if(is_move_valid(the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    /* down left*/
    i = 0;
    while(move_down_left(square + i*DOWN_LEFT, the_board, color)){
        create_a_move(temp, square, square + (i+1)*DOWN_LEFT, 0, 0, 0);
        i++;
        if(is_move_valid(the_board, temp, color)){
            moves[move_num] = temp;
            move_num ++;
        }
    }
    moves[move_num] = END;
    return move_num;
}

/*returns the rook moves list*/
int rook(char square, board *the_board, char color, move *moves){
    return move_in_straight_lines(square, the_board, color, moves);
}

/*returns the bishop moves list*/
int bishop(char square, board *the_board, char color, move *moves){
    return move_in_diagonal_lines(square, the_board, color, moves);
}

/*creats 2 lists 1 for striaght lins and one for diagonal and conects them to one which is the final*/
int queen(char square, board *the_board, char color, move *moves){
    int i = 0;
    int len1 = move_in_straight_lines(square, the_board, color, moves);
    int len2 = move_in_diagonal_lines(square, the_board, color, moves+len1);
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
int knight(char square, board *the_board, char color, move *moves){
    int move_num = 0;
    move temp;
    /*knight up up right*/
    if(get_column(square) < 7 && get_row(square) < 6){
        if(!colid_with_allay(square+KNIGHT_UP_UP_RIGHT, the_board, color)){
            create_a_move(temp, square, square+KNIGHT_UP_UP_RIGHT, 0, 0, 0);
            if(is_move_valid(the_board, temp, color)){
                moves[move_num] = temp;
                move_num ++;
            }
        }
    }
    /*knight up up left*/
    if(get_column(square) > 0 && get_row(square) < 6){
        if(!colid_with_allay(square+KNIGHT_UP_UP_LEFT, the_board, color)){
            create_a_move(temp, square, square+KNIGHT_UP_UP_LEFT, 0, 0, 0);
            if(is_move_valid(the_board, temp, color)){
                moves[move_num] = temp;
                move_num ++;
            }
        }
    }
    /*knight up right right*/
    if(get_column(square) < 6 && get_row(square) < 7){
        if(!colid_with_allay(square+KNIGHT_UP_RIGHT_RIGHT, the_board, color)){
            create_a_move(temp, square, square+KNIGHT_UP_RIGHT_RIGHT, 0, 0, 0);
            if(is_move_valid(the_board, temp, color)){
                moves[move_num] = temp;
                move_num ++;
            }
        }
    }
    /*knight up left left*/
    if(get_column(square) > 1 && get_row(square) < 7){
        if(!colid_with_allay(square+KNIGHT_UP_LEFT_LEFT, the_board, color)){
            create_a_move(temp, square, square+KNIGHT_UP_LEFT_LEFT, 0, 0, 0);
            if(is_move_valid(the_board, temp, color)){
                moves[move_num] = temp;
                move_num ++;
            }
        }
    }
    /*knight down down right*/
    if(get_column(square) < 7 && get_row(square) > 1){
        if(!colid_with_allay(square+KNIGHT_DOWN_DOWN_RIGHT, the_board, color)){
            create_a_move(temp, square, square+KNIGHT_DOWN_DOWN_RIGHT, 0, 0, 0);
            if(is_move_valid(the_board, temp, color)){
                moves[move_num] = temp;
                move_num ++;
            }
        }
    }
    /*knight down down left*/
    if(get_column(square) > 0 && get_row(square) > 1){
        if(!colid_with_allay(square+KNIGHT_DOWN_DOWN_LEFT, the_board, color)){
            create_a_move(temp, square, square+KNIGHT_DOWN_DOWN_LEFT, 0, 0, 0);
            if(is_move_valid(the_board, temp, color)){
                moves[move_num] = temp;
                move_num ++;
            }
        }
    }
    /*knight down right right*/
    if(get_column(square) < 6 && get_row(square) > 0){
        if(!colid_with_allay(square+KNIGHT_DOWN_RIGHT_RIGHT, the_board, color)){
            create_a_move(temp, square, square+KNIGHT_DOWN_RIGHT_RIGHT, 0, 0, 0);
            if(is_move_valid(the_board, temp, color)){
                moves[move_num] = temp;
                move_num ++;
            }
        }
    }
    /*knight down left left*/
    if(get_column(square) > 1 && get_row(square) > 0){
        if(!colid_with_allay(square+KNIGHT_DOWN_LEFT_LEFT, the_board, color)){
            create_a_move(temp, square, square+KNIGHT_DOWN_LEFT_LEFT, 0, 0, 0);
            if(is_move_valid(the_board, temp, color)){
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
int whitepawn(char square, board *the_board, move *moves){
    int move_num = 0;
    int crown;
    int x = 0;
    move temp;

    if(get_row(square) == 6)
        x = 3;

    if(get_row(square) == 1){
        if(pawn_straight(square, the_board, WHITE)){
            if(pawn_straight(square+UP, the_board, WHITE)){
                create_a_move(temp, square, square+(UP*2), 0, 0, 0);
                if(is_move_valid(the_board, temp, WHITE)){
                    moves[move_num] = temp;
                    move_num ++;
                }
            }
        }
    }

    for(crown = 0; crown <= x; crown++){
        if(pawn_straight(square, the_board, WHITE)){
            create_a_move(temp, square, square+UP, crown, 0, 0);
            if(is_move_valid(the_board, temp, WHITE)){
                moves[move_num] = temp;
                move_num ++;
            }
        }
        if(pawn_eat_right(square, the_board, WHITE)){
            create_a_move(temp, square, square+UP_RIGHT, crown, 0, 0);
            if(is_move_valid(the_board, temp, WHITE)){
                moves[move_num] = temp;
                move_num ++;
            }
        }  
        if(pawn_eat_left(square, the_board, WHITE)){
            create_a_move(temp, square, square+UP_LEFT, crown, 0, 0);
            if(is_move_valid(the_board, temp, WHITE)){
                moves[move_num] = temp;
                move_num ++;
            }
        }
    }
    moves[move_num] = END;
    return move_num;
}


int blackpawn(char square, board *the_board, move *moves){
    int move_num = 0;
    move temp;
    char crown;
    int x = 0;
    if(get_row(square) == 1)
        x = 3;
    if(get_row(square) == 6){
        if(pawn_straight(square, the_board, BLACK)){
            if(pawn_straight(square+DOWN, the_board, BLACK)){
                create_a_move(temp, square, square+(DOWN*2), 0, 0, 0);
                if(is_move_valid(the_board, temp, BLACK)){
                    moves[move_num] = temp;
                    move_num ++;
                }
            }
        }
    }
    for(crown = 0; crown <= x; crown++){
        if(pawn_straight(square, the_board, BLACK)){
            create_a_move(temp, square, square+DOWN, crown, 0, 0);
            if(is_move_valid(the_board, temp, BLACK)){
                moves[move_num] = temp;
                move_num ++;
            }
        }
        if(pawn_eat_right(square, the_board, BLACK)){
            create_a_move(temp, square, square+DOWN_RIGHT, crown, 0, 0);
            if(is_move_valid(the_board, temp, BLACK)){
                moves[move_num] = temp;
                move_num ++;
            }
        }
        if(pawn_eat_left(square, the_board, BLACK)){
            create_a_move(temp, square, square+DOWN_LEFT, crown, 0, 0);
            if(is_move_valid(the_board, temp, BLACK)){
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
    if(color){
        commit_a_move_for_white(the_board, the_move);
        if(isAttacked_by_black(the_board, find_king_square(the_board, WHITE))) {
            unmake_move(the_board, the_move, inf);
            return 0;
        }
        unmake_move(the_board, the_move, inf);
        return 1;
    } 
    commit_a_move_for_black(the_board, the_move);
    if(isAttacked_by_white(the_board, find_king_square(the_board, BLACK))) {
        unmake_move(the_board, the_move, inf);
        return 0;
    }
    unmake_move(the_board, the_move, inf);
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
char moves_of_piece(char square, board *the_board, move * moves){
    char peice = get_piece_in_square(the_board, square);
    switch (peice)
    {
    case white_knight:
        return knight(square, the_board, WHITE, moves);
    
    case black_knight:
        return knight(square, the_board, BLACK, moves);

    case white_rook:
        return rook(square, the_board, WHITE, moves);
    
    case black_rook:
        return rook(square, the_board, BLACK, moves);

    case white_queen:
        return queen(square, the_board, WHITE, moves);

    case black_queen:
        return queen(square, the_board, BLACK, moves);
    
    case white_king:
        return king(square, the_board, WHITE, moves);
    
    case black_king:
        return king(square, the_board, BLACK, moves);

    case white_bishop:
        return bishop(square, the_board, WHITE, moves);

    case black_bishop:
        return bishop(square, the_board, BLACK, moves);

    case white_pawn:
        return whitepawn(square, the_board, moves);
    
    case black_pawn:
        return blackpawn(square, the_board, moves);

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

void unmake_move(board *b, move m, irreversible_move_info inf) {
    //print_board(b);
    char src = get_src_square(m);
    char dst = get_dst_square(m);
    char piece = get_piece_in_square(b,dst);
    if (b->whos_turn == WHITE) {
        b->whos_turn = BLACK;
        if (piece == black_king) {
            if (dst == 62 && src == 60) { /* The move was a short castle. */
                change_the_square(b, 60, black_king);
                change_the_square(b, 63, black_rook);
                change_the_square(b, 62, empty);
                change_the_square(b, 61, empty);
                b->can_black_castle_short = 1;
            }
            else if (dst == 58 && src == 60) { /* The move was a short castle. */
                change_the_square(b, 60, black_king);
                change_the_square(b, 56, black_rook);
                change_the_square(b, 58, empty);
                change_the_square(b, 59, empty);
                b->can_black_castle_long = 1;
            }
            else {
                change_the_square(b, src, black_king);
                change_the_square(b, dst, get_piece_taken(inf));
            }
        }
        else if (get_is_en_passant(inf) != 0) { /* The move was an en passant. */
            change_the_square(b,dst+UP,white_pawn);
            change_the_square(b, src, black_pawn);
            change_the_square(b, dst, empty);
        }
        else if (get_is_promoted(inf) == 1) {
            change_the_square(b, src, black_pawn);
            change_the_square(b, dst, get_piece_taken(inf));
        }
        else {
            change_the_square(b, src, piece);
            change_the_square(b, dst, get_piece_taken(inf));
        }
    }
    else {
        b->whos_turn = WHITE;
        if (piece == white_king) {
            if (dst == 6 && src == 4) { /* The move was a short castle. */
                change_the_square(b, 4, white_king);
                change_the_square(b, 7, white_rook);
                change_the_square(b, 6, empty);
                change_the_square(b, 5, empty);
                b->can_white_castle_short = 1;
            }
            else if (dst == 2 && src == 4) { /* The move was a short castle. */
                change_the_square(b, 4, white_king);
                change_the_square(b, 0, white_rook);
                change_the_square(b, 2, empty);
                change_the_square(b, 3, empty);
                b->can_white_castle_long = 1;
            }
            else {
                change_the_square(b, src, white_king);
                change_the_square(b, dst, get_piece_taken(inf));
            }
        }
        else if (get_is_en_passant(inf) != 0) { /* The move was an en passant. */
            change_the_square(b,dst+UP,black_pawn);
            change_the_square(b, src, white_pawn);
            change_the_square(b, dst, empty);
        }
        else if (get_is_promoted(inf) == 1) {
            change_the_square(b, src, white_pawn);
            change_the_square(b, dst, get_piece_taken(inf));
        }
        else {
            change_the_square(b, src, piece);
            change_the_square(b, dst, get_piece_taken(inf));
        }
    }
    b->en_passant_pawn = get_en_passant_pawn_last_move(inf);
    //print_board(b);
}

/*main function*/
move* get_all_moves(board *the_board,move *all_moves){
    char color = the_board->whos_turn;
    char piece;
    int i = 0, len = 1, move_num = 0;
    for(i = 0; i<NUMBER_OF_SQUARES; i++){
    	piece = get_piece_in_square(the_board, i);
        if(color_of_piece(i, the_board) == color && piece != empty)
            len += get_max_moves_of_piece(piece);
    }
    len += 4;
    if (all_moves == 0) {
        printf("no memory");
        exit(1);
    }
    all_moves[0] = END;
    for(i = 0; i<NUMBER_OF_SQUARES; i++){
        if(color_of_piece(i, the_board) == color && get_piece_in_square(the_board, i) != empty){
            len = moves_of_piece(i, the_board, all_moves+move_num);
            move_num+=len;
        }
    }

    len = en_passant_and_castle(the_board, all_moves+move_num, color);

    move_num+=len;
    
    all_moves[move_num] = END;
    return all_moves;
}
