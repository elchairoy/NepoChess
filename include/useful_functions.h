#ifndef AE5BDBF7_77C4_4AB2_867A_1994FFAC6C77
#define AE5BDBF7_77C4_4AB2_867A_1994FFAC6C77

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "possible_moves.h"
#include "board_struct.h"
#include "make_move.h"


/* Gives the piece in the given square.
   If there is an error - returns -1. */
char get_piece_in_square(board *b ,unsigned char square_number);

/* Change the piece in the given square to the given piece.
   If there is an error - returns -1. */
void change_the_square(board *b,unsigned char square_number ,char new_piece);

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

char isAttacked_by_black(board *the_board, char square);

char isAttacked_by_white(board *the_board, char square);

char find_king_square(board *the_board, char color);

void print_board(board *the_board);

char check_white_long_castle(board *the_board);

char check_white_short_castle(board *the_board);

char check_black_long_castle(board *the_board);

char check_black_short_castle(board *the_board);

char *strrev(char *str);

#endif /* AE5BDBF7_77C4_4AB2_867A_1994FFAC6C77 */
