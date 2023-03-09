#ifndef AFD0BF27_C006_46B4_89E6_171B4DC00121
#define AFD0BF27_C006_46B4_89E6_171B4DC00121

#include "string.h"
#include "board_struct.h"
#include "possible_moves.h"
#include "useful_functions.h"
#include "make_move.h"
#include "minimax.h"
#include "evaluation.h"

char fen_to_board(char *fen, board *b); 
void bot_move(game *the_game);
int check_endgame(game *the_game);
char translate_promotion(char promotion);
int check_src(board *the_board, char src);
char uci_parse(game *the_game, char is_game_on);
int uci_main();
int player_move(game *the_game, char *str);
char translate_piece_symbol(char piece_symbol);
void moves_in_depth(char d,board *b,move *all_moves_last_move, move last_move, irreversible_move_info inf);
void create_game(game *g, board *initial_position);
void setup_start_board(board *b); 


#endif /* AFD0BF27_C006_46B4_89E6_171B4DC00121 */
