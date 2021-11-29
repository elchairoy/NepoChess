/*
 Created by Elchairoy Meir on 29/11/2021.
 This is the header file for the board and the squares' definition.
*/

#include <math.h>

#define number_of_rows 8 /* Number of rows in the chess board. */
#define number_of_columns 8 /* Number of columns in the chess board. */

enum types {empty,white_knight,white_rook,white_queen,white_king,white_pawn,white_bishop,black_knight,black_rook,black_queen,black_king,black_pawn,black_bishop}; /* What cat be on a square. */
enum columns {a,b,c,d,e,f,g,h};

typedef struct {
    unsigned column_in_the_board : 3; /* The number of the column where the square is. */
    unsigned row_in_the_board : 3; /* The number of the row where the square is. */

    unsigned type_of_piece : 4; /* What piece is on the square (form enum types). */

    unsigned can_en_passant_right : 1; /* Can it eat something with en passant to the right? (only relevant for pawns), 0 if can't, 1 if he can. */
    unsigned can_en_passant_left : 1; /* Can it eat something with en passant to the left? (only relevant for pawns), 0 if can't, 1 if he can. */

}square;

typedef struct {
    square squares[number_of_rows * number_of_columns]; /* List of all the squares in the board. */

    unsigned can_black_castle_long : 1; /* 0 if can't, 1 if he can. */
    unsigned can_black_castle_short : 1; /* 0 if can't, 1 if he can. */
    unsigned can_white_castle_long : 1; /* 0 if can't, 1 if he can. */
    unsigned can_white_castle_short : 1; /* 0 if can't, 1 if he can. */

    unsigned whose_turn : 1; /* 0 if it's white turn, 1 if it's black turn. */
}board;
