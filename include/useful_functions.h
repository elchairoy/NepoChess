#include <stdlib.h>
#include <stdio.h>
#ifndef BOARD_STRUCTS
#define BOARD_STRUCTS
#include "board_struct.h"
#endif

/* Gives the piece in the given square.
   If there is an error - returns -1. */
char get_piece_in_square(board *b ,unsigned char square_number);

/* Change the piece in the given square to the given piece.
   If there is an error - returns -1. */
char change_the_square(board *b,unsigned char square_number ,char new_piece);

/* This function gets the data needed for a move and returns a short representing the move.
   If the data is invalid - returns -1. */
short create_a_move(unsigned char src_loc,unsigned char dst_loc,unsigned char promote_to,unsigned char castle_long,unsigned char castle_short);

/* This function gets a move and returns the src square */
char get_src_square(move m);

/* This function gets a move and returns the src square */
char get_dst_square(move m);

/* This function gets a move and returns what to promote to */
char get_promotion_choice(move m);

/* This function gets a move and returns if it's a long castle */
char get_is_long_castle(move m);

/* This function gets a move and returns if it's a short castle */
char get_is_short_castle(move m);
