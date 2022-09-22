#ifndef AFD0BF27_C006_46B4_89E6_171B4DC00121
#define AFD0BF27_C006_46B4_89E6_171B4DC00121

#include "string.h"
#include "board_struct.h"
#include "possible_moves.h"
#include "useful_functions.h"
#include "make_move.h"
#include "minimax.h"

int check();
int game(board *the_board, HashTable *ht);
int check_src(board *the_board, char src, char the_move);
void bot_move(board *the_board, HashTable *ht, int color);
int check_endgame(board *the_board, int color);
int get_player_promotion_choice();



#endif /* AFD0BF27_C006_46B4_89E6_171B4DC00121 */
