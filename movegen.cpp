#include "movegen.h"

Board newMove (Board move, int from, int to) {
  move.makeMove120(from, to);
  return move;
}


std::vector<Board>* genmoves(Board board, std::vector<Board>* moves) {

  for (int i = 0; i < SIZE; i++)
    switch (board.board[i]) {
    case OUTOFBOARDER:
      break;
    case EMPTY:
      break;
    case wP:
      if(board.board[i + 10] == EMPTY) {
        moves->push_back(newMove(board, i, i + 10));
        if(i <= B8 && board.board[i + 20] == EMPTY)
          moves->push_back(newMove(board, i, i + 20));
      }
      if(board.board[i + 9] > wK && board.board[i + 9] <= bK)
        moves->push_back(newMove(board, i, i + 9));
      if(board.board[i + 11] > wK && board.board[i + 11] <= bK)
        moves->push_back(newMove(board, i, i + 11));

      break;
   }
  return moves;
}
