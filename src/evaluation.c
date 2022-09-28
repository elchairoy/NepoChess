#include "../include/evaluation.h"

/* Note: all values are in centipawns (pawn / 100) */


#define QUEEN_WORTH 900 /* How much does queen worth. */
#define ROOK_WORTH 500 /* How much does rook worth. */
#define PAWN_WORTH 100 /* How much does pawn worth. */
#define KNIGHT_WORTH 320 /* How much does knight worth. */
#define BISHOP_WORTH 330 /* How much does bishop worth. */
#define KING_WORTH 20000 /* How much does king worth. (used for piece-square values) */

char pawn_square_table[NUMBER_OF_SQUARES] = {
    0,  0,  0,  0,  0,  0,  0,  0,
    50, 50, 50, 50, 50, 50, 50, 50,
    10, 10, 20, 30, 30, 20, 10, 10,
    5,  5, 10, 25, 25, 10,  5,  5,
    0,  0,  0, 20, 20,  0,  0,  0,
    5, -5,-10,  0,  0,-10, -5,  5,
    5, 10, 10,-20,-20, 10, 10,  5,
    0,  0,  0,  0,  0,  0,  0,  0
};

char knight_square_table[NUMBER_OF_SQUARES] = {
    -50,-40,-30,-30,-30,-30,-40,-50,
    -40,-20,  0,  0,  0,  0,-20,-40,
    -30,  0, 10, 15, 15, 10,  0,-30,
    -30,  5, 15, 20, 20, 15,  5,-30,
    -30,  0, 15, 20, 20, 15,  0,-30,
    -30,  5, 10, 15, 15, 10,  5,-30,
    -40,-20,  0,  5,  5,  0,-20,-40,
    -50,-40,-30,-30,-30,-30,-40,-50,
};

char bishop_square_table[NUMBER_OF_SQUARES] = {
    -20,-10,-10,-10,-10,-10,-10,-20,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -10,  0,  5, 10, 10,  5,  0,-10,
    -10,  5,  5, 10, 10,  5,  5,-10,
    -10,  0, 10, 10, 10, 10,  0,-10,
    -10, 10, 10, 10, 10, 10, 10,-10,
    -10,  5,  0,  0,  0,  0,  5,-10,
    -20,-10,-10,-10,-10,-10,-10,-20,
};

char rook_square_table[NUMBER_OF_SQUARES] = {
    0,  0,  0,  0,  0,  0,  0,  0,
    5, 10, 10, 10, 10, 10, 10,  5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    0,  0,  0,  5,  5,  0,  0,  0
};

char queen_square_table[NUMBER_OF_SQUARES] = {
    -20,-10,-10, -5, -5,-10,-10,-20,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -10,  0,  5,  5,  5,  5,  0,-10,
    -5,  0,  5,  5,  5,  5,  0, -5,
    0,  0,  5,  5,  5,  5,  0, -5,
    -10,  5,  5,  5,  5,  5,  0,-10,
    -10,  0,  5,  0,  0,  0,  0,-10,
    -20,-10,-10, -5, -5,-10,-10,-20
};

char king_middlegame_square_table[NUMBER_OF_SQUARES] = {
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -20,-30,-30,-40,-40,-30,-30,-20,
    -10,-20,-20,-20,-20,-20,-20,-10,
    20, 20,  0,  0,  0,  0, 20, 20,
    20, 30, 10,  0,  0, 10, 30, 20
};

char king_endgame_square_table[NUMBER_OF_SQUARES] = {
    -50,-40,-30,-20,-20,-30,-40,-50,
    -30,-20,-10,  0,  0,-10,-20,-30,
    -30,-10, 20, 30, 30, 20,-10,-30,
    -30,-10, 30, 40, 40, 30,-10,-30,
    -30,-10, 30, 40, 40, 30,-10,-30,
    -30,-10, 20, 30, 30, 20,-10,-30,
    -30,-30,  0,  0,  0,  0,-30,-30,
    -50,-30,-30,-30,-30,-30,-30,-50
};

/* This function evaluates the position only by the points of the pieces. */
double evaluate_by_points(board *b) {
    char i, mirrored_square, endgame;
    double eval = 0; /* The eval. */
    endgame = is_endgame(b);
    for (i = 0;i < NUMBER_OF_SQUARES;i++) {
        mirrored_square = (NUMBER_OF_ROWS - get_row(i) - 1)*8 + get_column(i); /* The mirrored square in the board. (for black piece-square table) */
        switch (get_piece_in_square(b,i)) {
            case white_pawn:
                eval += PAWN_WORTH + pawn_square_table[mirrored_square];
                break;

            case white_bishop:
                eval += BISHOP_WORTH + bishop_square_table[mirrored_square];
                break;

            case white_knight:
                eval += KNIGHT_WORTH + knight_square_table[mirrored_square];
                break;

            case white_queen:
                eval += QUEEN_WORTH + queen_square_table[mirrored_square];
                break;

            case white_rook:
                eval += ROOK_WORTH + rook_square_table[mirrored_square];
                break;

            case white_king:
                if (endgame) 
                    eval += KING_WORTH + king_endgame_square_table[mirrored_square];
                else
                    eval += KING_WORTH + king_middlegame_square_table[mirrored_square];
                break;

            case black_pawn:
                eval -= PAWN_WORTH + pawn_square_table[i]; /* The table is mirrored for black. */
                break;

            case black_bishop:
                eval -= BISHOP_WORTH + bishop_square_table[i];
                break;

            case black_knight:
                eval -= KNIGHT_WORTH + knight_square_table[i];
                break;

            case black_queen:
                eval -= QUEEN_WORTH + queen_square_table[i];
                break;

            case black_rook:
                eval -= ROOK_WORTH + rook_square_table[i];
                break;
            
            case black_king:
                if (endgame) 
                    eval -= KING_WORTH + king_endgame_square_table[i];
                else
                    eval -= KING_WORTH + king_middlegame_square_table[i];
                break;


            default:
                break;
        }
    }
    return eval/100;
}

char is_endgame(board *b) 
{
    char number_of_minor_pieces_white, number_of_minor_pieces_black;
    char is_there_queen_white = 0, is_there_queen_black = 0;
    char i;
    for (i = 0; i<NUMBER_OF_SQUARES; i++) {
        switch (get_piece_in_square(b,i))
        {
            case white_queen:
                is_there_queen_white = 1;
                break;

            case black_queen:
                is_there_queen_black = 1;
                break;

            case white_bishop: case white_knight:
                number_of_minor_pieces_white ++;
                break;
            
            case black_bishop: case black_knight:
                number_of_minor_pieces_black ++;
                break;
            
            default:
                break;
        }
    }
    if (!is_there_queen_white && !is_there_queen_black) /* If there are no queens on the board: */
        return 1;
    else 
    { /* Now check if all sizes that have queen have 1 or less minor pieces: */
        if (is_there_queen_white && number_of_minor_pieces_white<=1) {
            if (!is_there_queen_black || (is_there_queen_black && number_of_minor_pieces_black<=1)) return 1;
        }        
        else if (!is_there_queen_white)
        {
            if (!is_there_queen_black || (is_there_queen_black && number_of_minor_pieces_black<=1)) return 1;
        }    
    }
    return 0;
}