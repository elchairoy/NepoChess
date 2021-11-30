/*
 Created by chaim at 30/11/2021.
*/

typedef struct {
    unsigned src_loc : 6; /* location of piece. */
    unsigned dst_loc : 6; /* where to move the piece to. */
    unsigned crown_to : 3; /* if pawn to line 8: what to crown pawn to, 0 if not. */
    unsigned castle_long : 1; /* if castle, 0 if isn't, 1 if is. */
    unsigned castle_short : 1; /* if castle, 0 if isn't, 1 if is. */
}move;