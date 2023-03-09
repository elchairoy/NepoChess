/*
 Created by meir on 30/11/2021.
*/
#include "../include/useful_functions.h"
char * PIECES1[13] = {" " , "\u265E", "\u265C", "\u265B", "\u265A", "\u265F", "\u265D", "\u2658", "\u2656", "\u2655", "\u2654", "\u2659", "\u2657"};

/* Gives the piece in the given square. */
char get_piece_in_square(board *b ,unsigned char square_number) {
    if (square_number % 2 == 1) /* If the square is in the first half a byte: */
        return (b->squares[square_number/2] & MASK_FOR_A_HALF) /* - clears the second half. */;
        
    else /* If the square is in the second half a byte: */
        return (b->squares[square_number/2] & (MASK_FOR_A_HALF << 4)) /* - clears the first half */ >> 4 /* - shifts it to the first half. */;
}

/* Change the piece in the given square to the given piece.
   If there is an error - returns -1. */
void change_the_square(board *b,unsigned char square_number ,char new_piece) {
    if (square_number % 2 == 1) /* If the square is in the first half a byte: */
        b->squares[square_number / 2] = (b->squares[square_number / 2] & (MASK_FOR_A_HALF << (4))) /* - clears the first half */ | (new_piece); /* - places the new piece in the first half */
    
    else /* If the square is in the second half a byte: */
        b->squares[square_number / 2] = (b->squares[square_number / 2] & MASK_FOR_A_HALF) /* - clears the second half */ | (new_piece << 4); /* - places the new piece in the second half */
}

char is_attacked_by_black(board *the_board, char square) {
    char piece;
    int i = 0;
    /* Check danger from columns and rows: */
    while (move_up(square + i * UP, the_board, WHITE))
        i++;
    piece = get_piece_in_square(the_board, square + i * UP);
    if (piece ==  black_queen || piece == black_rook)
        return 1;

    i=0;
    while (move_down(square + i * DOWN, the_board, WHITE))
        i++;
    piece = get_piece_in_square(the_board, square + i * DOWN);
    if (piece ==  black_queen || piece == black_rook)
        return 1;
    
    i=0;
    while (move_right(square + i * RIGHT, the_board, WHITE))
        i++;
    piece = get_piece_in_square(the_board, square + i * RIGHT);
    if (piece ==  black_queen || piece == black_rook)
        return 1;
    
    i=0;
    while (move_left(square + i * LEFT, the_board, WHITE))
        i++;
    piece = get_piece_in_square(the_board, square + i * LEFT);
    if (piece ==  black_queen || piece == black_rook)
        return 1;
    
    i=0;
    /* Check danger form diagonals: */
    while (move_up_right(square + i * UP_RIGHT, the_board, WHITE))
        i++;
    piece = get_piece_in_square(the_board, square + i * UP_RIGHT);
    if (piece ==  black_queen || piece == black_bishop)
        return 1;
    i=0;

    while (move_up_left(square + i * UP_LEFT, the_board, WHITE))
        i++;
    piece = get_piece_in_square(the_board, square + i * UP_LEFT);
    if (piece ==  black_queen || piece == black_bishop)
        return 1;
    i=0;

    while (move_down_right(square + i * DOWN_RIGHT, the_board, WHITE))
        i++;
    piece = get_piece_in_square(the_board, square + i * DOWN_RIGHT);
    if (piece ==  black_queen || piece == black_bishop)
        return 1;
    i=0;

    while (move_down_left(square + i * DOWN_LEFT, the_board, WHITE))
        i++;
    piece = get_piece_in_square(the_board, square + i * DOWN_LEFT);
    if (piece == black_queen || piece == black_bishop)
        return 1;
    i=0;

    /* Check danger from knights: */

    /*knight up up right to eat*/
    if (get_column(square) > 0 && get_row(square) > 1) {
        if (get_piece_in_square(the_board, square + KNIGHT_DOWN_DOWN_LEFT) == black_knight)
            return 1;
    }

    /*knight up up left to eat*/
    if (get_column(square) < 7 && get_row(square) > 1) {
        if (get_piece_in_square(the_board, square + KNIGHT_DOWN_DOWN_RIGHT) == black_knight)
            return 1;
    }

    /*knight up right right to eat*/
    if (get_column(square) > 1 && get_row(square) > 0) {
        if (get_piece_in_square(the_board, square + KNIGHT_DOWN_LEFT_LEFT) == black_knight)
            return 1;
    }

    /*knight up left left to eat*/
    if (get_column(square) < 6 && get_row(square) > 0) {
        if (get_piece_in_square(the_board, square + KNIGHT_DOWN_RIGHT_RIGHT) == black_knight)
            return 1;
    }

    /*knight down down right to eat*/
    if (get_column(square) > 0 && get_row(square) < 6) {
        if (get_piece_in_square(the_board, square + KNIGHT_UP_UP_LEFT) == black_knight)
            return 1;
    }

    /*knight down down left to eat*/
    if (get_column(square) < 7 && get_row(square) < 6) {
        if (get_piece_in_square(the_board, square + KNIGHT_UP_UP_RIGHT) == black_knight)
            return 1;
    }

    /*knight down right right to eat*/
    if (get_column(square) > 1 && get_row(square) < 7) {
        if (get_piece_in_square(the_board, square + KNIGHT_UP_LEFT_LEFT) == black_knight)
            return 1;
    }

    /*knight down left left to eat*/
    if (get_column(square) < 6 && get_row(square) < 7) {
        if (get_piece_in_square(the_board, square + KNIGHT_UP_RIGHT_RIGHT) == black_knight)
            return 1;
    }


    /* Check danger from pawns: */
    if (move_up_right(square,the_board,WHITE) && get_piece_in_square(the_board, square + UP_RIGHT) == black_pawn)
        return 1;
    
    if (move_up_left(square,the_board,WHITE) && get_piece_in_square(the_board, square + UP_LEFT) == black_pawn)
        return 1;

        /* Check danger from king: */
    if (move_right(square,the_board,WHITE) && get_piece_in_square(the_board,square + RIGHT) == black_king)
        return 1;

    if (move_left(square,the_board,WHITE) && get_piece_in_square(the_board,square + LEFT) == black_king)
        return 1;

    if (move_up(square,the_board,WHITE) && get_piece_in_square(the_board,square + UP) == black_king)
        return 1;

    if (move_down(square,the_board,WHITE) && get_piece_in_square(the_board,square + DOWN) == black_king)
        return 1;

    if (move_up_right(square,the_board,WHITE) && get_piece_in_square(the_board,square + UP_RIGHT) == black_king)
        return 1;

    if (move_up_left(square,the_board,WHITE) && get_piece_in_square(the_board,square + UP_LEFT) == black_king)
        return 1;

    if (move_down_left(square,the_board,WHITE) && get_piece_in_square(the_board,square + DOWN_LEFT) == black_king)
        return 1;

    if (move_down_right(square,the_board,WHITE) && get_piece_in_square(the_board,square + DOWN_RIGHT) == black_king)
        return 1;


    return 0;
}


