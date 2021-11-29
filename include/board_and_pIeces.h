/*
 Created by meir on 29/11/2021.
*/

#include <math.h>

#define number_of_rows 8 /* Number of rows in the chess board. */
#define number_of_columns 8 /* Number of columns in the chess board. */

enum types {empty,knight,rook,queen,king,pawn,bishop};
enum columns {a,b,c,d,e,f,g,h};

typedef struct {
    unsigned column_in_the_board : log2(number_of_columns);
    unsigned row_in_the_board : log2(number_of_rows);

    enum types type_of_piece;

    unsigned can_en_passant_right : 1;
    unsigned can_en_passant_left : 1;

}square;

typedef struct {
    square squares[number_of_rows * number_of_columns];

    unsigned can_black_castle_long : 1;
    unsigned can_black_castle_short : 1;
    unsigned can_white_castle_long : 1;
    unsigned can_white_castle_short : 1;

    unsigned whose_turn : 1;
}board;