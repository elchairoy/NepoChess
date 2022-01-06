#include <stdio.h>
#include "../include/test_minimax.h"
#include "../include/play_minigame.h"
#include "../include/hashtable.h"

/*
  Created by Elchairoy Meir on 29/11/2021.
*/

extern long int number_of_moves;

int main() {
  check_miminax();
  printf("%ld",number_of_moves);
  /*check();*/
  return 0;
}
