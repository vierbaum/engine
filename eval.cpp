#include "board.h"
#include "board.h"
#include <cstdio>

void readEval(double (*evalList)[6][3][64]) {
  FILE* file;
  file = fopen("evals", "r");

  char c;
  int currPiece;
  while ((c = fgetc(file)) != EOF) {
    if (c > 'A')
      switch (c) {
      case 'P':
        currPiece = 0;
        break;
      case 'N':
        currPiece = 1;
        break;
      case 'B':
        currPiece = 2;
        break;
      case 'R':
        currPiece = 3;
        break;
      case 'Q':
        currPiece = 4;
        break;
      case 'K':
        currPiece = 5;
        break;
        }
  }
  printf("%d\n", currPiece);
}