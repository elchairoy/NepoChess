#include <stdio.h>
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
/* This function tests the functions get_piece_in_square and change_the_square.
   If there is and error, prints an error message and returns 1, otherwise returns 0. */
int test_useful_functions();
