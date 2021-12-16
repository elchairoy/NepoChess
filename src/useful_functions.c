/*
 Created by meir on 30/11/2021.
*/
#include "../include/useful_functions.h"
char * PIECES1[13] = {" " , "\u265E", "\u265C", "\u265B", "\u265A", "\u265F", "\u265D", "\u2658", "\u2656", "\u2655", "\u2654", "\u2659", "\u2657"};

#define MASK_FOR_A_HALF 0x0f /* A mask to get only a half of a byte. */
#define MASK_FOR_6BITS 0x003f /* A mask to get only 6 bits of a short. */
#define MASK_FOR_2BITS 0x0003 /* A mask to get only 2 bits of a short. */

#define SRC_LOC_INDEX 0 /* The place of the source square in the short. */
#define DST_LOC_INDEX 6 /* The place of the destination square in the short. */
#define PROMOTE_TO_INDEX 12 /* The place of the 'promote to what' in the short. */
#define IS_LONG_CASTLE_INDEX 14 /* The place of the 'is long castle' in the short. */
#define IS_SHORT_CASTLE_INDEX 15 /* The place of the 'is short castle' in the short. */

/* Gives the piece in the given square.
   If there is an error - returns -1. */
char get_piece_in_square(board *b ,unsigned char square_number) {
    if (square_number >= NUMBER_OF_SQUARES || b->squares == NULL) /* If there is an error: */
        return -1;

    if (square_number % 2 == 1) /* If the square is in the first half a byte: */
        return (b->squares[square_number/2] & MASK_FOR_A_HALF) /* - clears the second half. */;
        
    else /* If the square is in the second half a byte: */
        return (b->squares[square_number/2] & (MASK_FOR_A_HALF << 4)) /* - clears the first half */ >> 4 /* - shifts it to the first half. */;
}

/* Change the piece in the given square to the given piece.
   If there is an error - returns -1. */
char change_the_square(board *b,unsigned char square_number ,char new_piece) {
    if (square_number >= NUMBER_OF_SQUARES || b->squares == NULL) /* If there is an error: */
        return -1;
        
    if (square_number % 2 == 1) /* If the square is in the first half a byte: */
        b->squares[square_number / 2] = (b->squares[square_number / 2] & (MASK_FOR_A_HALF << (4))) /* - clears the first half */ | (new_piece); /* - places the new piece in the first half */
    
    else /* If the square is in the second half a byte: */
        b->squares[square_number / 2] = (b->squares[square_number / 2] & MASK_FOR_A_HALF) /* - clears the second half */ | (new_piece << 4); /* - places the new piece in the second half */
    return 0;
}

/* This function gets the data needed for a move and returns a short representing the move.
   If the data is invalid - returns -1. */
short create_a_move(unsigned char src_loc,unsigned char dst_loc,unsigned char promote_to,unsigned char castle_long,unsigned char castle_short) {
    move result = 0;

    if (src_loc >= NUMBER_OF_SQUARES || src_loc >= NUMBER_OF_SQUARES || promote_to >= 4 || castle_long >= 2 || castle_short >= 2) /* If the data is invalid: */
        return -1;

    result |= (src_loc << SRC_LOC_INDEX); /* Enters the src loc. */
    result |= (dst_loc << DST_LOC_INDEX); /* Enters the dst loc. */
    result |= (promote_to << PROMOTE_TO_INDEX); /* Enters the promotion choice. */
    result |= (castle_long << IS_LONG_CASTLE_INDEX); /* Enters if it's a long castle. */
    result |= (castle_short << IS_SHORT_CASTLE_INDEX); /* Enters if it's a short castle. */

    return result;
}

/* This function gets a move and returns the src square */
char get_src_square(move m) {
    return (m & (MASK_FOR_6BITS << SRC_LOC_INDEX)) >> SRC_LOC_INDEX;
}

/* This function gets a move and returns the dst square */
char get_dst_square(move m) {
    return (m & (MASK_FOR_6BITS << DST_LOC_INDEX)) >> DST_LOC_INDEX;
}

