#include "eval.h"
#include <stdlib.h>

int getNum(char* number) {
  char* end = number;
  int res = 0;
  int i = 0;
  while (*number != '\0')
    number++;
  number--;
  while (number >= end) {
    res += power(10, i) * (*number - '0');
    number--;
    i++;
  }
  return res;
}

int power(int base, int exp) {
  int result = 1;
  while (exp > 0) {
    if (exp % 2 == 1) {
      result = result * base;
    }
    exp = exp / 2;
    base = base * base;
  }
  return result;
}

void printPieceTable(int table[64]) {
    for (int pos = 0; pos <= 63; pos++) {
      (table[pos] < 100) ? printf("%d\t|", table[pos]) : printf("%d|", table[pos]);
      if (pos % 8 == 7)
        printf("\n------------------------------------------------------\n");
    }
  return;
}

void readEvals() {
  FILE* file;
  file = fopen("evals", "r");

  char* number;
  number = (char*) malloc(4 * sizeof(char));
  int i = 0;
  char c;
  int *currPiece;
  int stage;
  char gennum = 0;
  int pos = 0;
  int x = 0;
  int y = 0;
  while ((c = fgetc(file)) != EOF) {
    if (c > 'A') {
      x = 0;
      y = 0;
      i = 0;
      switch (c) {
      case 'P':
        currPiece = PAWNEVAL;
        break;
      case 'N':
        currPiece = KNIGHTEVAL;
        break;
      case 'B':
        currPiece = BISHOPEVAL;
        break;
      case 'R':
        currPiece = ROOKEVAL;
        break;
      case 'Q':
        currPiece = QUEENEVAL;
        break;
      case 'K':
        currPiece = KINGEVAL;
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
      *(number + i) = c;
      i++;
    }
    else if (c == ',' || (c == '\n' && i != 0)) {
      *(number + i) = '\0';
      pos = x + 8 * y;
      *(currPiece + stage * 64 + pos) = getNum(number);

      pos = x + 8 * (7 - y);
      *(currPiece + 192 + stage * 64 + pos) = -getNum(number);
      i = 0;
      x++;
      if (x == 8) {
        y++;
        x = 0;
      }
    }
  }
}
