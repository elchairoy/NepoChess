#ifndef DF067538_D9C3_4DB6_9FA4_0090105C00B0
#define DF067538_D9C3_4DB6_9FA4_0090105C00B0
#include <stdio.h>

#include "board_struct.h"
#include "useful_functions.h"

/* This function evaluates the position only by the points of the pieces. */
char evaluate_by_points(board *b);
char number_of_white_developed_pieces(board *b);
char number_of_black_developed_pieces(board *b);

#endif /* DF067538_D9C3_4DB6_9FA4_0090105C00B0 */