/* This function gets a move and returns what to promote to */
char get_promotion_choice(move m) {
    return (m & (MASK_FOR_2BITS << PROMOTE_TO_INDEX)) >> PROMOTE_TO_INDEX;
}

/* This function gets a move and returns if it's a long castle */
char get_is_long_castle(move m) {
    return (m & (1 << IS_LONG_CASTLE_INDEX)) >> IS_LONG_CASTLE_INDEX;
}

/* This function gets a move and returns if it's a short castle */
char get_is_short_castle(move m) {
    return (m & (1 << IS_SHORT_CASTLE_INDEX)) >> IS_SHORT_CASTLE_INDEX;
}

char isAttacked_by_black(board *the_board, char square) {
    char piece;
    int i = 0;
    /* Check danger from columns and rows: */
    while (move_up(square + i * UP, the_board, WHITE))
        i++;
    piece = get_piece_in_square(the_board, square + i * UP);
    if (piece ==  black_queen || piece == black_rook)
        return 1;

    i=0;
    while (move_down(square + i * DOWN, the_board, WHITE))
        i++;
    piece = get_piece_in_square(the_board, square + i * DOWN);
    if (piece ==  black_queen || piece == black_rook)
        return 1;
    
    i=0;
    while (move_right(square + i * RIGHT, the_board, WHITE))
        i++;
    piece = get_piece_in_square(the_board, square + i * RIGHT);
    if (piece ==  black_queen || piece == black_rook)
        return 1;
    
    i=0;
    while (move_left(square + i * LEFT, the_board, WHITE))
        i++;
    piece = get_piece_in_square(the_board, square + i * LEFT);
    if (piece ==  black_queen || piece == black_rook)
        return 1;
    
    i=0;
    /* Check danger form diagonals: */
    while (move_up_right(square + i * UP_RIGHT, the_board, WHITE))
        i++;
    piece = get_piece_in_square(the_board, square + i * UP_RIGHT);
    if (piece ==  black_queen || piece == black_bishop)
        return 1;
    i=0;

    while (move_up_left(square + i * UP_LEFT, the_board, WHITE))
        i++;
    piece = get_piece_in_square(the_board, square + i * UP_LEFT);
    if (piece ==  black_queen || piece == black_bishop)
        return 1;
    i=0;

    while (move_down_right(square + i * DOWN_RIGHT, the_board, WHITE))
        i++;
    piece = get_piece_in_square(the_board, square + i * DOWN_RIGHT);
    if (piece ==  black_queen || piece == black_bishop)
        return 1;
    i=0;

    while (move_down_left(square + i * DOWN_LEFT, the_board, WHITE))
        i++;
    piece = get_piece_in_square(the_board, square + i * DOWN_LEFT);
    if (piece == black_queen || piece == black_bishop)
        return 1;
    i=0;

    /* Check danger from knights: */

    /*knight up up right to eat*/
    if (get_column(square) > 0 && get_row(square) > 1) {
        if (get_piece_in_square(the_board, square + KNIGHT_DOWN_DOWN_LEFT) == black_knight)
            return 1;
    }

    /*knight up up left to eat*/
    if (get_column(square) < 7 && get_row(square) > 1) {
        if (get_piece_in_square(the_board, square + KNIGHT_DOWN_DOWN_RIGHT) == black_knight)
            return 1;
    }

    /*knight up right right to eat*/
    if (get_column(square) > 1 && get_row(square) > 0) {
        if (get_piece_in_square(the_board, square + KNIGHT_DOWN_LEFT_LEFT) == black_knight)
            return 1;
    }

    /*knight up left left to eat*/
    if (get_column(square) < 6 && get_row(square) > 0) {
        if (get_piece_in_square(the_board, square + KNIGHT_DOWN_RIGHT_RIGHT) == black_knight)
            return 1;
    }

    /*knight down down right to eat*/
    if (get_column(square) > 0 && get_row(square) < 6) {
        if (get_piece_in_square(the_board, square + KNIGHT_UP_UP_LEFT) == black_knight)
            return 1;
    }

    /*knight down down left to eat*/
    if (get_column(square) < 7 && get_row(square) < 6) {
        if (get_piece_in_square(the_board, square + KNIGHT_UP_UP_RIGHT) == black_knight)
            return 1;
    }

    /*knight down right right to eat*/
    if (get_column(square) > 2 && get_row(square) < 7) {
        if (get_piece_in_square(the_board, square + KNIGHT_UP_LEFT_LEFT) == black_knight)
            return 1;
    }

    /*knight down left left to eat*/
    if (get_column(square) < 6 && get_row(square) < 7) {
        if (get_piece_in_square(the_board, square + KNIGHT_UP_RIGHT_RIGHT) == black_knight)
            return 1;
    }


    /* Check danger from pawns: */
    if (get_piece_in_square(the_board, square + UP_RIGHT) == black_pawn)
        return 1;
    
    if (get_piece_in_square(the_board, square + UP_LEFT) == black_pawn)
        return 1;

        /* Check danger from king: */
    if (get_piece_in_square(the_board,square + RIGHT) == black_king)
        return 1;

    if (get_piece_in_square(the_board,square + LEFT) == black_king)
        return 1;

    if (get_piece_in_square(the_board,square + UP) == black_king)
        return 1;

    if (get_piece_in_square(the_board,square + DOWN) == black_king)
        return 1;

    if (get_piece_in_square(the_board,square + UP_RIGHT) == black_king)
        return 1;

    if (get_piece_in_square(the_board,square + UP_LEFT) == black_king)
        return 1;

    if (get_piece_in_square(the_board,square + DOWN_LEFT) == black_king)
        return 1;

    if (get_piece_in_square(the_board,square + DOWN_RIGHT) == black_king)
        return 1;


    return 0;
}


