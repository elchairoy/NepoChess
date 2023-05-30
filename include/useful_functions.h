#ifndef AE5BDBF7_77C4_4AB2_867A_1994FFAC6C77
#define AE5BDBF7_77C4_4AB2_867A_1994FFAC6C77

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "possible_moves.h"
#include "board_struct.h"
#include "make_move.h"

#define MASK_FOR_A_HALF 0x0f /* A mask to get only a half of a byte. */
#define MASK_FOR_6BITS 0x003f /* A mask to get only 6 bits of a short. */
#define MASK_FOR_2BITS 0x0003 /* A mask to get only 2 bits of a short. */

#define SRC_LOC_INDEX 0 /* The place of the source square in the short. */
#define DST_LOC_INDEX 6 /* The place of the destination square in the short. */
#define PROMOTE_TO_INDEX 12 /* The place of the 'promote to what' in the short. */
#define IS_LONG_CASTLE_INDEX 14 /* The place of the 'is long castle' in the short. */
#define IS_SHORT_CASTLE_INDEX 15 /* The place of the 'is short castle' in the short. */

#define PIECE_TAKEN_INDEX 0 /* The place of the piece taken in the char (irrev move info). */
#define IS_PROMOTED_INDEX 6 /* The place of the is_promoted bit in the char (irrev move info). */
#define IS_EN_PASSANT_INDEX 7 /* The place of the is_en_passant bit in the char (irrev move info). */
#define EN_PASSANT_PAWN_INDEX 8 /* The place of the en passant pwan of the last move in the char (irrev move info). */
#define COULD_WHITE_SHORT_CASTLE_INDEX 14 /* The place of the could_white_short_castle bit in the char (irrev move info). */
#define COULD_WHITE_LONG_CASTLE_INDEX 15 /* The place of the could_white_long_castle bit in the char (irrev move info). */
#define COULD_BLACK_SHORT_CASTLE_INDEX 16 /* The place of the could_black_short_castle bit in the char (irrev move info). */
#define COULD_BLACK_LONG_CASTLE_INDEX 17 /* The place of the could_black_long_castle bit in the char (irrev move info). */

/* This macro gets a move and returns the src square */
#define get_src_square(m) ((m & (MASK_FOR_6BITS << SRC_LOC_INDEX)) >> SRC_LOC_INDEX)

/* This macro gets a move and returns the dst square */
#define get_dst_square(m) ((m & (MASK_FOR_6BITS << DST_LOC_INDEX)) >> DST_LOC_INDEX)

/* This macro gets a move and returns what to promote to */
#define get_promotion_choice(m) ((m & (MASK_FOR_2BITS << PROMOTE_TO_INDEX)) >> PROMOTE_TO_INDEX)

/* This macro gets a move and returns if it's a long castle */
#define get_is_long_castle(m) ((m & (1 << IS_LONG_CASTLE_INDEX)) >> IS_LONG_CASTLE_INDEX)

/* This macro gets a move and returns if it's a short castle */
#define get_is_short_castle(m) ((m & (1 << IS_SHORT_CASTLE_INDEX)) >> IS_SHORT_CASTLE_INDEX)

/* This macro gets an irreversible move info and returns the piece taken in the move */
#define get_piece_taken(move_info) ((move_info & (MASK_FOR_6BITS << PIECE_TAKEN_INDEX)) >> PIECE_TAKEN_INDEX)

/* This macro gets an irreversible move info and returns if the move is a promotion */
#define get_is_promoted(move_info) ((move_info & (1 << IS_PROMOTED_INDEX)) >> IS_PROMOTED_INDEX)

/* This macro gets an irreversible move info and returns if the move is an en passant */
#define get_is_en_passant(move_info) ((move_info & (1 << IS_EN_PASSANT_INDEX)) >> IS_EN_PASSANT_INDEX)

/* This macro gets an irreversible move info and returns the en passant pawn of the last move */
#define get_en_passant_pawn_last_move(move_info) ((move_info & (MASK_FOR_6BITS << EN_PASSANT_PAWN_INDEX)) >> EN_PASSANT_PAWN_INDEX)

