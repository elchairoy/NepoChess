#ifndef AFD0BF27_C006_46B4_89E6_171B4DC00121
#define AFD0BF27_C006_46B4_89E6_171B4DC00121

#include "string.h"
#include "board_struct.h"
#include "possible_moves.h"
#include "useful_functions.h"
#include "make_move.h"
#include "minimax.h"
#include "evaluation.h"

int check(char color);
int game(board *the_board, HashTable *ht, char color);
int check_src(board *the_board, char src);
void bot_move(board *the_board, HashTable *ht);
int check_endgame(board *the_board);
int get_player_promotion_choice();
char translate_promotion(char promotion);
char uci_parse(board *b, HashTable *ht);
int uci_main();
int player_move(board *the_board, char *move_str);
char translate_piece_symbol(char piece_symbol);
void moves_in_depth(char d, board *b);
void setup_start_board(board *b); 


#endif /* AFD0BF27_C006_46B4_89E6_171B4DC00121 */