char isAttacked_by_white(board *the_board, char square) {
    char piece;
    int i = 0;
    /* Check danger from columns and rows: */
    while (move_up(square + i * UP, the_board, BLACK))
        i++;
    piece = get_piece_in_square(the_board, square + i * UP);
    if (piece ==  white_queen || piece == white_rook)
        return 1;

    i=0;
    while (move_down(square + i * DOWN, the_board, BLACK))
        i++;
    piece = get_piece_in_square(the_board, square + i * DOWN);
    if (piece == white_queen || piece == white_rook)
        return 1;
    
    i=0;
    while (move_right(square + i * RIGHT, the_board, BLACK))
        i++;
    piece = get_piece_in_square(the_board, square + i * RIGHT);
    if (piece == white_queen || piece == white_rook)
        return 1;
    
    i=0;
    while (move_left(square + i * LEFT, the_board, BLACK))
        i++;
    piece = get_piece_in_square(the_board, square + i * LEFT);
    if (piece == white_queen || piece == white_rook)
        return 1;
    
    i=0;
    /* Check danger form diagonals: */
    while (move_up_right(square + i * UP_RIGHT, the_board, BLACK))
        i++;
    piece = get_piece_in_square(the_board, square + i * UP_RIGHT);
    if (piece == white_queen || piece == white_bishop)
        return 1;
    i=0;

    while (move_up_left(square + i * UP_LEFT, the_board, BLACK))
        i++;
    piece = get_piece_in_square(the_board, square + i * UP_LEFT);
    if (piece == white_queen || piece == white_bishop)
        return 1;
    i=0;

    while (move_down_right(square + i * DOWN_RIGHT, the_board, BLACK))
        i++;
    piece = get_piece_in_square(the_board, square + i * DOWN_RIGHT);
    if (piece == white_queen || piece == white_bishop)
        return 1;
    i=0;

    while (move_down_left(square + i * DOWN_LEFT, the_board, BLACK))
        i++;
    piece = get_piece_in_square(the_board, square + i * DOWN_LEFT);
    if (piece == white_queen || piece == white_bishop)
        return 1;
    i=0;

    /* Check danger from knights: */

    /*knight up up right to eat*/
    if (get_column(square) > 0 && get_row(square) > 1) {
        if (get_piece_in_square(the_board, square + KNIGHT_DOWN_DOWN_LEFT) == white_knight)
            return 1;
    }

    /*knight up up left to eat*/
    if (get_column(square) < 7 && get_row(square) > 1) {
        if (get_piece_in_square(the_board, square + KNIGHT_DOWN_DOWN_RIGHT) == white_knight)
            return 1;
    }

    /*knight up right right to eat*/
    if (get_column(square) > 1 && get_row(square) > 0) {
        if (get_piece_in_square(the_board, square + KNIGHT_DOWN_LEFT_LEFT) == white_knight)
            return 1;
    }

    /*knight up left left to eat*/
    if (get_column(square) < 6 && get_row(square) > 0) {
        if (get_piece_in_square(the_board, square + KNIGHT_DOWN_RIGHT_RIGHT) == white_knight)
            return 1;
    }

    /*knight down down right to eat*/
    if (get_column(square) > 0 && get_row(square) < 6) {
        if (get_piece_in_square(the_board, square + KNIGHT_UP_UP_LEFT) == white_knight)
            return 1;
    }

    /*knight down down left to eat*/
    if (get_column(square) < 7 && get_row(square) < 6) {
        if (get_piece_in_square(the_board, square + KNIGHT_UP_UP_RIGHT) == white_knight)
            return 1;
    }

    /*knight down right right to eat*/
    if (get_column(square) > 2 && get_row(square) < 7) {
        if (get_piece_in_square(the_board, square + KNIGHT_UP_LEFT_LEFT) == white_knight)
            return 1;
    }

    /*knight down left left to eat*/
    if (get_column(square) < 6 && get_row(square) < 7) {
        if (get_piece_in_square(the_board, square + KNIGHT_UP_RIGHT_RIGHT) == white_knight)
            return 1;
    }


    /* Check danger from pawns: */
    if (get_piece_in_square(the_board, square + DOWN_RIGHT) == white_pawn)
        return 1;
    
    if (get_piece_in_square(the_board, square + DOWN_LEFT) == white_pawn)
        return 1;


    /* Check danger from king: */
    if (get_piece_in_square(the_board,square + RIGHT) == white_king)
        return 1;

    if (get_piece_in_square(the_board,square + LEFT) == white_king)
        return 1;

    if (get_piece_in_square(the_board,square + UP) == white_king)
        return 1;

    if (get_piece_in_square(the_board,square + DOWN) == white_king)
        return 1;

    if (get_piece_in_square(the_board,square + UP_RIGHT) == white_king)
        return 1;

    if (get_piece_in_square(the_board,square + UP_LEFT) == white_king)
        return 1;

    if (get_piece_in_square(the_board,square + DOWN_LEFT) == white_king)
        return 1;

    if (get_piece_in_square(the_board,square + DOWN_RIGHT) == white_king)
        return 1;



    return 0;
}


