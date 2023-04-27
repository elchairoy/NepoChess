#include "../include/minimax.h"

#define MAX_EVAL 100 /* The maximum evaluation possible. */
#define MIN_EVAL -100 /* The minimum evaluation possible. */

#define EVAL_TO_PRUNE 2 /* In what evaluation the minimax will cut the moves branch because it's too bad. */

long int number_of_moves = 0; /* The number of positions scaned. */
long int number_of_ht_found = 0; /* The number of positions found in the hash table. */
long int number_of_ht_inserted = 0; /* The number of positions inserted to the hash table. */

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

    /* Search for the position in the hash table: */
    tempvoid = _ht_search_pos(ht, the_game, depth, CUT_NODE);
    if (tempvoid != NULL) {
        number_of_ht_found++;
        create_a_minimax_eval(temp, ((ht_move_eval_struct *)tempvoid)->eval, ((ht_move_eval_struct *)tempvoid)->type);
        return (temp);
    }  
    if (is_attacked_by_black(b,find_king_square(b,WHITE))) { /* Checks if it's a check: */
        get_possible_moves(b,all_moves,all_moves_last_move, last_move, inf); /* Gets all the moves possible. */
        if (all_moves[0] == END) { /* If it's a mate: */
            number_of_moves++;
            _ht_insert_pos(ht, the_game, depth, END, MIN_EVAL, PV_NODE);
            create_a_minimax_eval(temp, MIN_EVAL, PV_NODE);
            return temp;
        }
        is_check = 1;
    }

    if (depth == 0) {
        number_of_moves++;
        create_a_minimax_eval(temp, evaluate_by_points(b), PV_NODE);
        _ht_insert_pos(ht, the_game, depth, END, temp.eval, PV_NODE);
        return temp;
    }
    if (!is_check) {
        get_possible_moves(b,all_moves,all_moves_last_move, last_move, inf); /* Gets all the moves possible. */
    }
    best = all_moves[0];
    if (all_moves[0] == 0 || check_repetition(the_game))/* Stalmate */ {
        number_of_moves++;
        _ht_insert_pos(ht, the_game, depth, END, 0, PV_NODE);
        create_a_minimax_eval(temp, 0, PV_NODE);
        return temp;
    }

    if (depth > 1) {
        tempvoid = _ht_search_pos(ht, the_game, depth-1, PV_NODE);
        if (tempvoid != NULL && ((ht_move_eval_struct *)tempvoid)->best_move != END) {
            number_of_ht_found++;
            prev_best = ((ht_move_eval_struct *)tempvoid)->best_move;
        }  
        else {
            prev_best = get_best_move_white(the_game, depth - 1, all_moves, ht);
        }
        temp_inf = get_irrev_move_info(b,prev_best);
        commit_a_move_for_white_in_game(the_game,prev_best);
        temp.eval = evaluate_minimax_for_black(the_game, all_moves, prev_best, temp_inf,depth - 1,alpha, beta, ht).eval;
        unmake_move_in_game(the_game,prev_best,temp_inf);
        if (temp.eval >= beta) {
            _ht_insert_pos(ht, the_game, depth, prev_best, beta, CUT_NODE);
            create_a_minimax_eval(temp, beta, CUT_NODE);
            return temp;
        }
        if (temp.eval > alpha) {
            alpha = temp.eval;
        }
        if (temp.eval > max) {
            max = temp.eval;
            best = prev_best;
        }
    }

    while (all_moves[i] != 0) {
        //print_board(b);
        if (all_moves[i] == prev_best) {
            i++; continue;
        }
        temp_inf = get_irrev_move_info(b,all_moves[i]);
        commit_a_move_for_white_in_game(the_game,all_moves[i]); /* Commits the move. */
        temp.eval = evaluate_minimax_for_black(the_game, all_moves, all_moves[i], temp_inf,depth - 1,alpha, beta, ht).eval;
        unmake_move_in_game(the_game,all_moves[i],temp_inf);

        if (temp.eval >= beta) {
            _ht_insert_pos(ht, the_game, depth, best, beta, CUT_NODE);
            create_a_minimax_eval(temp, beta, CUT_NODE);
            return temp;
        }
        if (temp.eval > alpha) {
            alpha = temp.eval;
        }
        if (temp.eval > max) {
            max = temp.eval;
            best = all_moves[i];
        }

        i++;
    }
    _ht_insert_pos(ht, the_game, depth, best, alpha, PV_NODE);
    create_a_minimax_eval(temp, alpha, PV_NODE);
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
    //print_board(b);
