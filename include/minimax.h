#ifndef BOARD_STRUCTS
#define BOARD_STRUCTS
#include "board_struct.h"
#endif

#ifndef USEFUL_FUNCTIONS
#define USEFUL_FUNCTIONS
#include "useful_functions.h"
#endif

#ifndef MAKE_MOVE
#define MAKE_MOVE
#include "make_move.h"
#endif

#ifndef POSSIBLE_MOVES
#define POSSIBLE_MOVES
#include "possible_moves.h"
#endif

#ifndef EVALUATION
#define EVALUATION
#include "evaluation.h"
#endif

char evaluate_minimax_for_white(board b, char depth);
char evaluate_minimax_for_black(board b, char depth);
move minimax_for_white(board *b,char depth);
move minimax_for_black(board *b,char depth);