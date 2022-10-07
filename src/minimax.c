#include "../include/minimax.h"

#define MAX_EVAL 100 /* The maximum evaluation possible. */
#define MIN_EVAL -100 /* The minimum evaluation possible. */

#define EVAL_TO_PRUNE 2 /* In what evaluation the minimax will cut the moves branch because it's too bad. */

long int number_of_moves = 0; /* The number of positions scaned. */

/* This function gets a board (when is white's move) and the depth and evaluates the position using minimax. */
double evaluate_minimax_for_white(board *b, char depth, char pre_frontier, HashTable *ht) {
    move *all_moves; /* The array of all the moves possible. */
    board temp_board = *b;
    int i = 0;
    double max = MIN_EVAL; /* The maximun eval possible in the position(maximum = best for white). */
    double temp;
    void *tempvoid;

    if (isAttacked_by_black(b,find_king_square(b,WHITE))) { /* Checks if it's a check: */
        all_moves = get_all_moves(b);
        if (all_moves[0] == 0) { /* If it's a mate: */
            number_of_moves++;
            free(all_moves);
            return MIN_EVAL;
        }
        free(all_moves);
    }

    if (depth == 0) {
        number_of_moves++;
        return evaluate_by_points(b);
    }

    all_moves =  get_all_moves(b); /* Gets all the moves possible. */

    if (all_moves[0] == 0)/* Stalmate */
        max = 0;

    while (all_moves[i] != 0) {
        commit_a_move_for_white(&temp_board,all_moves[i]); /* Commits the move. */
        
        /* Checks if it's already evaluated: */
        tempvoid = ht_lookup(ht,&temp_board);
        if (tempvoid != NULL) {
            temp = *(double *)tempvoid;
            if (temp == MAX_EVAL) {  /* If it's forced mate after the move: */
                free(all_moves);
                return temp;
            }
            if (temp > max) /* If the eval is better then the max eval: */
                max = temp; /* Changes min to be it. */
            temp_board = *b;
            i++;
            continue;
        }
        /* The razoring: */
        if (depth > pre_frontier && max - evaluate_minimax_for_black(&temp_board,depth - 2,pre_frontier, ht) >= EVAL_TO_PRUNE) { /* If making the move will lead to a loss of 2 points in less moves: */
            i++;
            temp_board = *b;
            continue;
        }
        
        temp = evaluate_minimax_for_black(&temp_board,depth - 1,pre_frontier, ht); /* Checks what is the eval after the move. */

        /* Adds it to the hash table: */
        if (!ht_contains(ht,&temp_board) && (ht->size)*(ht->key_size)<=ht->capacity)
            ht_insert(ht, &temp_board, &temp);

        if (temp == MAX_EVAL) {  /* If it's forced mate after the move: */
            free(all_moves);
            return temp;
        }
        if (temp > max) /* If the eval is better then the max eval: */
            max = temp; /* Changes min to be it. */
        temp_board = *b;
        i++;
    }
    free(all_moves);
    return max;
}

/* This function gets a board (when is black's move) and the depth and evaluates the position using minimax. */
double evaluate_minimax_for_black(board *b, char depth, char pre_frontier, HashTable *ht) {
    move *all_moves; /* All moves possible in the possition. */
    board temp_board = *b;
    int i = 0;
    double min = MAX_EVAL; 
    double temp;
    void *tempvoid;

    if (isAttacked_by_white(b,find_king_square(b,BLACK))) { /* Checks if it's a check: */
        all_moves = get_all_moves(b); 
        if (all_moves[0] == END) { /* If it's a mate: */
            number_of_moves++;
            free(all_moves);
            return MAX_EVAL;
        }
        free(all_moves);
    }
    if (depth == 0) {
        number_of_moves++;
        return evaluate_by_points(b);
    }
    all_moves =  get_all_moves(b); /* Gets all the moves possible. */

    if (all_moves[0] == 0)/* Stalmate */
        min = 0;

    while (all_moves[i] != 0) {
        commit_a_move_for_black(&temp_board,all_moves[i]); /* Commits the move. */

        /* Checks if it's already evaluated: */
        tempvoid = ht_lookup(ht,&temp_board);
        if (tempvoid != NULL) {
            temp = *(double *)tempvoid;
            if (temp == MIN_EVAL) {  /* If it's forced mate after the move: */
                free(all_moves);
                return temp;
            }
            if (temp < min) /* If the eval is better then the min eval: */
                min = temp; /* Changes min to be it. */
            temp_board = *b;
            i++;
            continue;
        }

        /* The razoring: */
        if (depth > pre_frontier && evaluate_minimax_for_white(&temp_board,depth - 2,pre_frontier, ht) - min >= EVAL_TO_PRUNE) { /* If making the move will lead to a loss of 2 points in less moves: */
            i++;
            temp_board = *b;
            continue;
        }

        temp = evaluate_minimax_for_white(&temp_board,depth - 1,pre_frontier, ht); /* Checks what is the eval after the move. */

        /* Adds it to the hash table: */
        if (!ht_contains(ht,&temp_board) && (ht->size)*(ht->key_size)<=ht->capacity)
            ht_insert(ht, &temp_board, &temp);

        if (temp == MIN_EVAL) { /* If it's forced mate after the move: */
            free(all_moves);
            return temp;
        }

        if (temp < min) { /* If the eval is better then the min eval: */
            min = temp; /* Changes min to be it. */
        }
        temp_board = *b;
        i++;
    }
    free(all_moves);
    return min;
}

