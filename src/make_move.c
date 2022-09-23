#include "../include/make_move.h"


/* The function commit a short castle for white. */
void commit_a_short_castle_for_white(board * b){
    change_the_square(b, 4, empty); /* It changes the white king place to empty. */
    change_the_square(b, 7, empty); /* It changes the white rook place to empty. */
    change_the_square(b, 6, white_king); /* It puts the white king in his place. */
    change_the_square(b, 5, white_rook); /* It puts the white rook in his place. */
    b->can_white_castle_short = 0; /* White can't castle anymore. */
    b->can_white_castle_long = 0;/* White can't castle anymore. */
}

/* The function commit a long castle for white. */
void commit_a_long_castle_for_white(board * b){
    change_the_square(b, 4, empty); /* It changes the white king place to empty */
    change_the_square(b, 0, empty); /* It changes the white rook place to empty */
    change_the_square(b, 2, white_king); /* It puts the white king in his place */
    change_the_square(b, 3, white_rook); /* It puts the white rook in his place */
    b->can_white_castle_short = 0; /* White can't castle anymore. */
    b->can_white_castle_long = 0;/* White can't castle anymore. */
}

/* The function commit an en passant for white. */
void commit_en_passant_for_white(board * b, unsigned char src_loc, unsigned char dst_loc){

    change_the_square(b, src_loc, empty); /* It changes the white pawn place to empty. */
    change_the_square(b, dst_loc, white_pawn); /* It puts the white pawn in his place. */
    change_the_square(b, dst_loc - 8, empty); /* It changes the black pawn place to empty. */
}

/* The function commit a promotion for white. */
void commit_promotion_for_white(board * b, unsigned char src_loc, unsigned char dst_loc, unsigned char what_to_promote_to){
    change_the_square(b, src_loc, empty); /* Change the src loc to empty. */
    if (what_to_promote_to == promote_to_queen) change_the_square(b, dst_loc, white_queen); /* promote to queen. */
    else if (what_to_promote_to == promote_to_rook) change_the_square(b, dst_loc, white_rook); /* promote to rook. */
    else if(what_to_promote_to == promote_to_knight) change_the_square(b, dst_loc, white_knight); /* promote to knight */
    else change_the_square(b, dst_loc, white_bishop); /* promote to bishop. */
}

/* The function commit a short castle for black. */
void commit_a_short_castle_for_black(board * b){
    change_the_square(b, 60, empty); /* It changes the black king place to empty. */
    change_the_square(b, 63, empty); /* It changes the black rook place to empty. */
    change_the_square(b, 62, black_king); /* It puts the black king in his place. */
    change_the_square(b, 61, black_rook); /* It puts the black rook in his place. */
    b->can_black_castle_short = 0; /* Black can't castle anymore. */
    b->can_black_castle_long = 0;/* Black can't castle anymore. */
}

/* The function commit a long castle for black. */
void commit_a_long_castle_for_black(board * b){
    change_the_square(b, 60, empty); /* It changes the black king place to empty. */
    change_the_square(b, 56, empty); /* It changes the black rook place to empty. */
    change_the_square(b, 58, black_king); /* It puts the black king in his place. */
    change_the_square(b, 59, black_rook); /* It puts the black rook in his place. */
    b->can_black_castle_short = 0; /* Black can't castle anymore. */
    b->can_black_castle_long = 0;/* Black can't castle anymore. */
}

/* The function commit an en passant for black. */
void commit_en_passant_for_black(board * b, unsigned char src_loc, unsigned char dst_loc){
    change_the_square(b, src_loc, empty); /* It changes the black pawn place to empty. */
    change_the_square(b, dst_loc, black_pawn); /* It puts the black pawn in his place. */
    change_the_square(b, dst_loc + 8, empty); /* It changes the white pawn place to empty. */
}

/* The function commit a promotion for black. */
void commit_promotion_for_black(board * b, unsigned char src_loc, unsigned char dst_loc, unsigned char what_to_promote_to){
    change_the_square(b, src_loc, empty); /* Change the src loc to empty. */
    if (what_to_promote_to == promote_to_queen) change_the_square(b, dst_loc, black_queen); /* Promote to queen. */
    else if (what_to_promote_to == promote_to_rook) change_the_square(b, dst_loc, black_rook); /* Promote to rook. */
    else if(what_to_promote_to == promote_to_knight) change_the_square(b, dst_loc, black_knight); /* Promote to knight. */
    else change_the_square(b, dst_loc, black_bishop); /* Promote to bishop. */
}

