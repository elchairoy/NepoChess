#ifndef BE5F1FF0_4F72_47C7_8DFE_407829A022EA
#define BE5F1FF0_4F72_47C7_8DFE_407829A022EA

#include "board_struct.h"
#include "useful_functions.h"
#include "make_move.h"
#include "possible_moves.h"
#include "evaluation.h"
#include "hashtable.h"

double evaluate_minimax_for_white(board *b, move *all_moves_last_move, move last_move, irreversible_move_info inf, char depth ,double alpha, double beta, HashTable *ht);
double evaluate_minimax_for_black(board *b, move *all_moves_last_move, move last_move, irreversible_move_info inf, char depth, double alpha, double beta, HashTable *ht);
move get_best_move_white(board *b,char depth, move *all_moves_already_calculated, HashTable *ht);
move get_best_move_black(board *b,char depth, move *all_moves_already_calculated, HashTable *ht);


#endif /* BE5F1FF0_4F72_47C7_8DFE_407829A022EA */
