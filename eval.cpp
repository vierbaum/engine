#include "eval.h"

double Board::eval() {
    double eval = 0;
    for (int x = 0; x < 8; x++) {
      for (int y = 0; y < 8; y++) {
        switch (board[x][y]) {
        case 'P':
          eval += pawneval[y][x];
          break;

        case 'p':
          eval -= pawneval[7 - y][x];
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
          eval += KING + 100;
          break;

        case 'k':
          eval -= KING;
          break;

        }
      }
    }


    return eval;
}

double kingsafety(Board board) {
  int wk[2];
  int bk[2];

  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      if (board.board[x][y] == 'K') {
        wk[0] = x;
        wk[1] = y;
    }
      else if (board.board[x][y] == 'k') {
        bk[0] = x;
        bk[1] = y;
      }
    }
  }
  return 0;
}
