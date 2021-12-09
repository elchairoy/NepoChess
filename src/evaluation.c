#include "../include/evaluation.h"



#define QUEEN_WORTH 9
#define ROOK_WORTH 5
#define PAWN_WORTH 1
#define KNIGHT_WORTH 3
#define BISHOP_WORTH 3

#define NUMBER_OF_PIECES_DEVELOPED_MIDDLE_GAME 8

char evaluate_by_points(board *b) {
    int i;
    char eval = 0;
    /*
    for (i = 0;i < NUMBER_OF_SQUARES;i++) {
        switch (get_piece_in_square(b,i)) {
            case white_pawn:
                eval += PAWN_WORTH;
                break;

            case white_bishop:
                eval += BISHOP_WORTH;
                break;

            case white_knight:
                eval += KNIGHT_WORTH;
                break;

            case white_queen:
                eval += QUEEN_WORTH;
                break;

            case white_rook:
                eval += ROOK_WORTH;
                break;

            case black_pawn:
                eval -= PAWN_WORTH;
                break;

            case black_bishop:
                eval -= BISHOP_WORTH;
                break;

            case black_knight:
                eval -= KNIGHT_WORTH;
                break;

            case black_queen:
                eval -= QUEEN_WORTH;
                break;

            case black_rook:
                eval -= ROOK_WORTH;
                break;

            default:
                break;
        }
    }*/
    return eval;
}

/* We will add it later:

char number_of_white_developed_pieces(board *b) {
    char i;
    char piece;
    char number_of_pieces;
    for (i = 0; i < NUMBER_OF_COLUMNS; i++) {
        piece = get_piece_in_square(b,i);
        if (piece == white_knight || piece == white_bishop || piece == white_queen)
            number_of_pieces++;
    }
    return 5-number_of_pieces;
}

char number_of_black_developed_pieces(board *b) {
    char i;
    char piece;
    char number_of_pieces;
    for (i = NUMBER_OF_SQUARES - NUMBER_OF_COLUMNS ;i < NUMBER_OF_SQUARES; i++) {
        piece = get_piece_in_square(b,i);
        if (piece == black_knight|| piece == black_bishop || piece == black_queen)
            number_of_pieces++;
    }
    return 5-number_of_pieces;
}

char is_middle_game(board *b) {
    char is_middle_game;
    is_middle_game += number_of_white_developed_pieces(b) + number_of_black_developed_pieces(b);

    if (get_piece_in_square(b,4) != white_king)
        is_middle_game += 2;

    if (get_piece_in_square(b,54) != black_king)
        is_middle_game += 2;

}
 */