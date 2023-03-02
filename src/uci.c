#include "../include/uci.h"

long int moves = 0; /* The number of positions scaned. */

char initial_board[32] = {
        white_rook << 4 | white_knight, white_bishop << 4 | white_queen, white_king << 4 | white_bishop, white_knight << 4 | white_rook,
        white_pawn << 4 | white_pawn, white_pawn << 4 | white_pawn, white_pawn << 4 | white_pawn, white_pawn << 4 | white_pawn,
        empty, empty, empty, empty,
        empty, empty, empty, empty,
        empty, empty, empty, empty,
        empty, empty, empty, empty,
        black_pawn << 4 | black_pawn, black_pawn << 4 | black_pawn, black_pawn << 4 | black_pawn, black_pawn << 4 | black_pawn,
        black_rook << 4 | black_knight, black_bishop << 4 | black_queen, black_king << 4 | black_bishop, black_knight << 4 | black_rook};

/* From location (e2) to number (12): */
#define get_square_number(column, row) ((row - '0' - 1) * 8 + (column - 'a'))
/* From number(12) to location (e2): */
#define get_square_loc(square_num) (strcat((char[2]){(char)'a' + (square_num % 8), '\0'}, (char[2]){(char)'1' + (square_num / 8), '\0'}))
#define mirrored_square(i) ((NUMBER_OF_ROWS - get_row(i) - 1)*8 + get_column(i))

char fen_to_board(char *fen, board *b) 
{
    char modified_fen[100]; /* fen without '/', or numbers.  */
    char c1, c2, c3, c4;
    int i = 0, pointer_next_to_change = 0;
    char number_of_whitespaces = 0;
    char square;

    b->can_black_castle_long = 0;
    b->can_black_castle_short = 0;
    b->can_white_castle_long = 0;
    b->can_white_castle_short = 0;
    b->en_passant_pawn = 0;

    while (fen[i] != '\0' && number_of_whitespaces <= 5 /* If thats more than 5, than it's the end of the actual fen */)
    {   
        if (fen[i] == '/')
            i++;
        else if (fen[i] == '0')
            i++;
        else if ('1' <= fen[i] && fen[i] <= '9')
        {
            for (int j = 0; j < fen[i] - '0'; j++) {
                modified_fen[pointer_next_to_change] = '0';
                pointer_next_to_change++;
            }
            i++;
        }
        else 
        {
            if (fen[i] == ' ')
                number_of_whitespaces++;
            modified_fen[pointer_next_to_change] = fen[i];
            pointer_next_to_change++;
            i++;
        }
    }

    i = 0;
    fen = modified_fen;
    while (fen[i]!=' ')
    {   
        c1 = translate_piece_symbol(fen[i]); c2 = translate_piece_symbol(fen[i+1]);

        b->squares[mirrored_square(i)/2] = c1 << 4 | c2;
        i+=2;

    }
    i += 1;
    b->whos_turn = (fen[i] == 'w' ? WHITE : BLACK);
    i += 2;
    while (fen[i] != ' ')
    {
        switch (fen[i])
        {
        case 'K':
            b -> can_white_castle_short = 1;
            break;
        
        case 'Q':
            b -> can_white_castle_long = 1;
            break;

        case 'k':
            b -> can_black_castle_short = 1;
            break;
        
        case 'q':
            b -> can_black_castle_short = 1;
            break;

        default:
            break;
        }
        i++;
    }

    i++;
    if (b->whos_turn == WHITE)
        if (fen[i] != '-') {
            square = get_square_number(fen[i],fen[i+1]);
            b->en_passant_pawn = square + DOWN;
        }
    if (b->whos_turn == BLACK) {
        if (fen[i] != '-') {
            square = get_square_number(fen[i],fen[i+1]);
            b->en_passant_pawn = square + UP;
        }
    return 1;
    }
}

int player_move(board *the_board, char *str)
{
    /*ask for a move, validate it then comite the moveand request more info from user if needed*/
    int i = 0;
    char move_str[6];
    move all_moves[MAX_POSSIBLE_MOVES];
    char src_square, dst_square;
    move temp;

    /* If there is a whitespace - ignore what comes after it. */
    while (str[i] != '\0')
    {
        if (str[i] == ' ' || str[i] == '\n') {
            move_str[i] = '\0';
            break;
        }
        move_str[i] = str[i];
        i++;
    }
    move_str[i] = '\0';
    
    /* Check if the move is valid: */
    src_square = get_square_number(move_str[0], move_str[1]);
    if (check_src(the_board, src_square))
    {
        dst_square = get_square_number(move_str[2], move_str[3]);
        get_possible_moves(the_board,all_moves, 0 ,0 ,0);
        if (the_board->whos_turn == WHITE)
            i = 0;
        else
            i = MAX_POSSIBLE_MOVES / 2;
        while (all_moves[i] != END)
        {
            if (src_square == get_src_square(all_moves[i]) && dst_square == get_dst_square(all_moves[i]))
            {
                if (the_board->whos_turn == WHITE)
                {
                    if (get_piece_in_square(the_board, src_square) == white_pawn && get_row(src_square) == 6) {
                        create_a_move(temp, src_square, dst_square, translate_promotion(move_str[4]), 0, 0)
                        commit_a_move_for_white(the_board, temp);
                    }
                    else
                        commit_a_move_for_white(the_board, all_moves[i]);
                }
                else
                {
                    if (get_piece_in_square(the_board, src_square) == black_pawn && get_row(src_square) == 1) {
                        create_a_move(temp, src_square, dst_square, translate_promotion(move_str[4]), 0, 0)
                        commit_a_move_for_black(the_board, temp);
                    }
                    else
                        commit_a_move_for_black(the_board, all_moves[i]);
                }
                return 0;
            }
            i++;
        }
    }
    printf("invalid move\n");
}

