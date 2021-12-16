#ifndef EE025185_6380_4B7E_AEF0_4F6D62B6980A
#define EE025185_6380_4B7E_AEF0_4F6D62B6980A
#include <stdio.h>

#include "board_struct.h"
#include "useful_functions.h"
#include "possible_moves.h"


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
void commit_a_move_for_white(board * b, move m);

/* A function that receives a move of the black and executes it*/
void commit_a_move_for_black(board * b, move m);



#endif /* EE025185_6380_4B7E_AEF0_4F6D62B6980A */
