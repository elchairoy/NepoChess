#include <stdio.h>
#include "../include/test_minimax.h"
#include "../include/uci.h"

/*
  Created by Elchairoy Meir on 29/11/2021.
*/

extern long int moves;
int main() {
  setbuf(stdout, NULL); // Set no stdout buffering
  /*uci_main();*/
  board b;
  setup_start_board(&b);
  moves_in_depth(4,&b,0,0,0);
  return 0;
}