/* Translate the promotion choice to what the engine underdstands: */
char translate_promotion(char promotion){
    switch (promotion)
    {
    case '0':
        return 'q';
    case '1':
        return 'r';
    case '2':
        return 'n';
    case '3':
        return 'b';
    case 'q':
        return 0;
    case 'r':
        return 1;
    case 'n':
        return 2;
    case 'b':
        return 3;
    }
}

/* Translate the piece symbol (P/N/B/R/Q/K) to what the engine underdstands: */
char translate_piece_symbol(char piece_symbol){
    switch (piece_symbol)
    {
    case '0': /* Our symbol for empty */
        return empty;

    case 'P':
        return white_pawn;
    case 'N':
        return white_knight;
    case 'B':
        return white_bishop;
    case 'R':
        return white_rook;
    case 'Q':
        return white_queen;
    case 'K':
        return white_king;

    case 'p':
        return black_pawn;
    case 'n':
        return black_knight;
    case 'b':
        return black_bishop;
    case 'r':
        return black_rook;
    case 'q':
        return black_queen;
    case 'k':
        return black_king;
    }
    return -1;
}


char check_bot_promotion(board *the_board, move the_move)
{
    int src_s = get_src_square(the_move);
    int src_r = get_row(src_s);
    int src_p = get_piece_in_square(the_board ,src_s);
    if(the_board->whos_turn == WHITE){
        if(src_p == white_pawn && src_r == 6)
            return translate_promotion(get_promotion_choice(the_move) + '0');
    }
    else {
        if(src_p == black_pawn && src_r == 1)
            return translate_promotion(get_promotion_choice(the_move) + '0');
    }
    return ' ';
}


void bot_move(board *the_board, HashTable *ht)
{
    move bot_move;
    int depth = 4;
    if (the_board->whos_turn == WHITE)
    {
        bot_move = get_best_move_white(the_board, depth, 0, ht);
        printf("bestmove %s%s%c\n", get_square_loc(get_src_square(bot_move)),get_square_loc(get_dst_square(bot_move)), check_bot_promotion(the_board, bot_move));
        commit_a_move_for_white(the_board, bot_move);
    }
    else
    {
        bot_move = get_best_move_black(the_board, depth, 0, ht);
        printf("bestmove %s%s%c\n", get_square_loc(get_src_square(bot_move)),get_square_loc(get_dst_square(bot_move)), check_bot_promotion(the_board, bot_move));
        commit_a_move_for_black(the_board, bot_move);
    }
    /*ht_clear(ht);*/
}

int check_endgame(board *the_board)
{
    move all_moves[MAX_POSSIBLE_MOVES];
    if (the_board->whos_turn == WHITE)
    {
        get_all_moves(the_board,all_moves);
        if (all_moves[0] == END)
        {
            if (is_attacked_by_black(the_board, find_king_square(the_board, WHITE)))
                printf("CHECKMATE 0-1\n");
            else
                printf("STALMATE 0.5-0.5\n");
            return 0;
        }
    }
    else
    {
        get_all_moves(the_board,all_moves);
        if (all_moves[0] == END)
        {
            if (is_attacked_by_white(the_board, find_king_square(the_board, BLACK)))
                printf("CHECKMATE 1-0\n");
            else
                printf("STALMATE 0.5-0.5\n");
            return 0;
        }
    }
    return 1;
}

int check_src(board *the_board, char src)
{
    /*validate src squear from user input*/
    if (get_piece_in_square(the_board, src) == empty)
        return 0;
    if (color_of_piece(src, the_board) != the_board->whos_turn)
        return 0;
    return 1;
}

void setup_start_board(board *b) 
{   
    int i;
    b->can_black_castle_long = 1;
    b->can_black_castle_short = 1;
    b->can_white_castle_long = 1;
    b->can_white_castle_short = 1;
    b->en_passant_pawn = 0;
    b->whos_turn = WHITE;
    for (i = 0; i < 32; i++)
        b->squares[i] = initial_board[i];
}