char is_attacked_by_white(board *the_board, char square) {
    char piece;
    int i = 0;
    /* Check danger from columns and rows: */
    while (move_up(square + i * UP, the_board, BLACK))
        i++;
    piece = get_piece_in_square(the_board, square + i * UP);
    if (piece ==  white_queen || piece == white_rook)
        return 1;

    i=0;
    while (move_down(square + i * DOWN, the_board, BLACK))
        i++;
    piece = get_piece_in_square(the_board, square + i * DOWN);
    if (piece == white_queen || piece == white_rook)
        return 1;
    
    i=0;
    while (move_right(square + i * RIGHT, the_board, BLACK))
        i++;
    piece = get_piece_in_square(the_board, square + i * RIGHT);
    if (piece == white_queen || piece == white_rook)
        return 1;
    
    i=0;
    while (move_left(square + i * LEFT, the_board, BLACK))
        i++;
    piece = get_piece_in_square(the_board, square + i * LEFT);
    if (piece == white_queen || piece == white_rook)
        return 1;
    
    i=0;
    /* Check danger form diagonals: */
    while (move_up_right(square + i * UP_RIGHT, the_board, BLACK))
        i++;
    piece = get_piece_in_square(the_board, square + i * UP_RIGHT);
    if (piece == white_queen || piece == white_bishop)
        return 1;
    i=0;

    while (move_up_left(square + i * UP_LEFT, the_board, BLACK))
        i++;
    piece = get_piece_in_square(the_board, square + i * UP_LEFT);
    if (piece == white_queen || piece == white_bishop)
        return 1;
    i=0;

    while (move_down_right(square + i * DOWN_RIGHT, the_board, BLACK))
        i++;
    piece = get_piece_in_square(the_board, square + i * DOWN_RIGHT);
    if (piece == white_queen || piece == white_bishop)
        return 1;
    i=0;

    while (move_down_left(square + i * DOWN_LEFT, the_board, BLACK))
        i++;
    piece = get_piece_in_square(the_board, square + i * DOWN_LEFT);
    if (piece == white_queen || piece == white_bishop)
        return 1;
    i=0;

    /* Check danger from knights: */

    /*knight up up right to eat*/
    if (get_column(square) > 0 && get_row(square) > 1) {
        if (get_piece_in_square(the_board, square + KNIGHT_DOWN_DOWN_LEFT) == white_knight)
            return 1;
    }

    /*knight up up left to eat*/
    if (get_column(square) < 7 && get_row(square) > 1) {
        if (get_piece_in_square(the_board, square + KNIGHT_DOWN_DOWN_RIGHT) == white_knight)
            return 1;
    }

    /*knight up right right to eat*/
    if (get_column(square) > 1 && get_row(square) > 0) {
        if (get_piece_in_square(the_board, square + KNIGHT_DOWN_LEFT_LEFT) == white_knight)
            return 1;
    }

    /*knight up left left to eat*/
    if (get_column(square) < 6 && get_row(square) > 0) {
        if (get_piece_in_square(the_board, square + KNIGHT_DOWN_RIGHT_RIGHT) == white_knight)
            return 1;
    }

    /*knight down down right to eat*/
    if (get_column(square) > 0 && get_row(square) < 6) {
        if (get_piece_in_square(the_board, square + KNIGHT_UP_UP_LEFT) == white_knight)
            return 1;
    }

    /*knight down down left to eat*/
    if (get_column(square) < 7 && get_row(square) < 6) {
        if (get_piece_in_square(the_board, square + KNIGHT_UP_UP_RIGHT) == white_knight)
            return 1;
    }

    /*knight down right right to eat*/
    if (get_column(square) > 1 && get_row(square) < 7) {
        if (get_piece_in_square(the_board, square + KNIGHT_UP_LEFT_LEFT) == white_knight)
            return 1;
    }

    /*knight down left left to eat*/
    if (get_column(square) < 6 && get_row(square) < 7) {
        if (get_piece_in_square(the_board, square + KNIGHT_UP_RIGHT_RIGHT) == white_knight)
            return 1;
    }


    /* Check danger from pawns: */
    if (move_down_right(square,the_board,BLACK) && get_piece_in_square(the_board, square + DOWN_RIGHT) == white_pawn)
        return 1;
    
    if (move_down_left(square,the_board,BLACK) && get_piece_in_square(the_board, square + DOWN_LEFT) == white_pawn)
        return 1;

        /* Check danger from king: */
    if (move_right(square,the_board,BLACK) && get_piece_in_square(the_board,square + RIGHT) == white_king)
        return 1;

    if (move_left(square,the_board,BLACK) && get_piece_in_square(the_board,square + LEFT) == white_king)
        return 1;

    if (move_up(square,the_board,BLACK) && get_piece_in_square(the_board,square + UP) == white_king)
        return 1;

    if (move_down(square,the_board,BLACK) && get_piece_in_square(the_board,square + DOWN) == white_king)
        return 1;

    if (move_up_right(square,the_board,BLACK) && get_piece_in_square(the_board,square + UP_RIGHT) == white_king)
        return 1;

    if (move_up_left(square,the_board,BLACK) && get_piece_in_square(the_board,square + UP_LEFT) == white_king)
        return 1;

    if (move_down_left(square,the_board,BLACK) && get_piece_in_square(the_board,square + DOWN_LEFT) == white_king)
        return 1;

    if (move_down_right(square,the_board,BLACK) && get_piece_in_square(the_board,square + DOWN_RIGHT) == white_king)
        return 1;

    return 0;
}


