#include "board_struct.h"
#include <stdlib.h>

/* Gives the piece in the given square.
   If there is an error - returns -1. */
char get_piece_in_square(board ,unsigned char);

/* Change the piece in the given square to the given piece.
   If there is an error - returns -1. */
char change_the_square(board ,unsigned char ,char );

short create_a_move(unsigned char ,unsigned char ,unsigned char ,unsigned char ,unsigned char );

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