/*
    board v;
    fen_to_board("rnbqkbnr/pppp1ppp/8/4p3/8/2N2N2/PPPPPPPP/R1BQKB1R b KQkq - 1 2", &v);
    if (compare_boards(b,&v)) {
        printf("GOT IT!\n");
    }
*/
    /* Search for the position in the hash table: */
    tempvoid = _ht_search_pos(ht, the_game, depth, ALL_NODE);
    if (tempvoid != NULL) {
        number_of_ht_found++;
        create_a_minimax_eval(temp, ((ht_move_eval_struct *)tempvoid)->eval, ((ht_move_eval_struct *)tempvoid)->type);
        return (temp);
    }  
    //print_board(b);
    if (is_attacked_by_white(b,find_king_square(b,BLACK))) { /* Checks if it's a check: */
        get_possible_moves(b,all_moves,all_moves_last_move, last_move, inf); /* Gets all the moves possible. */
        if (all_moves[MAX_POSSIBLE_MOVES / 2] == END) { /* If it's a mate: */
            number_of_moves++;
            _ht_insert_pos(ht, the_game, depth, END, MAX_EVAL, PV_NODE);
            create_a_minimax_eval(temp, MAX_EVAL, PV_NODE);
            return temp;
        }
        is_check = 1;
    }
    if (depth == 0) {
        number_of_moves++;
        create_a_minimax_eval(temp, evaluate_by_points(b), PV_NODE);
        _ht_insert_pos(ht, the_game, depth, END, temp.eval, PV_NODE);
        return temp;
    }
    if (!is_check) {
        get_possible_moves(b,all_moves,all_moves_last_move, last_move, inf); /* Gets all the moves possible. */
    }
    best = all_moves[MAX_POSSIBLE_MOVES / 2];

    if (all_moves[MAX_POSSIBLE_MOVES / 2] == END) { /* If it's a draw: */
        number_of_moves++;
        _ht_insert_pos(ht, the_game, depth, END, 0, PV_NODE);
        create_a_minimax_eval(temp, 0, PV_NODE);
        return temp;
    }
    //print_board(b);
    if (depth > 1) {
        tempvoid = _ht_search_pos(ht, the_game, depth-1, PV_NODE);
        if (tempvoid != NULL && ((ht_move_eval_struct *)tempvoid)->best_move != END) {
            number_of_ht_found++;
            prev_best = ((ht_move_eval_struct *)tempvoid)->best_move;
        }  
        else {
            prev_best = get_best_move_black(the_game, depth-1, all_moves, ht);
        }
        temp_inf = get_irrev_move_info(b,prev_best);
        commit_a_move_for_black_in_game(the_game,prev_best);
        temp.eval = evaluate_minimax_for_white(the_game, all_moves, prev_best, temp_inf,depth - 1,alpha, beta, ht).eval;
        unmake_move_in_game(the_game,prev_best,temp_inf);
        if (temp.eval <= alpha) {
            _ht_insert_pos(ht, the_game, depth, best, alpha, ALL_NODE);
            create_a_minimax_eval(temp, alpha, ALL_NODE);
            return temp;
        }
        if (temp.eval < beta) {
            beta = temp.eval;
        }
        if (temp.eval < min) {
            min = temp.eval;
            best = prev_best;
        }
    }

    while (all_moves[i] != 0) {
        if (all_moves[i] == prev_best) {
            i++; continue;
        }
        temp_inf = get_irrev_move_info(b,all_moves[i]);
        commit_a_move_for_black_in_game(the_game,all_moves[i]); /* Commits the move. */
        temp.eval = evaluate_minimax_for_white(the_game, all_moves, all_moves[i], temp_inf, depth - 1,alpha, beta, ht).eval; /* Checks what is the eval after the move. */
        unmake_move_in_game(the_game,all_moves[i],temp_inf);
        //print_board(b);
        if (temp.eval <= alpha) {
            _ht_insert_pos(ht, the_game, depth, best, alpha, ALL_NODE);
            create_a_minimax_eval(temp, alpha, ALL_NODE);
            return temp;
        }
        if (temp.eval < beta) {
            beta = temp.eval;
        }
        if (temp.eval < min) {
            min = temp.eval;
            best = all_moves[i];
        }

        i++;
    }
    //print_board(b);
    _ht_insert_pos(ht, the_game, depth, best, beta, PV_NODE);
    create_a_minimax_eval(temp, beta, PV_NODE);
    return temp;
}

