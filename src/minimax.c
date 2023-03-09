#include "../include/minimax.h"

#define MAX_EVAL 100 /* The maximum evaluation possible. */
#define MIN_EVAL -100 /* The minimum evaluation possible. */

#define EVAL_TO_PRUNE 2 /* In what evaluation the minimax will cut the moves branch because it's too bad. */

long int number_of_moves = 0; /* The number of positions scaned. */

/* This function gets a board (when is white's move) and the depth and evaluates the position using minimax. */
double evaluate_minimax_for_white(game *the_game, move *all_moves_last_move, move last_move, irreversible_move_info inf, char depth, double alpha, double beta) {
    move all_moves[MAX_POSSIBLE_MOVES];
    move prev_best = END; /* The best move in the position, in depth - 1. */
    int i = 0;
    double temp;
    irreversible_move_info temp_inf;
    char is_check = 0;
    board *b = the_game->current_position;
    
    if (is_attacked_by_black(b,find_king_square(b,WHITE))) { /* Checks if it's a check: */
        get_possible_moves(b,all_moves,all_moves_last_move, last_move, inf); /* Gets all the moves possible. */
        if (all_moves[0] == END) { /* If it's a mate: */
            number_of_moves++;
            return MIN_EVAL;
        }
        is_check = 1;
    }
    if (depth == 0) {
        number_of_moves++;
        return evaluate_by_points(b);
    }
    if (!is_check) {
        get_possible_moves(b,all_moves,all_moves_last_move, last_move, inf); /* Gets all the moves possible. */
    }
    if (depth > 1) {
        prev_best = get_best_move_white(the_game, depth-1, all_moves);
        temp_inf = get_irrev_move_info(b,prev_best);
        commit_a_move_for_white_in_game(the_game,prev_best);
        temp = evaluate_minimax_for_black(the_game, all_moves, prev_best, temp_inf,depth - 1,alpha, beta);
        unmake_move_in_game(the_game,prev_best,temp_inf);
        if (temp >= beta)
            return beta;
        if (temp > alpha) 
            alpha = temp;
    }

    if (all_moves[0] == 0 || check_repetition(the_game))/* Stalmate */
        alpha = 0;

    while (all_moves[i] != 0) {
        //print_board(b);
        if (all_moves[i] == prev_best) {
            i++; continue;
        }
        temp_inf = get_irrev_move_info(b,all_moves[i]);
        commit_a_move_for_white_in_game(the_game,all_moves[i]); /* Commits the move. */
        temp = evaluate_minimax_for_black(the_game, all_moves, all_moves[i], temp_inf,depth - 1,alpha, beta);
        unmake_move_in_game(the_game,all_moves[i],temp_inf);

        if (temp >= beta) {
            return beta;
        }

        if (temp > alpha) 
            alpha = temp;

        i++;
    }
    return alpha;
}

/* This function gets a board (when is black's move) and the depth and evaluates the position using minimax. */
double evaluate_minimax_for_black(game *the_game, move *all_moves_last_move, move last_move, irreversible_move_info inf, char depth, double alpha, double beta) {
    board *b = the_game->current_position;
    move all_moves[MAX_POSSIBLE_MOVES];
    move prev_best = END; /* The best move in the position, in depth - 1. */
    int i = MAX_POSSIBLE_MOVES / 2;
    double temp;
    irreversible_move_info temp_inf;
    char is_check = 0;
    //print_board(b);

    if (is_attacked_by_white(b,find_king_square(b,BLACK))) { /* Checks if it's a check: */
        get_possible_moves(b,all_moves,all_moves_last_move, last_move, inf); /* Gets all the moves possible. */
        if (all_moves[MAX_POSSIBLE_MOVES / 2] == END) { /* If it's a mate: */
            number_of_moves++;
            return MAX_EVAL;
        }
        is_check = 1;
    }
    if (depth == 0) {
        number_of_moves++;
        return evaluate_by_points(b);
    }
    if (!is_check) {
        get_possible_moves(b,all_moves,all_moves_last_move, last_move, inf); /* Gets all the moves possible. */
    }
    if (depth > 1) {
        prev_best = get_best_move_black(the_game, depth-1, all_moves);
        temp_inf = get_irrev_move_info(b,prev_best);
        commit_a_move_for_black_in_game(the_game,prev_best);
        temp = evaluate_minimax_for_white(the_game, all_moves, prev_best, temp_inf,depth - 1,alpha, beta);
        unmake_move_in_game(the_game,prev_best,temp_inf);
        if (temp <= alpha)
            return alpha;
        if (temp < beta) 
            beta = temp;
    }
    if (all_moves[0] == 0 || check_repetition(the_game))/* Stalmate */
        beta = 0;

    while (all_moves[i] != 0) {
        if (all_moves[i] == prev_best) {
            i++; continue;
        }
        temp_inf = get_irrev_move_info(b,all_moves[i]);
        commit_a_move_for_black_in_game(the_game,all_moves[i]); /* Commits the move. */
        temp = evaluate_minimax_for_white(the_game, all_moves, all_moves[i], temp_inf, depth - 1,alpha, beta); /* Checks what is the eval after the move. */
        unmake_move_in_game(the_game,all_moves[i],temp_inf);

        if (temp <= alpha) {
            return alpha;
        }

        if (temp < beta) 
            beta = temp;

        i++;
    }
    return beta;
}