char find_king_square(board *the_board, char color){
    int i = 0;
    char piece = white_king;
    if(!color)
        piece = black_king;
    while (get_piece_in_square(the_board,i) != piece) 
        i++;
    return i;
}

void print_board(board *the_board){
    int num = 0;
    int i, x, y, z;
    for(z = 0; z < 2; z++)
            printf(" ");
    for(z = 0; z < 33; z++)
            printf("-");
    printf("\n");
    for(i = 0; i < 8; i++){
        y = NUMBER_OF_SQUARES - (i+1)*8;
        printf("%d ",(8-i));
        for(x = 0; x < 8; x++){
            num = get_piece_in_square(the_board, y + x);
            printf("| %s ", PIECES1[num]);
        }
        printf("|");
        printf("\n");

        for(z = 0; z < 2; z++)
            printf(" ");
        for(z = 0; z < 33; z++)
            printf("-");
        printf("\n");
    }

    for(z = 0; z < 2; z++)
        printf(" ");
    for(i=0; i < 8; i++)
        printf("  %c ", i+'a');
    printf("\n");
}

char check_white_long_castle(board *the_board){
    move temp;
    if(!isAttacked_by_black(the_board, DEAFULT_WHITE_KING_SQUARE)){
        if(the_board->can_white_castle_long 
                && get_piece_in_square(the_board, DEAFULT_WHITE_KING_SQUARE + LEFT) == empty 
                && get_piece_in_square(the_board, DEAFULT_WHITE_KING_SQUARE + LEFT*2) == empty 
                && get_piece_in_square(the_board, DEAFULT_WHITE_KING_SQUARE + LEFT*3) == empty){
            temp = create_a_move(DEAFULT_WHITE_KING_SQUARE, DEAFULT_WHITE_KING_SQUARE + LEFT, 0, 0, 0);
            if(is_move_valid(*the_board, temp, WHITE)){
                    temp = create_a_move(DEAFULT_WHITE_KING_SQUARE, DEAFULT_WHITE_KING_SQUARE + LEFT*2, 0, 1, 0);
                    if(is_move_valid(*the_board, temp, WHITE)){
                        return 1;
                    }
                }
        }
    }
    return 0;
}

