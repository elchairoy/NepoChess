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
  uci_main();
  return 0;
}
