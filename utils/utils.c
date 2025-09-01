#include <stdlib.h>

#include "utils.h"

int randomNumber(int x, int y) { return rand() % (x - y + 1) + x; }

void setSeed(unsigned int x) { srand(x); }
