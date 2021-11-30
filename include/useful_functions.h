#include "board_struct.h"

/* Gives the piece in the given square.
   If there is an error - returns -1. */
char get_piece_in_square(board *b ,unsigned char square_number);

/* Change the piece in the given square to the given piece.
   If there is an error - returns -1. */
char change_the_square(board *b,unsigned char square_number ,char new_piece);