char find_king_square(board *the_board, char color){
    int i = 0;
    char piece = 0; 
    if (color) {
        piece = white_king;
        if (get_piece_in_square(the_board,4) == white_king)
            return 4;
    }
    else {
        piece = black_king;
        if (get_piece_in_square(the_board,60) == black_king)
            return 60;
    }
    while (get_piece_in_square(the_board,i) != piece && i < NUMBER_OF_SQUARES) 
        i++;
    if (i == NUMBER_OF_SQUARES) {
        printf("Error: King not found!\n");
        print_board(the_board);
    }
        
    return i;
}

char is_in_array(char *array, char value){
    int i;
    for (i = 0; array[i] != -1; i++) {
        if (array[i] == value)
            return 1;
    }
    return 0;
}

char compare_boards(board *board1, board *board2){
    int i;
    for (i = 0; i < NUMBER_OF_SQUARES; i++) {
        if (get_piece_in_square(board1,i) != get_piece_in_square(board2,i))
            return 0;
    }
    if (board1->en_passant_pawn != board2->en_passant_pawn)
        return 0;
    if (board1->can_white_castle_short != board2->can_white_castle_short)
        return 0;
    if (board1->can_white_castle_long != board2->can_white_castle_long)
        return 0;
    if (board1->can_black_castle_short != board2->can_black_castle_short)
        return 0;
    if (board1->can_black_castle_long != board2->can_black_castle_long)
        return 0;
    return 1;
}

