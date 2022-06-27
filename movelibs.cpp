#include "movegen.h"

Board newMove(Board* move, int from, int to) {
  //printf("%d %d\n", from, to);
  Board b = *move;
  b.makeMove120(from, to);
  return b;
}

void knightMove(Board board, int pos, std::vector<Board> *moves) {
  for (int i = 0; i < 8; i++) {
    int xpos = pos + knightMoves[i];
    if (board.color && board.board[xpos] != OUTOFBOUNDS &&
        (board.bbW & (1ULL << board.B120to64(xpos))) == 0)
      moves->push_back(newMove(&board, pos, xpos));
    else if (!board.color && board.board[xpos] != OUTOFBOUNDS &&
             (board.bbB & (1ULL << board.B120to64(xpos))) == 0)
      moves->push_back(newMove(&board, pos, xpos));
  }
  return;
}

void bishopMove(Board board, int pos, std::vector<Board> *moves) {
  for (int xpos = pos + 9; xpos < SIZE; xpos += 9) // up left
    if (board.board[xpos] == OUTOFBOUNDS)
      break;
    else if (board.color && (board.bbW & (1ULL << board.B120to64(xpos))) == 0) {
      moves->push_back(newMove(&board, pos, xpos));
      if ((board.bbB & (1ULL << board.B120to64(xpos))) != 0)
        break;
    } else if (!board.color &&
               (board.bbB & (1ULL << board.B120to64(xpos))) == 0) {
      moves->push_back(newMove(&board, pos, xpos));
      if ((board.bbW & (1ULL << board.B120to64(xpos))) != 0)
        break;
    } else
      break;

  for (int xpos = pos + 11; xpos < SIZE; xpos += 11) // up right
    if (board.board[xpos] == OUTOFBOUNDS)
      break;
    else if (board.color && (board.bbW & (1ULL << board.B120to64(xpos))) == 0) {
      moves->push_back(newMove(&board, pos, xpos));
      if ((board.bbB & (1ULL << board.B120to64(xpos))) != 0)
        break;
    } else if (!board.color &&
               (board.bbB & (1ULL << board.B120to64(xpos))) == 0) {
      moves->push_back(newMove(&board, pos, xpos));
      if ((board.bbW & (1ULL << board.B120to64(xpos))) != 0)
        break;
    } else
      break;

  for (int xpos = pos - 11; xpos < SIZE; xpos -= 11) // down left
    if (board.board[xpos] == OUTOFBOUNDS)
      break;
    else if (board.color && (board.bbW & (1ULL << board.B120to64(xpos))) == 0) {
      moves->push_back(newMove(&board, pos, xpos));
      if ((board.bbB & (1ULL << board.B120to64(xpos))) != 0)
        break;
    } else if (!board.color &&
               (board.bbB & (1ULL << board.B120to64(xpos))) == 0) {
      moves->push_back(newMove(&board, pos, xpos));
      if ((board.bbW & (1ULL << board.B120to64(xpos))) != 0)
        break;
    } else
      break;

  for (int xpos = pos - 9; xpos < SIZE; xpos -= 9) // down right
    if (board.board[xpos] == OUTOFBOUNDS)
      break;
    else if (board.color && (board.bbW & (1ULL << board.B120to64(xpos))) == 0) {
      moves->push_back(newMove(&board, pos, xpos));
      if ((board.bbB & (1ULL << board.B120to64(xpos))) != 0)
        break;
    } else if (!board.color &&
               (board.bbB & (1ULL << board.B120to64(xpos))) == 0) {
      moves->push_back(newMove(&board, pos, xpos));
      if ((board.bbW & (1ULL << board.B120to64(xpos))) != 0)
        break;
    } else
      break;
}

