#include "board_struct.h"
#include <stdlib.h>

typedef unsigned short int move;

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

/* The function commit a short castle for white */
void commit_a_short_castle_for_white(board * b);

/* The function commit a long castle for white */
void commit_a_long_castle_for_white(board * b);

/* The function commit an en passant for white */
void commit_en_passant_for_white(board * b, unsigned char src_loc, unsigned char dst_loc);

/* The function commit a promotion for white */
void commit_promotion_for_white(board * b, unsigned char src_loc, unsigned char dst_loc, unsigned char what_to_promote_to);

/* The function commit a short castle for black */
void commit_a_short_castle_for_black(board * b);

/* The function commit a long castle for black */
void commit_a_long_castle_for_black(board * b);

/* The function commit an en passant for black */
void commit_en_passant_for_black(board * b, unsigned char src_loc, unsigned char dst_loc);

/* The function commit a promotion for black */
void commit_promotion_for_black(board * b, unsigned char src_loc, unsigned char dst_loc, unsigned char what_to_promote_to);

/* A function that receives a move of the white and executes it*/
void commit_a_regular_move_for_white(board * b, move m);

/* A function that receives a move of the black and executes it*/
void commit_a_regular_move_for_black(board * b, move m);