void copy_boards(board *board1, board *board2){
    memcpy(board1,board2,sizeof(board));
}

void print_move(move the_move){
    printf("%c%d%c%d\n",get_column(get_src_square(the_move)) + 'a',get_row(get_src_square(the_move)) + 1,get_column(get_dst_square(the_move)) + 'a',get_row(get_dst_square(the_move)) + 1);
}

void print_line(){
    int z;
    /*Print a row of lines to separate.*/
    printf("  ");
    for(z = 0; z < 8; z++){
        printf("+----");
    }
    printf("+\n");
}


void print_board(board *the_board){
    int i, x, square_in_line, first_square_in_line, line, piece;
    if (get_piece_in_square(the_board,57) == empty) {
        printf("1");

    }
    /*
    Line - current line number.
    First_square_in_line - number of the first square in the 'Line'
    Square_in_line - number of the column in the 'current_line'
    Piece - the peice in the 'current square'
    i, x - for loop var
    */
    print_line();
    /*First for returns the line to print from line 8 to line 1*/
    for(line = NUMBER_OF_ROWS; line > 0; line--){
        first_square_in_line = (line - 1) * NUMBER_OF_ROWS;
        printf("%d ",line);
        /*Second for prints the piece in every square of the current line from the left to the right.*/ 
        for(square_in_line = 0; square_in_line < NUMBER_OF_COLUMNS; square_in_line++){
            piece = get_piece_in_square(the_board, first_square_in_line + square_in_line);
            printf("| %s  ", PIECES1[piece]);
        }
        printf("|\n");
        print_line();
    }
    /*Print letters on the bottem.*/
    for(i=0; i < NUMBER_OF_COLUMNS; i++){
        /*Print enough spaces for the letter to be in the middle.*/
        for(x = 0; x < 4; x++)
            printf(" ");
        /*print the letter from a to h*/
        printf("%c", i + 'a');
    }
    printf("\n");
}


char check_white_long_castle(board *the_board){
    move temp;
    if(!is_attacked_by_black(the_board, DEAFULT_WHITE_KING_SQUARE)){
        if(the_board->can_white_castle_long 
                && get_piece_in_square(the_board, DEAFULT_WHITE_KING_SQUARE + LEFT) == empty 
                && get_piece_in_square(the_board, DEAFULT_WHITE_KING_SQUARE + LEFT*2) == empty 
                && get_piece_in_square(the_board, DEAFULT_WHITE_KING_SQUARE + LEFT*3) == empty){
            create_a_move(temp, DEAFULT_WHITE_KING_SQUARE, DEAFULT_WHITE_KING_SQUARE + LEFT, 0, 0, 0);
            if(is_move_valid(the_board, temp, WHITE)){
                    create_a_move(temp, DEAFULT_WHITE_KING_SQUARE, DEAFULT_WHITE_KING_SQUARE + LEFT*2, 0, 1, 0);
                    if(is_move_valid(the_board, temp, WHITE)){
                        return 1;
                    }
                }
        }
    }
    return 0;
}