/* The main function of minimax for white, returns the best move of the position. */
move get_best_move_white(game *the_game,char depth, move *all_moves_already_calculated) {
    board *b = the_game->current_position;
    move all_moves[MAX_POSSIBLE_MOVES]; /* All the moves possible in the position. */
    int i = 0;
    int j;
    char kings = 0;
    double max = MIN_EVAL; /* The maximun eval possible in the position(maximum = best for white). */
    move prev_best = END; /* The best move in the position, in depth - 1. */
    double temp;
    move best;
    irreversible_move_info temp_inf;
    /* Check white has 2 kings: (If there are, thats an error)*/
    /*for (j = 0; j < 64; j++) {
        if (get_piece_in_square(b,j) == white_king) {
            kings++;
        }
    }
    if (kings == 2 || kings == 0) {
        printf("Error: White has 2/0 kings");
        //print_board(b);
    }*/
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
        prev_best = get_best_move_white(the_game, depth-1, all_moves);
        temp_inf = get_irrev_move_info(b,prev_best);
        commit_a_move_for_white_in_game(the_game,prev_best);
        temp = evaluate_minimax_for_black(the_game, all_moves, prev_best, temp_inf,depth - 1, MIN_EVAL, MAX_EVAL);
        unmake_move_in_game(the_game,prev_best,temp_inf);
        if (temp > max) {
            max = temp;
            best = prev_best;
        }
    }
    //print_board(b);
    while (all_moves[i] != 0) {
        j=b->squares[26];
        if (all_moves[i] == prev_best) {
            i++; continue;
        }
        //print_board(b);
        temp_inf = get_irrev_move_info(b,all_moves[i]);
        commit_a_move_for_white_in_game(the_game,all_moves[i]); /* Commits the move. */
        temp = evaluate_minimax_for_black(the_game, all_moves, all_moves[i], temp_inf,depth - 1, max, MAX_EVAL); /* Checks what is the eval after the move. */
        unmake_move_in_game(the_game,all_moves[i],temp_inf);
        if (temp > max) { /* If the eval is better then the max eval: */
            max = temp; /* Changes max to be it. */
            best = all_moves[i];
        }

        i++;
    }
    if (depth == 5) {
        printf("Eval= %lf\n",max);
    }
    return best;
}

/* The main function of minimax for black, returns the best move of the position. */
move get_best_move_black(game *the_game,char depth, move *all_moves_already_calculated) {
    board *b = the_game->current_position;
    move all_moves[MAX_POSSIBLE_MOVES]; /* All the moves possible in the position. */
    int i = MAX_POSSIBLE_MOVES / 2;
    int j = 0;
    char kings = 0;
    double min = MAX_EVAL; /* The maximun eval possible in the position(maximum = best for white). */
    move best; /* The best move in the position. */
    move prev_best = END; /* The best move in the position, in depth - 1. */
    double temp = 0;
    irreversible_move_info temp_inf;
    if (all_moves_already_calculated == 0) /* If the moves weren't already calculated. */
        get_possible_moves(b,all_moves,0, 0, 0); /* Gets all the moves possible (but there is no "last move"). */
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
        prev_best = get_best_move_black(the_game, depth-1, all_moves);
        temp_inf = get_irrev_move_info(b,prev_best);
        commit_a_move_for_black_in_game(the_game,prev_best);
        temp = evaluate_minimax_for_white(the_game, all_moves, prev_best, temp_inf,depth - 1, MIN_EVAL, MAX_EVAL);
        unmake_move_in_game(the_game,prev_best,temp_inf);
        if (temp < min) {
            min = temp;
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
        temp = evaluate_minimax_for_white(the_game, all_moves, all_moves[i], temp_inf, depth - 1, MIN_EVAL, min); /* Checks what is the eval after the move. */
        unmake_move_in_game(the_game,all_moves[i],temp_inf);

        if (temp < min) { /* If the eval is better then the max eval: */
            min = temp; /* Changes max to be it. */
            best = all_moves[i];
        }
        i++;
    }
    if (depth == 5) {
        printf("Eval= %lf\n",min);
    }
    /*printf("number of moves = %ld\n",number_of_moves);*/
    return best;
}