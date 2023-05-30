#include "../include/minimax.h"

#define MAX_EVAL 100 /* The maximum evaluation possible. */
#define MIN_EVAL -100 /* The minimum evaluation possible. */

#define EVAL_TO_PRUNE 2 /* In what evaluation the minimax will cut the moves branch because it's too bad. */

long int number_of_moves = 0; /* The number of positions scaned. */
long int number_of_ht_found = 0; /* The number of positions found in the hash table. */
long int number_of_ht_inserted = 0; /* The number of positions inserted to the hash table. */
#define ASW_SIZE 1.0 /* The size of the aspiration window from each side of the guess. */

/* This function gets a board (when is white's move) and the depth and evaluates the position using minimax. */
minimax_eval evaluate_minimax_for_white(game *the_game, move *all_moves_last_move, move last_move, irreversible_move_info inf, char depth, double alpha, double beta, HashTable *ht) {
    move all_moves[MAX_POSSIBLE_MOVES];
    move prev_best = END; /* The best move in the position, in depth - 1. */
    int i = 0;
    minimax_eval temp;
    irreversible_move_info temp_inf;
    char is_check = 0;
    board *b = the_game->current_position;
    const void *tempvoid;
    move best;
    double max = MIN_EVAL;
    char is_pv_node = 0;
    number_of_moves++;
    int move_values[MAX_POSSIBLE_MOVES / 2]; /* The values of the moves. */
/*
    board k;
    char fen[100] = "8/3k4/3p4/p2P1p2/P1KP1P2/8/8/8 w - - 8 5";
    fen_to_board(fen, &k);
    if (compare_boards(&k,b) && depth == 3)
        printf("The board is the same!\n");
*/
    /* Search for the position in the hash table: */
    if (check_repetition(the_game))/* Repitition */ {
        _ht_insert_pos(ht, the_game, depth, END, 0, PV_NODE);
        create_a_minimax_eval(temp, 0, PV_NODE);
        return temp;
    }
    tempvoid = _ht_search_pos(ht, the_game, depth, CUT_NODE);
    if (tempvoid != NULL && (((ht_move_eval_struct *)tempvoid)->type ==PV_NODE || ((ht_move_eval_struct *)tempvoid)->eval >= beta)) { /* Make sure this would also be cutted. */
        number_of_ht_found++;
        create_a_minimax_eval(temp, ((ht_move_eval_struct *)tempvoid)->eval, ((ht_move_eval_struct *)tempvoid)->type);
        return (temp);
    }  
    if (is_attacked_by_black(b,find_king_square(b,WHITE))) { /* Checks if it's a check: */
        get_possible_moves(b,all_moves,all_moves_last_move, last_move, inf); /* Gets all the moves possible. */
        if (all_moves[0] == END) { /* If it's a mate: */
            _ht_insert_pos(ht, the_game, depth, END, MIN_EVAL, PV_NODE);
            create_a_minimax_eval(temp, MIN_EVAL, PV_NODE);
            return temp;
        }
        is_check = 1;
    }

    if (depth == 0) {
        create_a_minimax_eval(temp, evaluate_by_points(b), PV_NODE);
        _ht_insert_pos(ht, the_game, depth, END, temp.eval, PV_NODE);
        return temp;
    }
    if (!is_check) {
        get_possible_moves(b,all_moves,all_moves_last_move, last_move, inf); /* Gets all the moves possible. */
    }
    best = all_moves[0];
    if (all_moves[0] == 0)/* Stalmate */ {
        _ht_insert_pos(ht, the_game, depth, END, 0, PV_NODE);
        create_a_minimax_eval(temp, 0, PV_NODE);
        return temp;
    }
    order_moves(the_game, all_moves, move_values, depth, ht); /* Orders the moves. */
    while (all_moves[i] != 0) {
        selection_sort_for_moves(all_moves, move_values, i); /* Sorts the moves. */
        temp_inf = get_irrev_move_info(b,all_moves[i]);
        commit_a_move_for_white_in_game(the_game,all_moves[i]); /* Commits the move. */
        temp = evaluate_minimax_for_black(the_game, all_moves, all_moves[i], temp_inf,depth - 1,alpha, beta, ht);
        unmake_move_in_game(the_game,all_moves[i],temp_inf);
        if (temp.eval >= beta) {
            _ht_insert_pos(ht, the_game, depth, all_moves[i], temp.eval, CUT_NODE);
            create_a_minimax_eval(temp, beta, CUT_NODE);
            return temp;
        }
        if (temp.eval > alpha) {
            alpha = temp.eval;
            is_pv_node = 1;
        }
        if (temp.eval > max) {
            max = temp.eval;
            best = all_moves[i];
        }

        i++;
    }
    if (is_pv_node) {
        _ht_insert_pos(ht, the_game, depth, best, alpha, PV_NODE);
        create_a_minimax_eval(temp, alpha, PV_NODE);
    }
    else {
        _ht_insert_pos(ht, the_game, depth, best, alpha, CUT_NODE);
        create_a_minimax_eval(temp, alpha, CUT_NODE);
    }
    return temp;
}
/* This function gets a board (when is black's move) and the depth and evaluates the position using minimax. */
minimax_eval evaluate_minimax_for_black(game *the_game, move *all_moves_last_move, move last_move, irreversible_move_info inf, char depth, double alpha, double beta, HashTable *ht) {
    board *b = the_game->current_position;
    move all_moves[MAX_POSSIBLE_MOVES];
    move prev_best = END; /* The best move in the position, in depth - 1. */
    int i = MAX_POSSIBLE_MOVES / 2;
    minimax_eval temp;
    irreversible_move_info temp_inf;
    char is_check = 0;
    const void *tempvoid;
    move best;
    double min = MAX_EVAL;
    char is_pv_node = 0;
    number_of_moves++;
    int move_values[MAX_POSSIBLE_MOVES / 2]; /* The values of the moves. */

    if (check_repetition(the_game))/* Repitition */ {
        _ht_insert_pos(ht, the_game, depth, END, 0, PV_NODE);
        create_a_minimax_eval(temp, 0, PV_NODE);
        return temp;
    }
    /*board k;
    char fen[100] = "2k5/8/3p4/p2P1p2/P1KP1P2/8/8/8 b - - 7 4";
    fen_to_board(fen, &k);
    if (compare_boards(&k,b) && depth == 4)
        printf("The board is the same!\n");*/

    /* Search for the position in the hash table: */
    tempvoid = _ht_search_pos(ht, the_game, depth, ALL_NODE);
    if (tempvoid != NULL && (((ht_move_eval_struct *)tempvoid)->type ==PV_NODE || ((ht_move_eval_struct *)tempvoid)->eval <= alpha)) { /* Make sure this would also be cutted. */
        number_of_ht_found++;
        create_a_minimax_eval(temp, ((ht_move_eval_struct *)tempvoid)->eval, ((ht_move_eval_struct *)tempvoid)->type);
        return (temp);
    }  
    if (is_attacked_by_white(b,find_king_square(b,BLACK))) { /* Checks if it's a check: */
        get_possible_moves(b,all_moves,all_moves_last_move, last_move, inf); /* Gets all the moves possible. */
        if (all_moves[MAX_POSSIBLE_MOVES / 2] == END) { /* If it's a mate: */
            _ht_insert_pos(ht, the_game, depth, END, MAX_EVAL, PV_NODE);
            create_a_minimax_eval(temp, MAX_EVAL, PV_NODE);
            return temp;
        }
        is_check = 1;
    }
    if (depth == 0) {
        create_a_minimax_eval(temp, evaluate_by_points(b), PV_NODE);
        _ht_insert_pos(ht, the_game, depth, END, temp.eval, PV_NODE);
        return temp;
    }
    if (!is_check) {
        get_possible_moves(b,all_moves,all_moves_last_move, last_move, inf); /* Gets all the moves possible. */
    }
    best = all_moves[MAX_POSSIBLE_MOVES / 2];

    if (all_moves[MAX_POSSIBLE_MOVES / 2] == END) { /* If it's a draw: */
        _ht_insert_pos(ht, the_game, depth, END, 0, PV_NODE);
        create_a_minimax_eval(temp, 0, PV_NODE);
        return temp;
    }
    order_moves(the_game, all_moves, move_values, depth, ht); /* Orders the moves. */
    while (all_moves[i] != 0) {
        selection_sort_for_moves(all_moves + MAX_POSSIBLE_MOVES/2, move_values, i-MAX_POSSIBLE_MOVES/2); /* Sorts the moves. */
        temp_inf = get_irrev_move_info(b,all_moves[i]);
        commit_a_move_for_black_in_game(the_game,all_moves[i]); /* Commits the move. */
        temp = evaluate_minimax_for_white(the_game, all_moves, all_moves[i], temp_inf, depth - 1,alpha, beta, ht); /* Checks what is the eval after the move. */
        unmake_move_in_game(the_game,all_moves[i],temp_inf);
        if (temp.eval <= alpha) {
            _ht_insert_pos(ht, the_game, depth, all_moves[i], temp.eval, ALL_NODE);
            create_a_minimax_eval(temp, alpha, ALL_NODE);
            return temp;
        }
        if (temp.eval < beta) {
            beta = temp.eval;
            is_pv_node = 1;
        }
        if (temp.eval < min) {
            min = temp.eval;
            best = all_moves[i];
        }
        i++;
    }
    //print_board(b);
    if (is_pv_node) {
        _ht_insert_pos(ht, the_game, depth, best, min, PV_NODE);
        create_a_minimax_eval(temp, min, PV_NODE);
    }
    else {
        _ht_insert_pos(ht, the_game, depth, best, min, ALL_NODE);
        create_a_minimax_eval(temp, min, ALL_NODE);
    }
    return temp;
}