char check_white_short_castle(board *the_board){
    move temp;
    if(!is_attacked_by_black(the_board, DEAFULT_WHITE_KING_SQUARE)){
        if(the_board->can_white_castle_short 
                && get_piece_in_square(the_board, DEAFULT_WHITE_KING_SQUARE + RIGHT) == empty
                && get_piece_in_square(the_board, DEAFULT_WHITE_KING_SQUARE + RIGHT*2) == empty){
            create_a_move(temp, DEAFULT_WHITE_KING_SQUARE, DEAFULT_WHITE_KING_SQUARE + RIGHT, 0, 0, 0);
            if(is_move_valid(the_board, temp, WHITE)){
                    create_a_move(temp, DEAFULT_WHITE_KING_SQUARE, DEAFULT_WHITE_KING_SQUARE + RIGHT*2, 0, 0, 1);
                    if(is_move_valid(the_board, temp, WHITE)){
                        return 1;
                    }
                }
        }
    }
    return 0;
}

char check_black_long_castle(board *the_board){
    move temp;
    if(!is_attacked_by_white(the_board, DEAFULT_BLACK_KING_SQUARE)){
        if(the_board->can_black_castle_long
                && get_piece_in_square(the_board, DEAFULT_BLACK_KING_SQUARE + LEFT) == empty
                && get_piece_in_square(the_board, DEAFULT_BLACK_KING_SQUARE + LEFT * 2) == empty
                && get_piece_in_square(the_board, DEAFULT_BLACK_KING_SQUARE + LEFT * 3) == empty){
            create_a_move(temp, DEAFULT_BLACK_KING_SQUARE, DEAFULT_BLACK_KING_SQUARE + LEFT, 0, 0, 0);
            if(is_move_valid(the_board, temp, BLACK)){
                create_a_move(temp, DEAFULT_BLACK_KING_SQUARE, DEAFULT_BLACK_KING_SQUARE + LEFT * 2, 0, 1, 0);
                if(is_move_valid(the_board, temp, BLACK)){
                    return 1;
                }
            }
        }
    }
    return 0;
}

char check_black_short_castle(board *the_board){
    move temp;
    if(!is_attacked_by_white(the_board, DEAFULT_BLACK_KING_SQUARE)){
        if(the_board->can_black_castle_short 
                && get_piece_in_square(the_board, DEAFULT_BLACK_KING_SQUARE + RIGHT) == empty
                && get_piece_in_square(the_board, DEAFULT_BLACK_KING_SQUARE + RIGHT*2) == empty){
            create_a_move(temp, DEAFULT_BLACK_KING_SQUARE, DEAFULT_BLACK_KING_SQUARE + RIGHT, 0, 0, 0);
            if(is_move_valid(the_board, temp, BLACK)){
                    create_a_move(temp, DEAFULT_BLACK_KING_SQUARE, DEAFULT_BLACK_KING_SQUARE + RIGHT*2, 0, 0, 1);
                    if(is_move_valid(the_board, temp, BLACK)){
                        return 1;
                    }
                }
        }
    }
    return 0;
}

char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}

irreversible_move_info get_irrev_move_info(board *b, move m) {
    char src, dst, piece, piece_taken, en_passant_pawn = b->en_passant_pawn;
    irreversible_move_info inf;
    if (b->whos_turn == WHITE) {
            src = get_src_square(m);
            dst = get_dst_square(m);
            piece = get_piece_in_square(b,src);
            piece_taken = get_piece_in_square(b,dst);
            if (piece == white_pawn && piece_taken == 0 && dst != src + UP && dst != src + UP + UP) { /* En passant: */
                create_a_irrev_move_info(inf, piece_taken, 0, 1, en_passant_pawn, b->can_white_castle_short, b->can_white_castle_long, b->can_black_castle_short, b->can_black_castle_long);
            }
            else {
                create_a_irrev_move_info(inf, piece_taken, ((piece == white_pawn && 56 <= dst) ? 1 : 0), 0, en_passant_pawn, b->can_white_castle_short, b->can_white_castle_long, b->can_black_castle_short, b->can_black_castle_long);
            }
        }
    if (b->whos_turn == BLACK) {
        src = get_src_square(m);
        dst = get_dst_square(m);
        piece = get_piece_in_square(b,src);
        piece_taken = get_piece_in_square(b,dst);
        if (piece == black_pawn && piece_taken == 0 && dst != src + DOWN && dst != src + DOWN + DOWN) { /* En passant: */
            create_a_irrev_move_info(inf, piece_taken, 0, 1, en_passant_pawn, b->can_white_castle_short, b->can_white_castle_long, b->can_black_castle_short, b->can_black_castle_long);
        }
        else {
            create_a_irrev_move_info(inf, piece_taken, ((piece == black_pawn && dst <= 7) ? 1 : 0), 0, en_passant_pawn, b->can_white_castle_short, b->can_white_castle_long, b->can_black_castle_short, b->can_black_castle_long);
        }
    }
    return inf;
}