/* The main function of minimax for white, returns the best move of the position. */
move get_best_move_white(board *b,char depth,char pre_frontier, HashTable *ht) {
    move *all_moves = get_all_moves(b); /* All the moves possible in the position. */
    board temp_board = *b;
    int i = 0;
    double max = MIN_EVAL; /* The maximun eval possible in the position(maximum = best for white). */
    move best = all_moves[0]; /* The best move in the position. */
    double temp;
    
    while (all_moves[i] != 0) {
        commit_a_move_for_white(&temp_board,all_moves[i]); /* Commits the move. */
        /* The razoring: */
        if (depth > pre_frontier && max - evaluate_minimax_for_black(&temp_board,depth - 2,pre_frontier, ht) >= EVAL_TO_PRUNE) { /* If making the move will lead to a loss of 2 points in less moves: */
            i++;
            temp_board = *b;
            continue;
        }

        temp = evaluate_minimax_for_black(&temp_board,depth - 1,pre_frontier, ht); /* Checks what is the eval after the move. */
        
        /* Adds it to the hash table: */
        if (!ht_contains(ht,&temp_board) && (ht->size)*(ht->key_size)<=ht->capacity)
            ht_insert(ht, &temp_board, &temp);

        if (temp == MAX_EVAL) { /* If it's forced mate after the move: */
            best = all_moves[i];
            free(all_moves);
            return best; /* Returns it. */
        }

        if (temp > max) { /* If the eval is better then the max eval: */
            max = temp; /* Changes max to be it. */
            best = all_moves[i];
        }
        temp_board = *b;
        i++;
    }
    free(all_moves);
    return best;
}

/* The main function of minimax for black, returns the best move of the position. */
move get_best_move_black(board *b,char depth, char pre_frontier, HashTable *ht) {
    move *all_moves = get_all_moves(b); /* All the moves possible in the position. */
    board temp_board = *b;
    int i = 0;
    double min = MAX_EVAL; /* The minimun eval possible in the position(minimum = best for black). */
    move best = all_moves[0]; /* The best move in the position. */
    double temp = 0;

    while (all_moves[i] != END) {
        commit_a_move_for_black(&temp_board,all_moves[i]); /* Commits the move. */
     if (depth > pre_frontier && evaluate_minimax_for_white(&temp_board,depth - 2,pre_frontier, ht) - min >= EVAL_TO_PRUNE) {
            i++;
            temp_board = *b;
            continue;
        }
        temp = evaluate_minimax_for_white(&temp_board,depth - 1,pre_frontier,ht); /* Checks what is the eval after the move. */
        
        /* Adds it to the hash table: */
        if (!ht_contains(ht,&temp_board) && (ht->size)*(ht->key_size)<=ht->capacity)
            ht_insert(ht, &temp_board, &temp);;

        if (temp == MIN_EVAL) { /* If it's forced mate after the move: */
            best = all_moves[i];
            free(all_moves);
            return best; /* Returns it. */
        }

        if (temp < min) { /* If the eval is better then the min eval: */
            min = temp; /* Changes min to be it. */
            best = all_moves[i];
        }
        temp_board = *b;
        i++;
    }
    free(all_moves);
    /*printf("minmax eval= %lf\n",min);*/
    return best;
}