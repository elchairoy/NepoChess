#ifndef BE5F1FF0_4F72_47C7_8DFE_407829A022EA
#define BE5F1FF0_4F72_47C7_8DFE_407829A022EA

#include "board_struct.h"
#include "useful_functions.h"
#include "make_move.h"
#include "possible_moves.h"
#include "evaluation.h"
#include "hashtable.h"

double evaluate_minimax_for_white(game *b, move *all_moves_last_move, move last_move, irreversible_move_info inf, char depth ,double alpha, double beta);
double evaluate_minimax_for_black(game *b, move *all_moves_last_move, move last_move, irreversible_move_info inf, char depth, double alpha, double beta);
move get_best_move_white(game *b,char depth, move *all_moves_already_calculated);
move get_best_move_black(game *b,char depth, move *all_moves_already_calculated);


#endif /* BE5F1FF0_4F72_47C7_8DFE_407829A022EA */
