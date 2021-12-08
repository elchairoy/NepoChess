/*
 Created by meir on 30/11/2021.
*/
#include "useful_functions.h"
#include <stdio.h>

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

/* The function commit a short castle for white */
    void commit_a_short_castle_for_white(board * board1){
        change_the_square(board1, 4, empty); /* It changes the white king place to empty */ 
        change_the_square(board1, 7, empty); /* It changes the white rook place to empty */
        change_the_square(board1, 6, white_king); /* It puts the white king in his place */
        change_the_square(board1, 5, white_rook); /* It puts the white rook in his place */
    }

    /* The function commit a long castle for white */
    void commit_a_long_castle_for_white(board * board1){
        change_the_square(board1, 4, empty); /* It changes the white king place to empty */
        change_the_square(board1, 0, empty); /* It changes the white rook place to empty */
        change_the_square(board1, 2, white_king); /* It puts the white king in his place */
        change_the_square(board1, 3, white_rook); /* It puts the white rook in his place */
    }

    /* The function commit an en passant for white */
    void commit_en_passant_for_white(board * board1, unsigned char src_loc, unsigned char dst_loc){

        change_the_square(board1, src_loc, empty); /* It changes the white pawn place to empty */
        change_the_square(board1, dst_loc, white_pawn); /* It puts the white pawn in his place */ 
        change_the_square(board1, dst_loc - 8, empty); /* It changes the black pawn place to empty */
    }

    /* The function commit a promotion for white */
    void commit_promotion_for_white(board * board1, unsigned char src_loc, unsigned char dst_loc, unsigned char what_to_promote_to){
        change_the_square(board1, src_loc, empty); /* Change the src loc to empty */
        if (what_to_promote_to == promote_to_queen) change_the_square(board1, dst_loc, white_queen); /* promote to queen */
        else if (what_to_promote_to == promote_to_rook) change_the_square(board1, dst_loc, white_rook); /* promote to rook */
        else if(what_to_promote_to == promote_to_knight) change_the_square(board1, dst_loc, white_knight); /* promote to knight */
        else change_the_square(board1, dst_loc, white_bishop); /* promote to bishop */
    }

    /* The function commit a short castle for black */
    void commit_a_short_castle_for_black(board * board1){
        change_the_square(board1, 60, empty); /* It changes the black king place to empty */
        change_the_square(board1, 63, empty); /* It changes the black rook place to empty */
        change_the_square(board1, 62, black_king); /* It puts the black king in his place */
        change_the_square(board1, 61, black_rook); /* It puts the black rook in his place */
    }

    /* The function commit a long castle for black */
    void commit_a_long_castle_for_black(board * board1){
        change_the_square(board1, 60, empty); /* It changes the black king place to empty */
        change_the_square(board1, 56, empty); /* It changes the black rook place to empty */
        change_the_square(board1, 58, black_king); /* It puts the black king in his place */
        change_the_square(board1, 59, black_rook); /* It puts the black rook in his place */
    }

    /* The function commit an en passant for black */
    void commit_en_passant_for_black(board * board1, unsigned char src_loc, unsigned char dst_loc){
        change_the_square(board1, src_loc, empty); /* It changes the black pawn place to empty */
        change_the_square(board1, dst_loc, black_pawn); /* It puts the black pawn in his place */ 
        change_the_square(board1, dst_loc + 8, empty); /* It changes the white pawn place to empty */
    }

    /* The function commit a promotion for black */
    void commit_promotion_for_black(board * board1, unsigned char src_loc, unsigned char dst_loc, unsigned char what_to_promote_to){
        change_the_square(board1, src_loc, empty); /* Change the src loc to empty */
        if (what_to_promote_to == promote_to_queen) change_the_square(board1, dst_loc, black_queen); /* promote to queen */
        else if (what_to_promote_to == promote_to_rook) change_the_square(board1, dst_loc, black_rook); /* promote to rook */
        else if(what_to_promote_to == promote_to_knight) change_the_square(board1, dst_loc, black_knight); /* promote to knight */
        else change_the_square(board1, dst_loc, black_bishop); /* promote to bishop */
    }


    /* A function that receives a move of the white and executes it*/
    void commit_a_regular_move_for_white(board * board1, move m){
    unsigned char src_loc = get_src_square(m); /* The src square */
    unsigned char dst_loc = get_dst_square(m); /* The dst square */
    char first_piece = get_piece_in_square(board1, src_loc); /* It gets the sole in the src square */
    if (get_is_short_castle(m) == 1) /* If this move is a short castle */ 
        commit_a_short_castle_for_white(board1); /* Commit a short castle for white */
    
    else if (get_is_long_castle(m) == 1) /* If this move is a long castle */
        commit_a_long_castle_for_white(board1); /* Commit a long castle for white */
    
    else if ((dst_loc == (src_loc + 9) || dst_loc == (src_loc + 7)) && (first_piece == white_pawn) && (get_piece_in_square(board1, dst_loc) == empty)) /* if en passant exist */
        commit_en_passant_for_white(board1, src_loc, dst_loc);
    
    else if (first_piece == white_pawn && (dst_loc / 8) == 7)
        commit_promotion_for_white(board1, src_loc, dst_loc, get_promotion_choice(m));
    
    else
    { 
        change_the_square(board1, src_loc, empty); /* It changes the src square to empty */
        change_the_square(board1, dst_loc, first_piece); /* It changes the dst square to the "first piece" */
    }
    
    
}

/* A function that receives a move of the black and executes it*/
void commit_a_regular_move_for_black(board * board1, move m){
    unsigned char src_loc = get_src_square(m); /* The src square */
    unsigned char dst_loc = get_dst_square(m); /* The dst square */
    char first_piece = get_piece_in_square(board1, src_loc); /* It gets the sole in the src square */
    if (get_is_short_castle(m) == 1) /* If this move is a short castle */ 
        commit_a_short_castle_for_black(board1);
    
    else if (get_is_long_castle(m) == 1) /* If this move is a long castle */
        commit_a_long_castle_for_black(board1);
    
    else if ((dst_loc == (src_loc - 9) || dst_loc == (src_loc - 7)) && (first_piece == black_pawn) && (get_piece_in_square(board1, dst_loc) == empty)) /* if en passant exist */
        commit_en_passant_for_black(board1, src_loc, dst_loc);
    
    else if(first_piece == black_pawn && (dst_loc / 8) == 0)
        commit_promotion_for_black(board1, src_loc, dst_loc, get_promotion_choice(m));
    
    else
    {
    change_the_square(board1, src_loc, empty); /* It changes the src square to empty */
    change_the_square(board1, dst_loc, first_piece); /* It changes the dst square to the "first piece" */
    }

    
}