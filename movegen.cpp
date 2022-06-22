#include "movegen.h"

std::vector<Board>* genmoves(Board board, std::vector<Board>* moves) {

  for (int i = 0; i < SIZE; i++)
    switch (board.board[i]) {
    case OUTOFBOARDER:
      break;
    case EMPTY:
      break;
    case wP:

      break;
   }
  return moves;
}