/* Unmake move for games: */
void unmake_move_in_game(game *the_game, move m, irreversible_move_info inf) {
    unmake_move_in_board(the_game->current_position, m, inf);
    the_game->moves[the_game->number_of_moves-1] = 0;
    the_game->number_of_moves--;
}

/* Unmake move for boards: */
void unmake_move_in_board(board *the_board, move m, irreversible_move_info inf) {
    char src = get_src_square(m);
    char dst = get_dst_square(m);
    char piece = get_piece_in_square(the_board,dst);
    if (the_board->whos_turn == WHITE) {
        the_board->whos_turn = BLACK;
        if (piece == black_king) {
            if (dst == 62 && src == 60) { /* The move was a short castle. */
                change_the_square(the_board, 60, black_king);
                change_the_square(the_board, 63, black_rook);
                change_the_square(the_board, 62, empty);
                change_the_square(the_board, 61, empty);
            }
            else if (dst == 58 && src == 60) { /* The move was a short castle. */
                change_the_square(the_board, 60, black_king);
                change_the_square(the_board, 56, black_rook);
                change_the_square(the_board, 58, empty);
                change_the_square(the_board, 59, empty);
            }
            else {
                change_the_square(the_board, src, black_king);
                change_the_square(the_board, dst, get_piece_taken(inf));
            }
        }
        else if (get_is_en_passant(inf) != 0) { /* The move was an en passant. */
            change_the_square(the_board,dst+UP,white_pawn);
            change_the_square(the_board, src, black_pawn);
            change_the_square(the_board, dst, empty);
        }
        else if (get_is_promoted(inf) == 1) {
            change_the_square(the_board, src, black_pawn);
            change_the_square(the_board, dst, get_piece_taken(inf));
        }
        else {
            change_the_square(the_board, src, piece);
            change_the_square(the_board, dst, get_piece_taken(inf));
        }
    }
    else {
        the_board->whos_turn = WHITE;
        if (piece == white_king) {
            if (dst == 6 && src == 4) { /* The move was a short castle. */
                change_the_square(the_board, 4, white_king);
                change_the_square(the_board, 7, white_rook);
                change_the_square(the_board, 6, empty);
                change_the_square(the_board, 5, empty);
            }
            else if (dst == 2 && src == 4) { /* The move was a short castle. */
                change_the_square(the_board, 4, white_king);
                change_the_square(the_board, 0, white_rook);
                change_the_square(the_board, 2, empty);
                change_the_square(the_board, 3, empty);
            }
            else {
                change_the_square(the_board, src, white_king);
                change_the_square(the_board, dst, get_piece_taken(inf));
            }
        }
        else if (get_is_en_passant(inf) != 0) { /* The move was an en passant. */
            change_the_square(the_board,dst+DOWN,black_pawn);
            change_the_square(the_board, src, white_pawn);
            change_the_square(the_board, dst, empty);
        }
        else if (get_is_promoted(inf) == 1) {
            change_the_square(the_board, src, white_pawn);
            change_the_square(the_board, dst, get_piece_taken(inf));
        }
        else {
            change_the_square(the_board, src, piece);
            change_the_square(the_board, dst, get_piece_taken(inf));
        }
    }
    the_board->en_passant_pawn = get_en_passant_pawn_last_move(inf);
    the_board->can_white_castle_short = get_could_white_short_castle_last_move(inf);
    the_board->can_white_castle_long = get_could_white_long_castle_last_move(inf);
    the_board->can_black_castle_short = get_could_black_short_castle_last_move(inf);
    the_board->can_black_castle_long = get_could_black_long_castle_last_move(inf);
}

char check_repetition(game *the_game) {
    board temp = the_game->initial_position;
    int i;
    int number_of_repetitions = 0;
    for (i = 0; i < the_game->number_of_moves; i++) {
        if (temp.whos_turn == WHITE)
            commit_a_move_for_white_in_position(&temp, the_game->moves[i]);
        else 
            commit_a_move_for_black_in_position(&temp, the_game->moves[i]);
        if (compare_boards(&temp, the_game->current_position) == 1) {
            number_of_repetitions++;
        }
    }
    if (number_of_repetitions >= 2)
        return 1;
    else
        return 0;
}