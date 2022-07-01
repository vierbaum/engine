#include "movegen.h"

bool checkCheck(Board* board, int pos) {
  // bishop / queen moves
  for (int xpos = pos + 9; xpos < SIZE; xpos += 9) {// up left
    if (board->board[xpos] == OUTOFBOUNDS)
      break;
    else if ((board->color && (board->bbW & (1ULL << board->B120to64(xpos))) != 0) || (!board->color && (board->bbB & (1ULL << board->B120to64(xpos)) ) != 0)) // hit own piece
      break;
    else if ((board->color && (board->bbB & (1ULL << board->B120to64(xpos))) != 0 && !(board->board[xpos] == bB || board->board[xpos] == bQ)) || (board->color && (board->bbB & (1ULL << board->B120to64(xpos))) != 0 && !(board->board[xpos] == bB || board->board[xpos] == bQ))) // hit piece other then bishop or queen
      break;
    else if (board->board[xpos] == EMPTY)
      continue;
    else
      return 1;
  }
  for (int xpos = pos + 11; xpos < SIZE; xpos += 11) // up right
    if (board->board[xpos] == OUTOFBOUNDS)
      break;
    else if ((board->color && (board->bbW & (1ULL << board->B120to64(xpos)) ) != 0) || (!board->color && (board->bbB & (1ULL << board->B120to64(xpos)) ) != 0)) // hit own piece
      break;
    else if ((board->color && (board->bbB & (1ULL << board->B120to64(xpos))) != 0 && !(board->board[xpos] == bB || board->board[xpos] == bQ)) || (board->color && (board->bbB & (1ULL << board->B120to64(xpos))) != 0 && !(board->board[xpos] == bB || board->board[xpos] == bQ))) // hit piece other then bishop or queen
      break;
    else if (board->board[xpos] == EMPTY)
      continue;
    else
      return 1;

  for (int xpos = pos - 11; xpos < SIZE; xpos -= 11) // down left
    if (board->board[xpos] == OUTOFBOUNDS)
      break;
    else if ((board->color && (board->bbW & (1ULL << board->B120to64(xpos)) ) != 0) || (!board->color && (board->bbB & (1ULL << board->B120to64(xpos)) ) != 0)) // hit own piece
      break;
    else if ((board->color && (board->bbB & (1ULL << board->B120to64(xpos))) != 0 && !(board->board[xpos] == bB || board->board[xpos] == bQ)) || (board->color && (board->bbB & (1ULL << board->B120to64(xpos))) != 0 && !(board->board[xpos] == bB || board->board[xpos] == bQ))) // hit piece other then bishop or queen
      break;
    else if (board->board[xpos] == EMPTY)
      continue;
    else
      return 1;

  for (int xpos = pos - 9; xpos < SIZE; xpos -= 9) { // down right
    if (board->board[xpos] == OUTOFBOUNDS)
      break;
    else if ((board->color && (board->bbW & (1ULL << board->B120to64(xpos)) ) != 0) || (!board->color && (board->bbB & (1ULL << board->B120to64(xpos)) ) != 0)) // hit own piece
      break;
    else if ((board->color && (board->bbB & (1ULL << board->B120to64(xpos))) != 0 && !(board->board[xpos] == bB || board->board[xpos] == bQ)) || (board->color && (board->bbB & (1ULL << board->B120to64(xpos))) != 0 && !(board->board[xpos] == bB || board->board[xpos] == bQ))) // hit piece other then bishop or queen
      break;
    else if (board->board[xpos] == EMPTY)
      continue;
    else
      return 1;
  }
  // Rook / Queen Moves
  for (int xpos = pos + 10; xpos < SIZE; xpos += 10) {// up
    if (board->board[xpos] == OUTOFBOUNDS)
      break;
    else if ((board->color && (board->bbW & (1ULL << board->B120to64(xpos)) ) != 0) || (!board->color && (board->bbB & (1ULL << board->B120to64(xpos)) ) != 0)) // hit own piece
      break;
    else if ((board->color && (board->bbB & (1ULL << board->B120to64(xpos))) != 0 && !(board->board[xpos] == bR || board->board[xpos] == bQ)) || (board->color && (board->bbB & (1ULL << board->B120to64(xpos))) != 0 && !(board->board[xpos] == wR || board->board[xpos] == bQ))) // hit piece other then rook or queen
      break;
    else if (board->board[xpos] == EMPTY)
      continue;
    else
      return 1;
  }
  for (int xpos = pos - 10; xpos < SIZE; xpos -= 10) {// down
    if (board->board[xpos] == OUTOFBOUNDS)
      break;
    else if ((board->color && (board->bbW & (1ULL << board->B120to64(xpos)) ) != 0) || (!board->color && (board->bbB & (1ULL << board->B120to64(xpos)) ) != 0)) // hit own piece
      break;
    else if ((board->color && (board->bbB & (1ULL << board->B120to64(xpos))) != 0 && !(board->board[xpos] == bR || board->board[xpos] == bQ)) || (board->color && (board->bbB & (1ULL << board->B120to64(xpos))) != 0 && !(board->board[xpos] == wR || board->board[xpos] == bQ))) // hit piece other then rook or queen
      break;
    else if (board->board[xpos] == EMPTY)
      continue;
    else
      return 1;
  }
  for (int xpos = pos + 1; xpos < SIZE; xpos += 1) {// right
    if (board->board[xpos] == OUTOFBOUNDS)
      break;
    else if ((board->color && (board->bbW & (1ULL << board->B120to64(xpos)) ) != 0) || (!board->color && (board->bbB & (1ULL << board->B120to64(xpos)) ) != 0)) // hit own piece
      break;
    else if ((board->color && (board->bbB & (1ULL << board->B120to64(xpos))) != 0 && !(board->board[xpos] == bR || board->board[xpos] == bQ)) || (board->color && (board->bbB & (1ULL << board->B120to64(xpos))) != 0 && !(board->board[xpos] == wR || board->board[xpos] == bQ))) // hit piece other then rook or queen
      break;
    else if (board->board[xpos] == EMPTY)
      continue;
    else
      return 1;
  }
  for (int xpos = pos - 1; xpos < SIZE; xpos -= 1) {// left
    if (board->board[xpos] == OUTOFBOUNDS)
      break;
    else if ((board->color && (board->bbW & (1ULL << board->B120to64(xpos)) ) != 0) || (!board->color && (board->bbB & (1ULL << board->B120to64(xpos)) ) != 0)) // hit own piece
      break;
    else if ((board->color && (board->bbB & (1ULL << board->B120to64(xpos))) != 0 && !(board->board[xpos] == bR || board->board[xpos] == bQ)) || (board->color && (board->bbB & (1ULL << board->B120to64(xpos))) != 0 && !(board->board[xpos] == wR || board->board[xpos] == bQ))) // hit piece other then rook or queen
      break;
    else if (board->board[xpos] == EMPTY)
      continue;
    else
      return 1;
  }
  // knight moves
  for (int i = 0; i < 8; i++) {
    int xpos = knightMoves[i];
    if ((board->color && board->board[xpos] == bK) || (!board->color && board->board[xpos] == wK))
      return 1;
  }

  // pawn
  if (board->color && (board->board[pos + 9] == bP || board->board[pos + 11] == bP))
    return 1;
  if (!board->color && (board->board[pos - 9] == wP || board->board[pos - 11] == wP))
    return 1;

  // king
  for (int i = 0; i < 8; i++) {
    int xpos = pos + kingMoves[i];
    if (board->color && board->board[xpos] == bK)
      return 1;
    else if (!board->color && board->board[xpos] == wK)
      return 0;
  }

  return 0;
}
