#include "../include/minimax.h"

#define MAX_CHAR 100
#define MIN_CHAR -100

long int number_of_moves = 0;

char evaluate_minimax_for_white(board b, char depth) {
    move *all_moves = get_all_moves(&b);
    board temp_board = b;
    char i = 0;
    char max = MIN_CHAR;
    char temp;

    if (all_moves[0] == 0) {
        number_of_moves++;
        free(all_moves);
        if (isAttacked_by_black(&b,find_king_square(&b,1)))
            return MIN_CHAR;
        
        return 0;
    }

    if (depth == 0) {
        number_of_moves++;
        free(all_moves);
        return evaluate_by_points(&b);
    }

    while (all_moves[i] != 0) {
        temp_board = b;
        commit_a_move_for_white(&temp_board,all_moves[i]);
        temp = evaluate_minimax_for_black(temp_board,depth - 1);
        if (temp == MAX_CHAR) {
            free(all_moves);
            return temp;
        }
        if (temp > max)
            max = temp;
        temp_board = b;
        i++;
    }
    free(all_moves);
    return max;
}

char evaluate_minimax_for_black(board b, char depth) {
    move *all_moves = get_all_moves(&b);
    board temp_board = b;
    char i = 0;
    char min = MAX_CHAR;
    char temp;
    if (all_moves[0] == 0) {
        number_of_moves++;
        free(all_moves);
        if (isAttacked_by_white(&b,find_king_square(&b,0)))
            return MAX_CHAR;
        return 0;
    }
    if (depth == 0) {
        number_of_moves++;
        free(all_moves);
        return evaluate_by_points(&b);
    }

    while (all_moves[i] != 0) {
        commit_a_move_for_black(&temp_board,all_moves[i]);
        temp = evaluate_minimax_for_white(temp_board,depth - 1);
        if (temp == MIN_CHAR) {
            free(all_moves);
            return temp;
        }
        if (temp < min) {
            min = temp;
        }
        temp_board = b;
        i++;
    }
    free(all_moves);
    return min;
}

move minimax_for_white(board *b,char depth) {
    move *all_moves = get_all_moves(b);
    board temp_board = *b;
    char i = 0;
    char max = MIN_CHAR;
    move best = all_moves[0];
    char temp;

    while (all_moves[i] != 0) {
        commit_a_move_for_white(&temp_board,all_moves[i]);
        temp = evaluate_minimax_for_black(temp_board,depth - 1);
        if (temp == MAX_CHAR) {
            best = all_moves[i];
            free(all_moves);
            return best;
        }
        if (temp < max) {
            max = temp;
            best = all_moves[i];
        }
        temp_board = *b;
        i++;
    }
    free(all_moves);
    return best;
}

move minimax_for_black(board *b,char depth) {
    move *all_moves = get_all_moves(b);
    board temp_board = *b;
    char i = 0;
    char min = MAX_CHAR;
    move best = all_moves[0];
    char temp;

    while (all_moves[i] != 0) {
        commit_a_move_for_black(&temp_board,all_moves[i]);
        temp = evaluate_minimax_for_white(temp_board,depth - 1);
        if (temp == MIN_CHAR) {
            best = all_moves[i];
            free(all_moves);
            return best;
        }
        if (temp < min) {
            min = temp;
            best = all_moves[i];
        }
        temp_board = *b;
        i++;
    }
    free(all_moves);
    return best;
}