#include "../include/play_minigame.h"

#define get_square_number(column, row) ((row - '0' - 1) * 8 + (column - 'a'))
#define get_square_loc(square_num) (strcat((char[2]){(char)'a' + (square_num % 8), '\0'}, (char[2]){(char)'1' + (square_num / 8), '\0'}))

move random_move(board *the_board)
{
    /*generate random move from the board*/
    move *all_moves = get_all_moves(the_board);
    int len = 0;
    while (all_moves[len] != END)
        len++;
    return all_moves[rand() % len];
}

void scanner(char *move, int get_src)
{
    /*get move from user and validate the move, keep asking untill a valid move is given*/
    char row;
    char column;
    char trash;
    if (get_src)
        printf("enter src: ");
    else
        printf("enter dst: ");
    while (scanf(" %c %c%c", &column, &row, &trash) == 3 &&
           trash != '\r' && trash != '\n')
    {
        char buffer[4096];
        if (scanf("%4095[^\n]", buffer) == EOF)
            break;
        printf("too long\n");
        if (get_src)
            printf("enter src: ");
        else
            printf("enter dst: ");
    }
    if (column < 'a' || column > 'h' || row < '1' || row > '8')
    {
        printf("invalid square\n");
        scanner(move, get_src);
    }
    else
    {
        move[0] = column;
        move[1] = row;
    }
}

int player_move(board *the_board, int color)
{
    /*ask for a move, validate it then comite the moveand request more info from user if needed*/
    int i = 0;
    int row;
    char temp[3];
    move *all_moves;
    char column, src_square, dst_square;
    while (1)
    {
        scanner(temp, 1);
        src_square = get_square_number(temp[0], temp[1]);
        if (check_src(the_board, src_square, color))
        {
            scanner(temp, 0);
            dst_square = get_square_number(temp[0], temp[1]);
            all_moves = get_all_moves(the_board);
            i = 0;
            while (all_moves[i] != END)
            {
                if (src_square == get_src_square(all_moves[i]) && dst_square == get_dst_square(all_moves[i]))
                {
                    if (color)
                    {
                        if (get_piece_in_square(the_board, src_square) == white_pawn && get_row(src_square) == 6)
                            commit_a_move_for_white(the_board, create_a_move(src_square, dst_square, get_player_promotion_choice(), 0, 0));
                        else
                            commit_a_move_for_white(the_board, all_moves[i]);
                    }
                    else
                    {
                        if (get_piece_in_square(the_board, src_square) == black_pawn && get_row(src_square) == 1)
                            commit_a_move_for_black(the_board, create_a_move(src_square, dst_square, get_player_promotion_choice(), 0, 0));
                        else
                            commit_a_move_for_black(the_board, all_moves[i]);
                    }
                    free(all_moves);
                    return 0;
                }
                i++;
            }
            free(all_moves);
        }
        printf("invalid move\n");
    }
}


int get_player_promotion_choice()
{
    int promotion;
    while (1)
    {
        printf("promot to? (0=Q,1=R,2=N,3=B): ");
        scanf("%d", &promotion);
        if (promotion >= 0 && promotion <= 3)
            return promotion;
        printf("invalid move\n");
    }
}

int game(board *the_board, HashTable *ht)
{
    /*while loop for the chess game, move from white to black and when the game over checker returns true the loop is broken*/
    system("clear");
    print_board(the_board);
    while (1)
    {
        if (check_endgame(the_board, WHITE) == 0)
            return 0;
        player_move(the_board, WHITE);
        system("clear");
        print_board(the_board);
        if (check_endgame(the_board, BLACK) == 0)
            return 0;
        bot_move(the_board, ht, BLACK);
        system("clear");
        print_board(the_board);
    }
    return 0;
}


char translate_promotion(int promotion){
    switch (promotion)
    {
    case 0:
        return 'q';
    case 1:
        return 'r';
    case 2:
        return 'n';
    case 3:
        return 'b';
    }
}