/* The function checks which pawns can en passant next move. */
void can_en_passant_next_move(board * b, move m) {
    unsigned char src_loc = get_src_square(m); /* The src square. */
    unsigned char dst_loc = get_dst_square(m); /* The dst square. */
    char piece = get_piece_in_square(b, src_loc); /* It gets the sole in the src square. */

    if (piece == white_pawn && dst_loc == src_loc + UP + UP) { /* A white pawn and goes 2 times forward. */
        if (get_piece_in_square(b, dst_loc + LEFT) == black_pawn) /* If there is a black pawn next to it: */
            b->pawn_en_passant_right = dst_loc + LEFT;

        if (get_piece_in_square(b, dst_loc + RIGHT) == black_pawn) /* If there is a black pawn next to it: */
            b->pawn_en_passant_left = dst_loc + RIGHT;
    }
    else if (piece == black_pawn && dst_loc == src_loc + DOWN + DOWN) { /* A black pawn and goes 2 times forward. */
        if (get_piece_in_square(b, dst_loc + LEFT) == white_pawn) /* If there is a white pawn next to it: */
            b->pawn_en_passant_right = dst_loc + LEFT;

        if (get_piece_in_square(b, dst_loc + RIGHT) == white_pawn) /* If there is a white pawn next to it: */
            b->pawn_en_passant_left = dst_loc + RIGHT;
    }
}


/* A function that receives a move of the white and executes it. */
void commit_a_move_for_white(board * b, move m){
    unsigned char src_loc = get_src_square(m); /* The src square. */
    unsigned char dst_loc = get_dst_square(m); /* The dst square. */
    char piece = get_piece_in_square(b, src_loc); /* It gets the sole in the src square. */
    b->pawn_en_passant_left = 0; /* The pawns can't en passant anymore. */
    b->pawn_en_passant_right = 0;

    b->whos_turn = 0; /* It will be black's turn next. */
    if (get_is_short_castle(m) == 1) /* If this move is a short castle. */
        commit_a_short_castle_for_white(b); /* Commit a short castle for white. */

    else if (get_is_long_castle(m) == 1) /* If this move is a long castle. */
        commit_a_long_castle_for_white(b); /* Commit a long castle for white. */

    else if ((dst_loc == (src_loc + 9) || dst_loc == (src_loc + 7)) && (piece == white_pawn) && (get_piece_in_square(b, dst_loc) == empty)) /* if it's an en passant: */
        commit_en_passant_for_white(b, src_loc, dst_loc);

    else if (piece == white_pawn && (dst_loc / 8) == 7) /* If it's a promotion: */
        commit_promotion_for_white(b, src_loc, dst_loc, get_promotion_choice(m));

    else
    {
        /* Check if a rook or the king moved: */
        if  (src_loc == 0 || dst_loc == 0 || src_loc == 4)
            b->can_white_castle_long = 0;
        if  (src_loc == 7 || dst_loc==7 || src_loc == 4)
            b->can_white_castle_short = 0;
        if (dst_loc == 56)
            b->can_black_castle_long = 0;
        if (dst_loc == 63)
            b->can_black_castle_short = 0;

        can_en_passant_next_move(b,m); /* Check which pawns can en passant in the next move. */
        change_the_square(b, src_loc, empty); /* It changes the src square to empty. */
        change_the_square(b, dst_loc, piece); /* It changes the dst square to the piece. */
    }
}

/* A function that receives a move of the black and executes it. */
void commit_a_move_for_black(board * b, move m){
    unsigned char src_loc = get_src_square(m); /* The src square. */
    unsigned char dst_loc = get_dst_square(m); /* The dst square. */
    char piece = get_piece_in_square(b, src_loc); /* It gets the sole in the src square. */
    b->pawn_en_passant_left = 0; /* The pawns can't en passant anymore. */
    b->pawn_en_passant_right = 0;

    b->whos_turn = 1; /* It will be white's turn next. */
    if (get_is_short_castle(m) == 1) /* If this move is a short castle. */
        commit_a_short_castle_for_black(b);

    else if (get_is_long_castle(m) == 1) /* If this move is a long castle. */
        commit_a_long_castle_for_black(b);

    else if ((dst_loc == (src_loc - 9) || dst_loc == (src_loc - 7)) && (piece == black_pawn) && (get_piece_in_square(b, dst_loc) == empty)) /* if it's an en passant. */
        commit_en_passant_for_black(b, src_loc, dst_loc);

    else if(piece == black_pawn && (dst_loc / 8) == 0)
        commit_promotion_for_black(b, src_loc, dst_loc, get_promotion_choice(m));
    else
    {
        /* Check if a rook or the king moved: */
        if  (src_loc == 63 || src_loc == 60)
            b->can_black_castle_short = 0;
        if  (src_loc == 56 || src_loc == 60)
            b->can_black_castle_long = 0;
        if (dst_loc == 0)
            b->can_white_castle_long = 0;
        if (dst_loc == 7)
            b->can_white_castle_short = 0;

        can_en_passant_next_move(b,m); /* Check which pawns  can en passant in the next move. */
        change_the_square(b, src_loc, empty); /* It changes the src square to empty. */
        change_the_square(b, dst_loc, piece); /* It changes the dst square to the piece. */
    }
}