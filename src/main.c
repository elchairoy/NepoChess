#include <stdio.h>
#include <board_struct.h>
/*
  Created by Elchairoy Meir on 29/11/2021.
*/

int main() {
    char x = 0x1a;
    printf("%d",4 >> (x << 4));
    return 0;
}