char check_bot_promotion(board *the_board, move the_move, int color)
{
    int src_s = get_src_square(the_move);
    int src_r = get_row(src_s);
    int src_p = get_piece_in_square(the_board ,src_s);
    if(color == WHITE){
        if(src_p == white_pawn && src_r == 6)
            return translate_promotion(get_promotion_choice(the_move));
    }
    else {
        if(src_p == black_pawn && src_r == 1)
            return translate_promotion(get_promotion_choice(the_move));
    }
    return ' ';
}


void bot_move(board *the_board, HashTable *ht, int color)
{
    move bot_move;
    int depth = 5;
    int prefrontier = 4;
    if (color == WHITE)
    {
        bot_move = get_best_move_white(the_board, depth, prefrontier, ht);
        printf("%s%s%c\n", get_square_loc(get_src_square(bot_move)),get_square_loc(get_dst_square(bot_move)), check_bot_promotion(the_board, bot_move, color));
        commit_a_move_for_white(the_board, bot_move);
    }
    else
    {
        bot_move = get_best_move_black(the_board, depth, prefrontier, ht);
        printf("%s%s%c\n", get_square_loc(get_src_square(bot_move)),get_square_loc(get_dst_square(bot_move)), check_bot_promotion(the_board, bot_move, color));
        commit_a_move_for_black(the_board, bot_move);
    }
    ht_clear(ht);
}

int check_endgame(board *the_board, int color)
{
    if (color == WHITE)
    {
        if (get_all_moves(the_board)[0] == END)
        {
            if (isAttacked_by_black(the_board, find_king_square(the_board, WHITE)))
                printf("CHECKMATE 0-1\n");
            else
                printf("STALMATE 0.5-0.5\n");
            return 0;
        }
    }
    else
    {
        if (get_all_moves(the_board)[0] == END)
        {
            if (isAttacked_by_white(the_board, find_king_square(the_board, BLACK)))
                printf("CHECKMATE 1-0\n");
            else
                printf("STALMATE 0.5-0.5\n");
            return 0;
        }
    }
    return 1;
}

int check_src(board *the_board, char src, char the_move)
{
    /*validate src squear from user input*/
    if (get_piece_in_square(the_board, src) == empty)
        return 0;
    if (color_of_piece(src, the_board) != the_move)
        return 0;
    return 1;
}

int check()
{
    /*creates the board, set info and calls game func*/
    board START_BOARD;
    move *all_moves;
    char initial_board[32] = {
        white_rook << 4 | white_knight, white_bishop << 4 | white_queen, white_king << 4 | white_bishop, white_knight << 4 | white_rook,
        white_pawn << 4 | white_pawn, white_pawn << 4 | white_pawn, white_pawn << 4 | white_pawn, white_pawn << 4 | white_pawn,
        empty, empty, empty, empty,
        empty, empty, empty, empty,
        empty, empty, empty, empty,
        empty, empty, empty, empty,
        black_pawn << 4 | black_pawn, black_pawn << 4 | black_pawn, black_pawn << 4 | black_pawn, black_pawn << 4 | black_pawn,
        black_rook << 4 | black_knight, black_bishop << 4 | black_queen, black_king << 4 | black_bishop, black_knight << 4 | black_rook};
    START_BOARD.can_black_castle_long = 1;
    START_BOARD.can_black_castle_short = 1;
    START_BOARD.can_white_castle_long = 1;
    START_BOARD.can_white_castle_short = 1;
    START_BOARD.pawn_en_passant_left = 0;
    START_BOARD.pawn_en_passant_right = 0;
    START_BOARD.whos_turn = WHITE;

    int i;
    for (i = 0; i < 32; i++)
        START_BOARD.squares[i] = initial_board[i];
    HashTable ht;
    ht_setup(&ht, sizeof(board), sizeof(double), 100000000);
    game(&START_BOARD, &ht);
    return 0;
}

/*
games againts chess.com engeine:
    1 - win
    2 - win
    3 (550) - win 21/9/22
    4 (700) - win 21/9/22
    5 - ?
    6 - ?
    7 - ?
    elchai - ?
*/
