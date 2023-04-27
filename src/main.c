#include <stdio.h>
#include "../include/uci.h"

/*
  Created by Elchairoy Meir on 29/11/2021.
*/

extern long int no_of_moves;
int main() {
   setbuf(stdout, NULL); // Set no stdout buffering
  /*uci_main();*/
  board b;
  char *fen = "r2qkb1r/ppp2pp1/3p1p1p/8/1n6/2NP1P1P/PPP1QPP1/1R2KB1R b Kkq - 2 9 ";
  uci_main();
  return 0;
}
