/*
 Created by meir on 29/11/2021.
*/

#ifndef DD0FAEFF_39F7_47FA_AB64_C1E01E82D91A
#define DD0FAEFF_39F7_47FA_AB64_C1E01E82D91A


#include <math.h>

#define NUMBER_OF_ROWS 8 /* Number of rows in the chess board. */
#define NUMBER_OF_COLUMNS 8 /* Number of columns in the chess board. */

#define NUMBER_OF_SQUARES (NUMBER_OF_COLUMNS * NUMBER_OF_ROWS)

#define get_column(square) (square % NUMBER_OF_COLUMNS) /* Get the column of a square. */
#define get_row(square) (square / NUMBER_OF_ROWS) /* Get a row of a square. */

#define is_white(piece) ((piece) <= 6 && (piece) >= 1)
#define is_black(piece) ((piece) >= 7)

#define UP NUMBER_OF_COLUMNS /* Piece moves up. */
#define DOWN -NUMBER_OF_COLUMNS /* and down. */
#define LEFT -1 /* To the left. */
#define RIGHT 1 /* To the right. */

#define MAX_POSSIBLE_MOVES 200 /* Maximum number of moves possible in a position. */

enum types {empty,white_knight,white_rook,white_queen,white_king,white_pawn,white_bishop,black_knight,black_rook,black_queen,black_king,black_pawn,black_bishop}; /* What cat be on a square. */
enum columns {a,b,c,d,e,f,g,h}; /* The columns there are. */
enum promotions {promote_to_queen, promote_to_rook, promote_to_knight, promote_to_bishop}; /* What can be promoted to */

typedef unsigned short int move;

typedef unsigned int irreversible_move_info; 

/* The struct of a position. */
typedef struct {
    char squares[NUMBER_OF_SQUARES / 2]; /* List of all the squares in the board.
                                                        Each square represented by half a char. */

    unsigned can_black_castle_long : 1; /* 0 if can't, 1 if he can. */
    unsigned can_black_castle_short : 1; /* 0 if can't, 1 if he can. */
    unsigned can_white_castle_long : 1; /* 0 if can't, 1 if he can. */
    unsigned can_white_castle_short : 1; /* 0 if can't, 1 if he can. */

    unsigned whos_turn : 1; /* 1 if it's white turn, 0 if it's black turn. */

    /* To read about en passant - https://www.chess.com/terms/en-passant. */
    unsigned en_passant_pawn : 7; /* The square of the pawn that can by eaten by en passant. (if no pawns can en passant, it's 0)  */
}board;


/* The struct of a game: */
typedef struct {
    board *current_position; /* The current position of the game. */
    board initial_position; /* The initial position of the game. */
    move moves[100]; /* List of all the moves in the game. */
    unsigned int number_of_moves; /* Number of moves in the game. */
    char result; /* The result of the game. */
}game;

#endif /* DD0FAEFF_39F7_47FA_AB64_C1E01E82D91A */