/* The main function of minimax for white, returns the best move of the position. */
move get_best_move_white(game *the_game,char depth, move *all_moves_already_calculated, HashTable *ht) {
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
    const void *tempvoid;

    if (all_moves_already_calculated == 0){ /* If the moves weren't already calculated. */
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
            number_of_moves++;
            return MIN_EVAL;
        }
    }
    if (depth > 1){
        tempvoid = _ht_search_pos(ht, the_game, depth-1, PV_NODE);
        if (tempvoid != NULL && ((ht_move_eval_struct *)tempvoid)->best_move != END) {
            number_of_ht_found++;
            prev_best = ((ht_move_eval_struct *)tempvoid)->best_move;
        }  
        else {
            prev_best = get_best_move_white(the_game, depth-1, all_moves, ht);
        }
        temp_inf = get_irrev_move_info(b,prev_best);
        commit_a_move_for_white_in_game(the_game,prev_best);
        temp.eval = evaluate_minimax_for_black(the_game, all_moves, prev_best, temp_inf,depth - 1, MIN_EVAL, MAX_EVAL, ht).eval;
        unmake_move_in_game(the_game,prev_best,temp_inf);
        if (temp.eval > max) {
            max = temp.eval;
            best = prev_best;
        }
    }
    //print_board(b);
    while (all_moves[i] != 0) {
        if (all_moves[i] == prev_best) {
            i++; continue;
        }
        //print_board(b);
        temp_inf = get_irrev_move_info(b,all_moves[i]);
        commit_a_move_for_white_in_game(the_game,all_moves[i]); /* Commits the move. */
        temp.eval = evaluate_minimax_for_black(the_game, all_moves, all_moves[i], temp_inf,depth - 1, max, MAX_EVAL, ht).eval; /* Checks what is the eval after the move. */
        unmake_move_in_game(the_game,all_moves[i],temp_inf);
        if (temp.eval > max) { /* If the eval is better then the max eval: */
            max = temp.eval; /* Changes max to be it. */
            best = all_moves[i];
        }
        i++;
    }
    //print_board(b);
    _ht_insert_pos(ht, the_game, depth, best, max, PV_NODE);
    if (depth == 5) {
        printf("no_of_ht_found = %ld\n",number_of_ht_found);
        printf("no_of_ht_inserted = %ld\n",number_of_ht_inserted);
        printf("number of moves = %ld\n",number_of_moves);
        //printf("Eval= %lf\n",max);
    }
    //printf("no_of_moves = %ld\n",number_of_moves);
    return best;
}

/* The main function of minimax for black, returns the best move of the position. */
move get_best_move_black(game *the_game,char depth, move *all_moves_already_calculated, HashTable *ht) {
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
    const void *tempvoid;

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
            number_of_moves++;
            return MAX_EVAL;
        }
    }
    if (depth > 1){
        tempvoid = _ht_search_pos(ht, the_game, depth-1, PV_NODE);
        if (tempvoid != NULL && ((ht_move_eval_struct *)tempvoid)->best_move != END) {
            number_of_ht_found++;
            prev_best = ((ht_move_eval_struct *)tempvoid)->best_move;
        }  
        else {
            prev_best = get_best_move_black(the_game, depth-1, all_moves, ht);
        }
        temp_inf = get_irrev_move_info(b,prev_best);
        commit_a_move_for_black_in_game(the_game,prev_best);
        temp.eval = evaluate_minimax_for_white(the_game, all_moves, prev_best, temp_inf, depth - 1, MIN_EVAL, MAX_EVAL, ht).eval;
        unmake_move_in_game(the_game,prev_best,temp_inf);
        if (temp.eval < min) {
            min = temp.eval;
            best = prev_best;
        }
    }
    while (all_moves[i] != END) {
        if (all_moves[i] == prev_best) {
            i++; continue;
        }
        //print_board(b);
        temp_inf = get_irrev_move_info(b,all_moves[i]);
        commit_a_move_for_black_in_game(the_game,all_moves[i]); /* Commits the move. */
        temp.eval = evaluate_minimax_for_white(the_game, all_moves, all_moves[i], temp_inf, depth - 1, MIN_EVAL, min, ht).eval; /* Checks what is the eval after the move. */
        unmake_move_in_game(the_game,all_moves[i],temp_inf);

        if (temp.eval < min) { /* If the eval is better then the max eval: */
            min = temp.eval; /* Changes max to be it. */
            best = all_moves[i];
        }
        i++;
    }
    _ht_insert_pos(ht, the_game, depth, best, min, PV_NODE);
    if (depth == 5) {
        printf("no_of_ht_found = %ld\n",number_of_ht_found);
        printf("no_of_ht_inserted = %ld\n",number_of_ht_inserted);
        printf("number of moves = %ld\n",number_of_moves);
        //printf("Eval= %lf\n",min);
    }
    //printf("number of moves = %ld\n",number_of_moves);
    return best;
}