void rookMove(Board board, int pos, std::vector<Board> *moves) {
  for (int xpos = pos + 1; xpos < SIZE; xpos++) {
    if (board.board[xpos] == OUTOFBOUNDS)
      break;
    else if (board.color && (board.bbW & (1ULL << board.B120to64(xpos))) == 0) {
      moves->push_back(newMove(&board, pos, xpos));
      if ((board.bbB & (1ULL << board.B120to64(xpos))) != 0)
        break;
    } else if (!board.color &&
               (board.bbB & (1ULL << board.B120to64(xpos))) == 0) {
      moves->push_back(newMove(&board, pos, xpos));
      if ((board.bbW & (1ULL << board.B120to64(xpos))) != 0)
        break;

    } else
      break;
  }

  for (int xpos = pos - 1; xpos >= 0; xpos--) {
    if (board.board[xpos] == OUTOFBOUNDS)
      break;
    else if (board.color && (board.bbW & (1ULL << board.B120to64(xpos))) == 0) {
      moves->push_back(newMove(&board, pos, xpos));
      if ((board.bbB & (1ULL << board.B120to64(xpos))) != 0)
        break;
    } else if (!board.color &&
               (board.bbB & (1ULL << board.B120to64(xpos))) == 0) {
      moves->push_back(newMove(&board, pos, xpos));
      if ((board.bbW & (1ULL << board.B120to64(xpos))) != 0)
        break;

    } else
      break;
  }

  for (int xpos = pos + 10; xpos < SIZE; xpos += 10) {
    if (board.board[xpos] == OUTOFBOUNDS)
      break;
    else if (board.color && (board.bbW & (1ULL << board.B120to64(xpos))) == 0) {
      moves->push_back(newMove(&board, pos, xpos));
      if ((board.bbB & (1ULL << board.B120to64(xpos))) != 0)
        break;
    } else if (!board.color &&
               (board.bbB & (1ULL << board.B120to64(xpos))) == 0) {
      moves->push_back(newMove(&board, pos, xpos));
      if ((board.bbW & (1ULL << board.B120to64(xpos))) != 0)
        break;

    } else
      break;
  }

  for (int xpos = pos - 10; xpos >= 0; xpos -= 10) {
    if (board.board[xpos] == OUTOFBOUNDS)
      break;
    else if (board.color && (board.bbW & (1ULL << board.B120to64(xpos))) == 0) {
      moves->push_back(newMove(&board, pos, xpos));
      if ((board.bbB & (1ULL << board.B120to64(xpos))) != 0)
        break;
    } else if (!board.color &&
               (board.bbB & (1ULL << board.B120to64(xpos))) == 0) {
      moves->push_back(newMove(&board, pos, xpos));
      if ((board.bbW & (1ULL << board.B120to64(xpos))) != 0)
        break;

    } else
      break;
  }
  return;
}

void pawnMove(Board board, int pos, std::vector<Board> *moves) {
  if (board.color) {
    if (board.board[pos + 10] == EMPTY) {
      moves->push_back(newMove(&board, pos, pos + 10));
      if (pos <= B8 && board.board[pos + 20] == EMPTY) {
        Board m = newMove(&board, pos, pos + 20);
        m.enPassant = pos + 10;
        moves->push_back(m);
      }
    }
    if ((board.board[pos + 9] > wK && board.board[pos + 9] <= bK) ||
        board.enPassant == pos + 9)
      moves->push_back(newMove(&board, pos, pos + 9));
    if ((board.board[pos + 11] > wK && board.board[pos + 11] <= bK) ||
        board.enPassant == pos + 11)
      moves->push_back(newMove(&board, pos, pos + 11));
  } else {
    if (board.board[pos - 10] == EMPTY) {
      moves->push_back(newMove(&board, pos, pos - 10));
      if (pos <= B8 && board.board[pos - 20] == EMPTY) {
        Board m = newMove(&board, pos, pos - 20);
        m.enPassant = pos - 10;
        moves->push_back(m);
      }
    }
    if ((board.board[pos - 9] > wK && board.board[pos - 9] <= bK) ||
        board.enPassant == pos - 9)
      moves->push_back(newMove(&board, pos, pos - 9));
    if ((board.board[pos - 11] > wK && board.board[pos - 11] <= bK) ||
        board.enPassant == pos - 11)
      moves->push_back(newMove(&board, pos, pos - 11));
  }
}

void kingMove(Board board, int pos, std::vector<Board> *moves) {
  int xpos;
  for (int i = 0; i < 8; i++) {
    xpos = pos + kingMoves[i];
    if (board.board[xpos] == OUTOFBOUNDS)
      continue;
    else if (board.color && (board.bbW & (1ULL << board.B120to64(xpos))) == 0)
      moves->push_back(newMove(&board, pos, xpos));
    else if (!board.color && (board.bbB & (1ULL << board.B120to64(xpos))) == 0)
      moves->push_back(newMove(&board, pos, xpos));
  }
  if (board.color && board.castlingRights[0] && !checkCheck(board, 24))
    moves->push_back(newMove(&board, pos, 23));
  if (board.color && board.castlingRights[1] && !checkCheck(board, 26))
    moves->push_back(newMove(&board, pos, 27));
  if (!board.color && board.castlingRights[2] && !checkCheck(board, 94))
    moves->push_back(newMove(&board, pos, 93));
  if (!board.color && board.castlingRights[3] && !checkCheck(board, 96))
    moves->push_back(newMove(&board, pos, 97));
  return;
}
