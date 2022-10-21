#ifndef DA695DC0_90E2_40B5_BC05_F55A01BC0605
#define DA695DC0_90E2_40B5_BC05_F55A01BC0605


#include "board_struct.h"
#include "useful_functions.h"
#include "make_move.h"

#include <stdio.h>
#define DEAFULT_WHITE_KING_SQUARE 4
#define DEAFULT_BLACK_KING_SQUARE 60
#define PAWN_MAX_MOVES 4 /*max squres pawn can go to in one turn*/
#define QUEEN_MAX_MOVES 27 /*as well*/
#define KING_MAX_MOVES 8 /*as well*/
#define BISHOP_MAX_MOVES 13 /*as well*/
#define KNIGHT_MAX_MOVES 8 /*as well*/
#define ROOK_MAX_MOVES 14 /*as well*/
#define END 0 /*sign for the end of the array*/
#define get_column(square) (square % NUMBER_OF_COLUMNS) /*get the column of a square*/
#define get_row(square) (square / NUMBER_OF_ROWS) /*get a row of a square*/
#define UP_RIGHT (UP + RIGHT) /*up in a diagonal to the left*/
#define UP_LEFT (UP + LEFT) /*up... to the right*/
#define DOWN_RIGHT (DOWN + RIGHT) /*down...right*/
#define DOWN_LEFT (DOWN + LEFT) /*down...left*/
#define MAX_MOVES 7/*max moves of a liner peice to any side*/
#define WHITE 1 /*white is true*/
#define BLACK 0 /*black is false (I know it's Racist but I don't care so live with it)*/
#define NUM_OF_WHITE_PIECES 6
/*every move of the knight the name is the move in squres - up up right means 1 up then another 1 up then to the left
and the number is the cal of the amount of squares he passes*/
#define KNIGHT_UP_UP_RIGHT (UP + UP + RIGHT)
#define KNIGHT_UP_UP_LEFT (UP + UP + LEFT)
#define KNIGHT_UP_RIGHT_RIGHT (UP + RIGHT + RIGHT)
#define KNIGHT_UP_LEFT_LEFT (UP + LEFT + LEFT)
#define KNIGHT_DOWN_DOWN_RIGHT (DOWN + DOWN + RIGHT)
#define KNIGHT_DOWN_DOWN_LEFT (DOWN + DOWN + LEFT)
#define KNIGHT_DOWN_RIGHT_RIGHT (DOWN + RIGHT + RIGHT)
#define KNIGHT_DOWN_LEFT_LEFT (DOWN + LEFT + LEFT)
/*4 func to cal if peice is getting off board in hes move*/
char pass_left(char src);
char pass_right(char src);
char pass_down(char src);
char pass_up(char src);

/*check if peice will get on a square that an ally is on which means he can't*/
char colid_with_ally(char dst, board *the_board, char color);

/*check if peice is on a square that an enemy is on which means he can't continue*/
char colid_with_enemy(char src, board *the_board, char color);

/*3 func to check if the pawn by his color can move and if so to where*/
char pawn_straight(char src, board *the_board, char color);
char pawn_eat_left(char src, board *the_board, char color);
char pawn_eat_right(char src, board *the_board, char color);

/*8 func to return if the peice can move to any of his 8 sides (if the peice itself can of course)*/
char move_up(char src, board *the_board, char color);
char move_down(char src, board *the_board, char color);
char move_left(char src, board *the_board, char color);
char move_right(char src, board *the_board, char color);
char move_up_left(char src, board *the_board, char color);
char move_up_right(char src, board *the_board, char color);
char move_down_left(char src, board *the_board, char color);
char move_down_right(char src, board *the_board, char color);

/*func to return for the rook and partly for the queen their move list in straight lines - left right up and down*/
int move_in_straight_lines(char square, board *the_board, char color, move *moves);

/*this one returns the list of moves in diagonal lines - up_right up_left etc.*/
int move_in_diagonal_lines(char square, board *the_board, char color, move *moves);

/*returns the rook moves list*/
int rook(char square, board *the_board, char color, move *moves);

/*returns the bishop moves list*/
int bishop(char square, board *the_board, char color, move *moves);

/*creats 2 lists 1 for striaght lins and one for diagonal and conects them to one which is the final*/
int queen(char square, board *the_board, char color, move *moves);

/*checks every possible move of the king out of 8*/
int king(char square, board *the_board, char color, move *moves);

/*checks every possible move of the king out of 8*/
int knight(char square, board *the_board, char color, move *moves);

/*checks every special move the pawn can do exept for the usual on which also gets checked but its minor, anyway there is 2 func
because the pawn for each color moves only in one diriction and its the exact oppised of the other*/
int whitepawn(char square, board *the_board, move *moves);
int blackpawn(char square, board *the_board, move *moves);

/*calls the right func for the peice it was asked to check*/
char moves_of_piece(char square, board *the_board, move * moves);
char color_of_piece(char square, board *the_board);
char is_move_valid(board *the_board, move the_move, char color);
/*main func*/
int connect_arrays(move * array, move * array1, int array_len, int array1_len);
void unmake_move(board *b, move m, irreversible_move_info inf);
move* get_all_moves(board *the_board,move *all_moves);



#endif /* DA695DC0_90E2_40B5_BC05_F55A01BC0605 */
