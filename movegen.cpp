#include "movegen.h"
#include "board.h"
#include <vector>

Board newMove (Board move, int from, int to) {
  move.makeMove120(from, to);
  return move;
}

void knightMove (Board board, int pos, std::vector<Board>* moves) {
  for(int i = 0; i < 8; i++) {
    int xpos = pos + knightMoves[i];
    if (board.color && board.board[xpos] != OUTOFBOUNDS && (board.bbW & (1ULL << board.B120to64(xpos))) == 0)
      moves->push_back(newMove(board, pos, xpos));
    else if (!board.color && board.board[xpos] != OUTOFBOUNDS && (board.bbB & (1ULL << board.B120to64(xpos))) == 0)
      moves->push_back(newMove(board, pos, xpos));
  }
  return;
}

void bishopMove (Board board, int pos, std::vector<Board>* moves) {
  for (int xpos = pos + 9; xpos < SIZE; xpos += 9) // up left
    if (board.board[xpos] == OUTOFBOUNDS)
      break;
    else if (board.color && (board.bbW & (1ULL << board.B120to64(xpos))) == 0)
      moves->push_back(newMove(board, pos, xpos));
    else if (!board.color && (board.bbB & (1ULL << board.B120to64(xpos))) == 0)
      moves->push_back(newMove(board, pos, xpos));

  for (int xpos = pos + 11; xpos < SIZE; xpos += 11) // up right
    if (board.board[xpos] == OUTOFBOUNDS)
      break;
    else if (board.color && (board.bbW & (1ULL << board.B120to64(xpos))) == 0)
      moves->push_back(newMove(board, pos, xpos));
    else if (!board.color && (board.bbB & (1ULL << board.B120to64(xpos))) == 0)
      moves->push_back(newMove(board, pos, xpos));

  for (int xpos = pos - 11; xpos < SIZE; xpos -= 11) // down left
    if (board.board[xpos] == OUTOFBOUNDS)
      break;
    else if (board.color && (board.bbW & (1ULL << board.B120to64(xpos))) == 0)
      moves->push_back(newMove(board, pos, xpos));
    else if (!board.color && (board.bbB & (1ULL << board.B120to64(xpos))) == 0)
      moves->push_back(newMove(board, pos, xpos));

  for (int xpos = pos - 9; xpos < SIZE; xpos -= 9) // down right
    if (board.board[xpos] == OUTOFBOUNDS)
      break;
    else if (board.color && (board.bbW & (1ULL << board.B120to64(xpos))) == 0)
      moves->push_back(newMove(board, pos, xpos));
    else if (!board.color && (board.bbB & (1ULL << board.B120to64(xpos))) == 0)
      moves->push_back(newMove(board, pos, xpos));
  return;
}

void rookMove (Board board, int pos, std::vector<Board>* moves) {
  for (int xpos = pos + 1; xpos < SIZE; xpos++) {
    if (board.board[xpos] == OUTOFBOUNDS)
      break;
    else if (board.color && (board.bbW & (1ULL << board.B120to64(xpos))) == 0)
      moves->push_back(newMove(board, pos, xpos));
    else if (!board.color && (board.bbB & (1ULL << board.B120to64(xpos))) == 0)
      moves->push_back(newMove(board, pos, xpos));
  }

  for (int xpos = pos - 1; xpos >= 0; xpos--) {
    if (board.board[xpos] == OUTOFBOUNDS)
      break;
    else if (board.color && (board.bbW & (1ULL << board.B120to64(xpos))) == 0)
      moves->push_back(newMove(board, pos, xpos));
    else if (!board.color && (board.bbB & (1ULL << board.B120to64(xpos))) == 0)
      moves->push_back(newMove(board, pos, xpos));
  }

  for (int xpos = pos + 10; xpos < SIZE; xpos += 10) {
    if (board.board[xpos] == OUTOFBOUNDS)
      break;
    else if (board.color && (board.bbW & (1ULL << board.B120to64(xpos))) == 0)
      moves->push_back(newMove(board, pos, xpos));
    else if (!board.color && (board.bbB & (1ULL << board.B120to64(xpos))) == 0)
      moves->push_back(newMove(board, pos, xpos));
  }

  for (int xpos = pos - 10; xpos >= 0; xpos -= 10) {
    if (board.board[xpos] == OUTOFBOUNDS)
      break;
    else if (board.color && (board.bbW & (1ULL << board.B120to64(xpos))) == 0)
      moves->push_back(newMove(board, pos, xpos));
    else if (!board.color && (board.bbB & (1ULL << board.B120to64(xpos))) == 0)
      moves->push_back(newMove(board, pos, xpos));
  }
  return;
}

std::vector<Board>* genmoves(Board board, std::vector<Board>* moves) {
  int pos;
  if (board.color) {
    /*
     if (board.numPieces[wP] != 0)
       for (int i = 0; i < board.numPieces[wP]; i++) {
         pos = board.pieceList[wP][i];
         if(board.board[pos + 10] == EMPTY) {
           moves->push_back(newMove(board, pos, pos + 10));
           if(pos <= B8 && board.board[pos + 20] == EMPTY)
             moves->push_back(newMove(board, pos, pos + 20));
         }
         if(board.board[pos + 9] > wK && board.board[pos + 9] <= bK)
           moves->push_back(newMove(board, pos, pos + 9));
         if(board.board[pos + 11] > wK && board.board[pos + 11] <= bK)
           moves->push_back(newMove(board, pos, pos + 11));
       }

  if (board.numPieces[wN] != 0)
    for (int i = 0; i < board.numPieces[wN]; i++) {
      pos = board.pieceList[wN][i];
      knightMove(board, pos, moves);
    }
*/
  if (board.numPieces[wB] != 0)
    for (int i = 0; i < board.numPieces[wB]; i++) {
      pos = board.pieceList[wB][i];
      bishopMove(board, pos, moves);
    }
  }
  return moves;
}
