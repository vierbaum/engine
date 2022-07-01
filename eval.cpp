#include "board.h"
#include "board.h"
#include <cstdio>

void readEval(double (*evalList)[12][3][64]) {
  FILE* file;
  file = fopen("evals", "r");

  std::string number = "";
  char c;
  int currPiece;
  int stage;
  bool gennum = false;
  int pos = 0;
  int x = 0;
  int y = 0;
  while ((c = fgetc(file)) != EOF) {
    if (c > 'A') {
      x = 0;
      y = 0;
      number = "";
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
      case 'S':
        stage = 0;
        break;
      case 'M':
        stage = 1;
        break;
      case 'E':
        stage = 2;
        break;
      }

    }

    else if (c >= '0' && c <= '9') {
      number += c;
    } else if (c == ',' || (c == '\n' && number != "")) {
      pos = (7 - y) * 8 + x;
      (*evalList)[currPiece][stage][(7 - y) * 8 + x] = (double) std::stoi(number) / 100;
      (*evalList)[currPiece + bP][stage][y * 8 + x] = (double) std::stoi(number) / -100;

      number = "";
      x++;
      if (x == 8) {
        y++;
        x = 0;
      }
    }
  }
}

void printPieceTable(double table[64]) {
  
    for (int y = 7; y >= 0; y--) {
      for (int x = 0; x < 8; x++)
          printf("%.2f | ", table[y * 8 + x]);
      printf("\n------------------------------------------------------\n");
    }
  return;
}