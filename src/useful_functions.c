/*
 Created by meir on 30/11/2021.
*/
#include <stdio.h>
#include <stdlib.h>
#include "board_struct.h"

#define mask_for_first_half 0xf0 /* A mask to clear the first half of the byte. */
#define mask_for_second_half 0x0f /* A mask to clear the second half of the byte. */

/* Gives the piece in the given square. */
char get_piece_in_square(board *b ,unsigned char square_number) {
    if (square_number >= 64 || b->squares == NULL) /* If there is an error: */
        return -1;

    if (square_number % 2 == 1) /* If the square is in the first half a byte: */
        return (b->squares[square_number/2] & mask_for_second_half) /* - clears the second half. */;
        
    else /* If the square is in the second half a byte: */
        return (b->squares[square_number/2] & mask_for_first_half) /* - clears the first half */ >> 4 /* - shifts it to the first half. */;
}

/* Change the piece in the given square to the given piece. */
char change_the_square(board *b,unsigned char square_number ,char new_piece) {
    if (square_number >= 64 || b->squares == NULL) /* If there is an error: */
        return -1;
        
    if (square_number % 2 == 1) /* If the square is in the first half a byte: */
        b->squares[square_number / 2] = (b->squares[square_number / 2] & mask_for_first_half) /* - clears the first half */ | (new_piece) /* - places the new piece in the first half */;
    
    else /* If the square is in the second half a byte: */
        b->squares[square_number / 2] = (b->squares[square_number / 2] & mask_for_second_half) /* - clears the second half */ | (new_piece << 4) /* - places the new piece in the second half */;
    return 0;
}
