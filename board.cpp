#include "board.h"


void printBitBoard (unsigned long long bitBoard) {
  unsigned long long a = 1ULL;
  for (int i = 63; i >= 0; i--) {
    if (((a << i) & bitBoard))  {
      if (i % 8 == 0)
        printf("X\n");
      else
        printf("X");
    }
    else {
      if (i % 8 == 0)
        printf("-\n");
      else
        printf("-");
    }

  }
  printf("\n");
}