char check_white_short_castle(board *the_board){
    move temp;
    if(!isAttacked_by_black(the_board, DEAFULT_WHITE_KING_SQUARE)){
        if(the_board->can_white_castle_short 
                && get_piece_in_square(the_board, DEAFULT_WHITE_KING_SQUARE + RIGHT) == empty
                && get_piece_in_square(the_board, DEAFULT_WHITE_KING_SQUARE + RIGHT*2) == empty){
            temp = create_a_move(DEAFULT_WHITE_KING_SQUARE, DEAFULT_WHITE_KING_SQUARE + RIGHT, 0, 0, 0);
            if(is_move_valid(*the_board, temp, WHITE)){
                    temp = create_a_move(DEAFULT_WHITE_KING_SQUARE, DEAFULT_WHITE_KING_SQUARE + RIGHT*2, 0, 0, 1);
                    if(is_move_valid(*the_board, temp, WHITE)){
                        return 1;
                    }
                }
        }
    }
    return 0;
}

char check_black_long_castle(board *the_board){
    move temp;
    if(!isAttacked_by_white(the_board, DEAFULT_BLACK_KING_SQUARE)){
        if(the_board->can_black_castle_long
                && get_piece_in_square(the_board, DEAFULT_BLACK_KING_SQUARE + LEFT) == empty
                && get_piece_in_square(the_board, DEAFULT_BLACK_KING_SQUARE + LEFT * 2) == empty
                && get_piece_in_square(the_board, DEAFULT_BLACK_KING_SQUARE + LEFT * 3) == empty){
            temp = create_a_move(DEAFULT_BLACK_KING_SQUARE, DEAFULT_BLACK_KING_SQUARE + LEFT, 0, 0, 0);
            if(is_move_valid(*the_board, temp, BLACK)){
                temp = create_a_move(DEAFULT_BLACK_KING_SQUARE, DEAFULT_BLACK_KING_SQUARE + LEFT * 2, 0, 1, 0);
                if(is_move_valid(*the_board, temp, BLACK)){
                    return 1;
                }
            }
        }
    }
    return 0;
}

char check_black_short_castle(board *the_board){
    move temp;
    if(!isAttacked_by_white(the_board, DEAFULT_BLACK_KING_SQUARE)){
        if(the_board->can_black_castle_short 
                && get_piece_in_square(the_board, DEAFULT_BLACK_KING_SQUARE + RIGHT) == empty
                && get_piece_in_square(the_board, DEAFULT_BLACK_KING_SQUARE + RIGHT*2) == empty){
            temp = create_a_move(DEAFULT_BLACK_KING_SQUARE, DEAFULT_BLACK_KING_SQUARE + RIGHT, 0, 0, 0);
            if(is_move_valid(*the_board, temp, BLACK)){
                    temp = create_a_move(DEAFULT_BLACK_KING_SQUARE, DEAFULT_BLACK_KING_SQUARE + RIGHT*2, 0, 0, 1);
                    if(is_move_valid(*the_board, temp, BLACK)){
                        return 1;
                    }
                }
        }
    }
    return 0;
}