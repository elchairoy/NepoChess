/*
 Created by meir on 30/11/2021.
*/
#include "useful_functions.h"

#define MASK_FOR_A_HALF 0x0f /* A mask to get only a half of a byte. */
#define MASK_FOR_6BITS 0x00fd /* A mask to get only 6 bits of a short. */
#define MASK_FOR_2BITS 0xd0fd /* A mask to get only 2 bits of a short. */

#define SRC_LOC_INDEX 0 /* The place of the source square in the short. */
#define DST_LOC_INDEX 6 /* The place of the destination square in the short. */
#define PROMOTE_TO_INDEX 12 /* The place of the 'promote to what' in the short. */
#define IS_LONG_CASTLE 14 /* The place of the 'is long castle' in the short. */
#define IS_SHORT_CASTLE 15 /* The place of the 'is short castle' in the short. */


typedef unsigned short int move;

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
    result |= (castle_long << IS_LONG_CASTLE); /* Enters if it's a long castle. */
    result |= (castle_short << IS_SHORT_CASTLE); /* Enters if it's a short castle. */

    return result;
}

/* This function gets a move and returns the src square */
char get_src_square(move m) {
    return (m & (MASK_FOR_6BITS << SRC_LOC_INDEX)) >> SRC_LOC_INDEX;
}

/* This function gets a move and returns the src square */
char get_dst_square(move m) {
    return (m & (MASK_FOR_6BITS << DST_LOC_INDEX)) >> DST_LOC_INDEX;
}

/* This function gets a move and returns what to promote to */
char get_promotion_choice(move m) {
    return (m & (MASK_FOR_6BITS << PROMOTE_TO_INDEX)) >> PROMOTE_TO_INDEX;
}

/* This function gets a move and returns if it's a long castle */
char get_is_long_castle(move m) {
    return (m & (MASK_FOR_6BITS << IS_LONG_CASTLE)) >> IS_LONG_CASTLE;
}

/* This function gets a move and returns if it's a short castle */
char get_is_short_castle(move m) {
    return (m & (MASK_FOR_6BITS << IS_SHORT_CASTLE)) >> IS_SHORT_CASTLE;
}