/* The main function of minimax for white, returns the best move of the position. */
move get_best_move_white(game *the_game,char depth, move *all_moves_already_calculated, char use_asw, HashTable *ht) {
    board *b = the_game->current_position;
    move all_moves[MAX_POSSIBLE_MOVES]; /* All the moves possible in the position. */
    int i = 0;
    int j;
    char kings = 0;
    double max = MIN_EVAL; /* The maximun eval possible in the position(maximum = best for white). */
    move prev_best = END; /* The best move in the position, in depth - 1. */
    minimax_eval temp;
    move best;
    irreversible_move_info temp_inf;
    const void *tempvoid = 0;
    double alpha = 2 * MIN_EVAL;
    double beta = 2 * MAX_EVAL;
    char is_fail = 1; /* Did the search fail? needed when using aspiration windows. */
    number_of_moves++;
    int move_values[MAX_POSSIBLE_MOVES / 2]; /* The values of the moves. */
/*
    board k;
    char fen[100] = "8/6k1/3p4/p2P1K2/P2P1P2/8/8/8 b - - 0 13";
    fen_to_board(fen, &k);
    if (compare_boards(&k,b))
        printf("The board is the same!\n");*/
    if (use_asw == 1) { /* We need to use an aspiration window: */
        tempvoid = _ht_search_pos(ht, the_game, depth - 1, PV_NODE); /* A guess of the evaluation based on the previous iteration. */
        if (tempvoid != NULL) {
            double guess = ((ht_move_eval_struct *)tempvoid)->eval;
            alpha = guess - ASW_SIZE;
            beta = guess + ASW_SIZE;
        }
    }
    if (all_moves_already_calculated == 0) {/* If the moves weren't already calculated. */
        get_possible_moves(b,all_moves,0, 0, 0); /* Gets all the moves possible (but there is no "last move"). */
    }
    else { /* Else - copy the moves. */
        for (j = 0; j < MAX_POSSIBLE_MOVES; j++) {
            all_moves[j] = all_moves_already_calculated[j];
        }
    }
    best = all_moves[0]; /* The default best move in the position. */
    //print_board(b);
    if (is_attacked_by_black(b,find_king_square(b,WHITE))) { 
        if (all_moves[0] == END) {
            return MIN_EVAL;
        }
    }

    order_moves(the_game,all_moves,move_values, depth, ht); /* Orders the moves. */
    while (all_moves[i] != 0) {
        selection_sort_for_moves(all_moves, move_values, i); /* Sorts the moves. */
        temp_inf = get_irrev_move_info(b,all_moves[i]);
        commit_a_move_for_white_in_game(the_game,all_moves[i]); /* Commits the move. */
        temp = evaluate_minimax_for_black(the_game, all_moves, all_moves[i], temp_inf,depth - 1, max, beta, ht); /* Checks what is the eval after the move. */
        unmake_move_in_game(the_game,all_moves[i],temp_inf);
        if (temp.eval > max) { /* If the eval is better then the max eval: */
            max = temp.eval; /* Changes max to be it. */
            best = all_moves[i];
        }
        if (temp.type == PV_NODE) {
            is_fail = 0;
        }
        i++;
    }
    //print_board(b);
    if (is_fail == 1 && use_asw == 1) { /* If the search failed and we used an aspiration window: */
        best = get_best_move_white(the_game, depth, all_moves_already_calculated, 0, ht); /* Do the search again without the window. */
    }
    _ht_insert_pos(ht, the_game, depth, best, max, PV_NODE);
    return best;
}

