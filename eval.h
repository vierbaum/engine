#ifndef EVAL_H_
#define EVAL_H_

#include "board.h"

#define PAWN 1
#define KNIGHT 3
#define BISHOP 3.25
#define ROOK 5
#define QUEEN 9
#define KING 1000


double eval(Board* board) {
  double eval = 0;
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      switch (board->board[x][y]) {
      case 'P':
        eval += PAWN;
        break;

      case 'p':
        eval -= PAWN;
        break;

      case 'N':
        eval += KNIGHT;
        break;

      case 'n':
        eval -= KNIGHT;
        break;

      case 'B':
        eval += BISHOP;
        break;

      case 'b':
        eval -= BISHOP;
        break;

      case 'R':
        eval += ROOK;
        break;

      case 'r':
        eval -= ROOK;
        break;

      case 'Q':
        eval += QUEEN;
        break;

      case 'q':
        eval -= QUEEN;
        break;

      case 'K':
        eval += KING;
        break;

      case 'k':
        eval -= KING;
        break;

      }
    }
  }


  return eval;
}


#endif // EVAL_H_
