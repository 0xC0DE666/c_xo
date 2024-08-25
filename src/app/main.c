#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#include "../libs/c_structs.h"

#include "utils/io.h"
#include "models/player.h"
#include "models/board.h"

int main() {
  printf("C XO\n");

  printf("%d %d\n", true, false);

  Position p = position_new(100, 12);
  printf("%d %d\n", p.row, p.column);

  return 0;
}