/* The main function of minimax for black, returns the best move of the position. */
move get_best_move_black(game *the_game,char depth, move *all_moves_already_calculated, char use_asw, HashTable *ht) {
    board *b = the_game->current_position;
    move all_moves[MAX_POSSIBLE_MOVES]; /* All the moves possible in the position. */
    int i = MAX_POSSIBLE_MOVES / 2;
    int j = 0;
    char kings = 0;
    double min = MAX_EVAL; /* The maximun eval possible in the position(maximum = best for white). */
    move best; /* The best move in the position. */
    move prev_best = END; /* The best move in the position, in depth - 1. */
    minimax_eval temp;
    irreversible_move_info temp_inf;
    const void *tempvoid = 0;
    double alpha = 2 * MIN_EVAL;
    double beta = 2 *MAX_EVAL;
    char is_fail = 1; /* Did the search fail? needed when using aspiration windows. */
    number_of_moves++;
    int move_values[MAX_POSSIBLE_MOVES / 2]; /* The values of the moves. */
    /*
    board k;
    char fen[100] = "8/6k1/3p4/p2P1K2/P2P1P2/8/8/8 b - - 0 13";
    fen_to_board(fen, &k);
    if (compare_boards(&k,b))
        printf("The board is the same!\n");
        */
    
    if (use_asw == 1) { /* We need to use an aspiration window: */
        tempvoid = _ht_search_pos(ht, the_game, depth - 1, PV_NODE); /* A guess of the evaluation based on the previous iteration. */
        if (tempvoid != NULL) {
            double guess = ((ht_move_eval_struct *)tempvoid)->eval;
            alpha = guess - ASW_SIZE;
            beta = guess + ASW_SIZE;
        }
    }

    if (all_moves_already_calculated == 0) {/* If the moves weren't already calculated. */
        get_possible_moves(b,all_moves,0, 0, 0); /* Gets all the moves possible (but there is no "last move"). */
    }
    else { /* Else - copy the moves. */
        for (j = 0; j < MAX_POSSIBLE_MOVES; j++) {
            all_moves[j] = all_moves_already_calculated[j];
        }
    }
    best = all_moves[i]; /* The default move . */
    /* Check black has 2 kings: (If there are, thats an error)*/
    

    if (is_attacked_by_white(b,find_king_square(b,BLACK))) {
        if (all_moves[MAX_POSSIBLE_MOVES / 2] == END) {
            return MAX_EVAL;
        }
    }
    order_moves(the_game, all_moves, move_values, depth, ht);
    while (all_moves[i] != END) {
        /* Make a selection sort in all_moves, using the values of the moves: */
        selection_sort_for_moves(all_moves + MAX_POSSIBLE_MOVES/2, move_values, i - MAX_POSSIBLE_MOVES/2);
        temp_inf = get_irrev_move_info(b,all_moves[i]);
        commit_a_move_for_black_in_game(the_game,all_moves[i]); /* Commits the move. */
        temp = evaluate_minimax_for_white(the_game, all_moves, all_moves[i], temp_inf, depth - 1, alpha, min, ht); /* Checks what is the eval after the move. */
        unmake_move_in_game(the_game,all_moves[i],temp_inf);
        if (temp.eval < min) { /* If the eval is better then the max eval: */
            min = temp.eval; /* Changes max to be it. */
            best = all_moves[i];
        }
        if (temp.type == PV_NODE) {
            is_fail = 0;
        }
        i++;
    }
    if (is_fail == 1 && use_asw == 1) { /* If the search failed and we used an aspiration window: */
        best = get_best_move_black(the_game, depth, all_moves, 0, ht);
    }
    _ht_insert_pos(ht, the_game, depth, best, min, PV_NODE);
    return best;
}

