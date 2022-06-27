#include "movegen.h"
#include "board.h"
#include <vector>


std::vector<Board>* genmoves(Board board, std::vector<Board>* moves) {
  int pos;
  if (board.color) {
     if (board.numPieces[wP] != 0)
       for (int i = 0; i < board.numPieces[wP]; i++) {
         pos = board.pieceList[wP][i];
         pawnMove(board, pos, moves);
       }
     if (board.numPieces[wN] != 0)
       for (int i = 0; i < board.numPieces[wN]; i++) {
         pos = board.pieceList[wN][i];
         knightMove(board, pos, moves);
       }
     if (board.numPieces[wB] != 0)
       for (int i = 0; i < board.numPieces[wB]; i++) {
         pos = board.pieceList[wB][i];
         bishopMove(board, pos, moves);
       }
     if (board.numPieces[wR] != 0)
       for (int i = 0; i < board.numPieces[wR]; i++) {
         pos = board.pieceList[wR][i];
         rookMove(board, pos, moves);
       }
     if (board.numPieces[wQ] != 0)
       for (int i = 0; i < board.numPieces[wQ]; i++) {
         pos = board.pieceList[wQ][i];
         rookMove(board, pos, moves);
         bishopMove(board, pos, moves);
       }
  }
  else {
    if (board.numPieces[bP] != 0)
      for (int i = 0; i < board.numPieces[bP]; i++) {
        pos = board.pieceList[bP][i];
        pawnMove(board, pos, moves);
      }

    if (board.numPieces[bN] != 0)
      for (int i = 0; i < board.numPieces[bN]; i++) {
        pos = board.pieceList[bN][i];
        knightMove(board, pos, moves);
      }
    if (board.numPieces[bB] != 0)
      for (int i = 0; i < board.numPieces[bB]; i++) {
        pos = board.pieceList[bB][i];
        bishopMove(board, pos, moves);
      }
    if (board.numPieces[bR] != 0)
      for (int i = 0; i < board.numPieces[bR]; i++) {
        pos = board.pieceList[bR][i];
        rookMove(board, pos, moves);
      }
    if (board.numPieces[wQ] != 0)
      for (int i = 0; i < board.numPieces[bQ]; i++) {
        pos = board.pieceList[bQ][i];
        rookMove(board, pos, moves);
        bishopMove(board, pos, moves);
      }
  }
  return moves;
}
