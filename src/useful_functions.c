/*
 Created by meir on 30/11/2021.
*/
#include "useful_functions.h"

#define MASK_FOR_A_HALF 0x0f /* A mask to get only a half of a byte. */

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

short create_a_move(unsigned char src_loc,unsigned char dst_loc,unsigned char promote_to,unsigned char castle_long,unsigned char castle_short) {
    move result = 0;
    if (src_loc >= NUMBER_OF_SQUARES || src_loc >= NUMBER_OF_SQUARES || promote_to >= 4 || castle_long >= 2 || castle_short >= 2) /* */
        return -1;
    result |= src_loc;
    result |= (dst_loc << 6); /* Fill it in the next 6 bits. */
    result |= (promote_to << 12);
    result |= (castle_long << 14);
    result |= (castle_short << 15);

    return result;
}