int uci_main()
{
    board b;
    setup_start_board(&b);
    HashTable ht;
    /* ht_setup(&ht, sizeof(board), sizeof(double), 100000000); */

	setbuf (stdin, NULL);
	setbuf (stdout, NULL);

	printf ("\nid name NepoChess\n");
	printf ("id author Elchai and Chaim\n");
	printf ("uciok\n");
	fflush (stdout);

	while(uci_parse(&b, &ht));

	return 0;
}

char line[10000];

char uci_parse(board *b, HashTable *ht)
{  
    fgets (line, 8192, stdin);  

	if (!strncmp (line, "isready", 7))
		printf ("readyok\n");

    if (!strncmp (line, "ucinewgame", 10));

    if (!strncmp (line, "position", 8))
	{
		char *posline = line + 9;

		if (!strncmp (posline, "startpos", 8))
		{
			setup_start_board(b);
		}
		else if (!strncmp (posline, "fen", 3))
		{
			fen_to_board(posline + 4, b);
		}

		/* need to make some moves on this position as well? */
		posline = strstr (line, "moves");

		if (posline)
		{
			posline += 6;

			while (1)
			{
                player_move(b,posline);

				posline = strstr (posline, " ");

				if (!posline)
					break;

				posline ++;
			}
		}
	}
    if (!strncmp (line, "go", 2))
	{
        print_board(b);
		bot_move(b,ht);
	}

    return 1;

}

//irreversible_move_info all_info[10000];
//long int top = 0;

void moves_in_depth(char d,board *b,move *all_moves_last_move, move last_move, irreversible_move_info inf) {
    move all_moves[200];
    move m;
    int i, j, temp2;
    move all_moves2[200];
    //board b2;
    //char fen[100] = "rnbqkbnr/ppp1pppp/8/3p4/Q1P5/8/PP1PPPPP/RNB1KBNR b KQkq - 1 2";
    irreversible_move_info temp;
    /*fen_to_board(fen, &b2);
    for (i = 0; i <= 31; i++) {
        if (b->squares[i] != b2.squares[i]) {
            break;
        }
        if (i == 31) {
            printf("\ngot it!\n");
            print_board(b);
        }
    } */
    print_board(b);
    if (d == 0) {
        moves++;
        return;
    }
    get_possible_moves(b,all_moves,all_moves_last_move, last_move, inf);
    get_all_moves(b,all_moves2);
    for (i = 0; i<100; i++) {
        for (j = 0; j<100; j++) {
            if (all_moves[i] == all_moves2[j]) {
                all_moves2[j] = -1;
                temp2 = 1;
                break;
            }
        }
        if (!temp2) {
            printf("moves not equal!\n\n\n");
            print_board(b);
            for (j = 0; all_moves[j] != END; j++) {
                printf("%c%d%c%d ", get_column(get_src_square(all_moves[j])) + 'a',get_row(get_src_square(all_moves[j])),get_column(get_dst_square(all_moves[j])) + 'a',get_row(get_dst_square(all_moves[j])) + 'a');
            }
            for (j = 100; all_moves[j] != END; j++) {
                printf("%c%d%c%d ", get_column(get_src_square(all_moves[j])) + 'a',get_row(get_src_square(all_moves[j])),get_column(get_dst_square(all_moves[j])) + 'a',get_row(get_dst_square(all_moves[j])) + 'a');
            }
            for (j = 0; all_moves2[j] != END; j++) {
                printf("%c%d%c%d ", get_column(get_src_square(all_moves2[j])) + 'a',get_row(get_src_square(all_moves2[j])),get_column(get_dst_square(all_moves2[j])) + 'a',get_row(get_dst_square(all_moves2[j])) + 'a');
            }
            for (j = 100; all_moves2[j] != END; j++) {
                printf("%c%d%c%d ", get_column(get_src_square(all_moves2[j])) + 'a',get_row(get_src_square(all_moves2[j])),get_column(get_dst_square(all_moves2[j])) + 'a',get_row(get_dst_square(all_moves2[j])) + 'a');
            }
            break;
        }
    }
    if (b->whos_turn == WHITE)
        i = 0;
    else
        i = 100;
    m = all_moves[i];
    while (m != END)
    {
        temp = get_irrev_move_info(b,m);
        if (b->whos_turn == WHITE){
            commit_a_move_for_white(b,m);
            moves_in_depth(d-1,b,all_moves,m,temp);
            unmake_move(b,m,temp);
        }
        else {
            commit_a_move_for_black(b,m);
            moves_in_depth(d-1,b,all_moves,m,temp);
            unmake_move(b,m,temp);
        }
        i++;
        m = all_moves[i];
    }
    if (d == 4) {
        printf("%ld",moves);
    }
    return;
}