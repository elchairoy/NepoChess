#ifndef BE5F1FF0_4F72_47C7_8DFE_407829A022EA
#define BE5F1FF0_4F72_47C7_8DFE_407829A022EA

#include "board_struct.h"
#include "useful_functions.h"
#include "make_move.h"
#include "possible_moves.h"
#include "evaluation.h"
#include "hashtable.h"

char evaluate_minimax_for_white(board *b, char depth,char pre_frontier, HashTable *ht);
char evaluate_minimax_for_black(board *b, char depth,char pre_frontier, HashTable *ht);
move get_best_move_white(board *b,char depth, char pre_frontier, HashTable *ht);
move get_best_move_black(board *b,char depth, char pre_frontier, HashTable *ht);


#endif /* BE5F1FF0_4F72_47C7_8DFE_407829A022EA */
