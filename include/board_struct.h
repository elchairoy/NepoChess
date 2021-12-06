/*
 Created by meir on 29/11/2021.
*/

#include <math.h>

#define NUMBER_OF_ROWS 8 /* Number of rows in the chess board. */
#define NUMBER_OF_COLUMNS 8 /* Number of columns in the chess board. */

#define NUMBER_OF_SQUARES (NUMBER_OF_COLUMNS * NUMBER_OF_ROWS)

enum types {empty,white_knight,white_rook,white_queen,white_king,white_pawn,white_bishop,black_knight,black_rook,black_queen,black_king,black_pawn,black_bishop}; /* What cat be on a square. */
enum columns {a,b,c,d,e,f,g,h}; /* The columns there are. */
enum promotions {promote_to_queen, promote_to_rook, promote_to_knight, promote_to_bishop}; /* What can be promoted to */

typedef struct {
    char squares[NUMBER_OF_SQUARES / 2]; /* List of all the squares in the board.
                                                        Each square represented by half a char. */

    unsigned can_black_castle_long : 1; /* 0 if can't, 1 if he can. */
    unsigned can_black_castle_short : 1; /* 0 if can't, 1 if he can. */
    unsigned can_white_castle_long : 1; /* 0 if can't, 1 if he can. */
    unsigned can_white_castle_short : 1; /* 0 if can't, 1 if he can. */

    unsigned whose_turn : 1; /* 0 if it's white turn, 1 if it's black turn. */

    /* To read about en passant - https://www.chess.com/terms/en-passant. */
    unsigned pawn1_en_passant : 7; /* The square of the pawn that can en passant (if no pawns can en passant, it's -1)  */
    unsigned side_of_pawn1_en_passant: 1; /* If the en passant is to the right - it's 0, left - 1; */
    unsigned pawn2_en_passant : 7; /* The square of the other pawn that can en passant (if no other pawns can en passant, it's -1)  */
    unsigned side_of_pawn2_en_passant: 1; /* If the en passant is to the right - it's 0, left - 1; */

}board;