void order_moves(game *g, move *all_moves, int *move_values, char depth, HashTable *ht) {
    /* We need to order the moves so the moves expected to be better will be first: */
    move hash_move;
    char temp;
    const void *tempvoid;
    board *the_board = g->current_position;
    if (the_board->whose_turn == WHITE)
        tempvoid = _ht_search_pos(ht, g, depth-1, CUT_NODE);
    else
        tempvoid = _ht_search_pos(ht, g, depth-1, ALL_NODE);
    if (tempvoid != NULL && ((ht_move_eval_struct *)tempvoid)->best_move != END) {
        hash_move = ((ht_move_eval_struct *)tempvoid)->best_move;
    }  
    else if (depth > 1){
        if (the_board->whose_turn == WHITE)
            hash_move = get_best_move_white(g, depth-1, all_moves, 0, ht);
        else
            hash_move = get_best_move_black(g, depth-1, all_moves, 0, ht);
    }

    /* Go through all the moves and assign values: */
    int j = the_board->whose_turn == WHITE ? 0 : MAX_POSSIBLE_MOVES / 2;
    for (int i = j; i < j + MAX_POSSIBLE_MOVES / 2; i++) {
        move_values[i - j] = 0;
        if (all_moves[i] == hash_move) {
            move_values[i - j] = 10000;
            continue;
        }
        if ((temp = get_piece_in_square(the_board,get_dst_square(all_moves[i]))) != empty) {
            move_values[i - j] = (temp - get_piece_in_square(the_board,get_src_square(all_moves[i]))) * 25; /* The value is higher when a valueable piece is captured by less valueable piece. */
        }
        if (get_piece_in_square(the_board,get_src_square(all_moves[i])) == white_pawn && get_row(get_dst_square(all_moves[i])) == 7) {
            move_values[i -j] += get_promotion_choice(all_moves[i]) * 4; /* Promoting is good. */
        }
        if ((the_board->whose_turn == WHITE && ((!pass_up(temp = get_dst_square(all_moves[i])) && !pass_left(temp) 
            && get_piece_in_square(the_board ,temp+UP_LEFT) == black_pawn)
            || (!pass_up(temp) && !pass_right(temp) && get_piece_in_square(the_board ,temp+UP_RIGHT) == black_pawn)))
            || (the_board->whose_turn == BLACK && ((!pass_down(temp = get_dst_square(all_moves[i])) && !pass_left(temp)
            && get_piece_in_square(the_board ,temp+DOWN_LEFT) == white_pawn)
            || (!pass_down(temp) && !pass_right(temp) && get_piece_in_square(the_board ,temp+DOWN_RIGHT) == white_pawn)))) {
                move_values[i - j] -= 50; /* moving to a square that is attacked by an enemy pawn is bad. */
        }
    }
}