/* This macro gets an irreversible move info and returns if white could make a short castle before the move */
#define get_could_white_short_castle_last_move(move_info) ((move_info & (1 << COULD_WHITE_SHORT_CASTLE_INDEX)) >> COULD_WHITE_SHORT_CASTLE_INDEX)

/* This macro gets an irreversible move info and returns if white could make a long castle before the move */
#define get_could_white_long_castle_last_move(move_info) ((move_info & (1 << COULD_WHITE_LONG_CASTLE_INDEX)) >> COULD_WHITE_LONG_CASTLE_INDEX)

/* This macro gets an irreversible move info and returns if black could make a short castle before the move */
#define get_could_black_short_castle_last_move(move_info) ((move_info & (1 << COULD_BLACK_SHORT_CASTLE_INDEX)) >> COULD_BLACK_SHORT_CASTLE_INDEX)

/* This macro gets an irreversible move info and returns if black could make a long castle before the move */
#define get_could_black_long_castle_last_move(move_info) ((move_info & (1 << COULD_BLACK_LONG_CASTLE_INDEX)) >> COULD_BLACK_LONG_CASTLE_INDEX)


/* This macro gets the data needed for a move and returns a short representing the move.*/
#define create_a_move(the_move, src_loc, dst_loc, promote_to,castle_long, castle_short)\
    (the_move) = 0; \
    (the_move) |= ((src_loc) << SRC_LOC_INDEX); \
    (the_move) |= ((dst_loc) << DST_LOC_INDEX); \
    (the_move) |= ((promote_to) << PROMOTE_TO_INDEX); \
    (the_move) |= ((castle_long) << IS_LONG_CASTLE_INDEX); \
    (the_move) |= ((castle_short) << IS_SHORT_CASTLE_INDEX);

/* This macro gets the data needed for a move and returns a short representing the move.*/
#define create_a_irrev_move_info(the_move_info, piece_taken, is_promoted, is_en_passant, en_passant_pawn_last_move, could_white_short_castle, could_white_long_castle, could_black_short_castle, could_black_long_castle)\
    (the_move_info) = 0; \
    (the_move_info) |= ((piece_taken) << PIECE_TAKEN_INDEX); \
    (the_move_info) |= ((is_promoted) << IS_PROMOTED_INDEX); \
    (the_move_info) |= ((is_en_passant) << IS_EN_PASSANT_INDEX); \
    (the_move_info) |= ((en_passant_pawn_last_move) << EN_PASSANT_PAWN_INDEX); \
    (the_move_info) |= ((could_white_short_castle) << COULD_WHITE_SHORT_CASTLE_INDEX); \
    (the_move_info) |= ((could_white_long_castle) << COULD_WHITE_LONG_CASTLE_INDEX); \
    (the_move_info) |= ((could_black_short_castle) << COULD_BLACK_SHORT_CASTLE_INDEX); \
    (the_move_info) |= ((could_black_long_castle) << COULD_BLACK_LONG_CASTLE_INDEX);

/* Gives the piece in the given square.
   If there is an error - returns -1. */
char get_piece_in_square(board *b ,unsigned char square_number);

/* Change the piece in the given square to the given piece.
   If there is an error - returns -1. */
void change_the_square(board *b,unsigned char square_number ,char new_piece);

char is_attacked_by_black(board *the_board, char square);

char is_attacked_by_white(board *the_board, char square);

char compare_boards(board *board1, board *board2);

char find_king_square(board *the_board, char color);

void print_board(board *the_board);

void print_move(move the_move);

char check_white_long_castle(board *the_board);

char check_white_short_castle(board *the_board);

char check_black_long_castle(board *the_board);

char check_black_short_castle(board *the_board);

char *strrev(char *str);

char is_in_array(char *array, char value);

irreversible_move_info get_irrev_move_info(board *b, move m);

void unmake_move_in_board(board *b, move m, irreversible_move_info inf);

void unmake_move_in_game(game *the_game, move m, irreversible_move_info inf);

char check_repetition(game *the_game);

void selection_sort_for_moves(move moves[MAX_POSSIBLE_MOVES / 2], int *values, int k);

#endif /* AE5BDBF7_77C4_4AB2_867A_1994FFAC6C77 */
