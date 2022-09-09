#ifndef SEARCH_H_
#define SEARCH_H_

#include "movegen.h"
#include "makemove.h"
#include "board.h"
#include "eval.h"
#include "pthread.h"
#include "stdlib.h"

typedef struct {
   moves* moveList;
   int depthleft;
   int* currMove;
   int* alpha;
   int* beta;
   Board* board;
   int* legalMoves;
}Data;

static int gAlpha, gBeta;
static int bMove;
static int nodes = 0;

static int killerMoves[2][64];
static int historyMoves[12][64];

static const int mvvLva[12][12] = {
  9, 15, 25, 35, 45, 55,   5, 15, 25, 35, 45, 55,
  8, 14, 24, 34, 44, 54,   4, 14, 24, 34, 44, 54,
  7, 13, 23, 33, 43, 53,   3, 13, 23, 33, 43, 53,
  6, 12, 22, 32, 42, 52,   2, 12, 22, 32, 42, 52,
  5, 11, 21, 31, 41, 51,   1, 11, 21, 31, 41, 51,
  4, 10, 20, 30, 40, 50,   0, 10, 20, 30, 40, 50,

  9, 15, 25, 35, 45, 55,   5, 15, 25, 35, 45, 55,
  8, 14, 24, 34, 44, 54,   4, 14, 24, 34, 44, 54,
  7, 13, 23, 33, 43, 53,   3, 13, 23, 33, 43, 53,
  6, 12, 22, 32, 42, 52,   2, 12, 22, 32, 42, 52,
  5, 11, 21, 31, 41, 51,   1, 11, 21, 31, 41, 51,
  4, 10, 20, 30, 40, 50,   0, 10, 20, 30, 40, 50,
};


static inline int scoreMove(int move, Board* board) {
  if (getCapture(move))
    {
      int target = P, piece;

      if (board->side == white)
        for (piece = p; piece <= k; piece++)
          {
            if (getBit(board->bitboards[piece], getTarget(move)))
              {
                target = piece;
                break;
              }
          }
      for (piece = P; piece <= K; piece++)
        {
          if (getBit(board->bitboards[piece], getTarget(move)))
            {
              target = piece;
              break;
            }
        }

      return mvvLva[getPiece(move)][target];
    }

  else
    {
      if (killerMoves[0][board->ply])
        return 3;
      else if (killerMoves[1][board->ply])
        return 2;
      else return historyMoves[getPiece(move)][getTarget(move)];
    }

  return 0;
}

static inline void sortMoves(moves* moveList, Board* board)
{
  if (moveList->count <= 1)
    return;
  int scores[moveList->count][2];
  for (int count = 0; count < moveList->count; count++) {
    scores[count][0] = scoreMove(moveList->moves[count], board);
    scores[count][1] = moveList->moves[count];
  }


  int count[56];
  moves output;
  int j, i;
  for(i = 0; i < 56; i++) count[i] = 0;
  for(i = 0; i < moveList->count; i++) {
    j = scores[i][0];
    count[j] += 1;
  }

  for(i = 1; i <= 55; i++)
    count[i] += count[i - 1];

  for(i = moveList->count - 1; i >= 0; i--) {
    j = scores[i][0];
    count[j] -= 1;
    moveList->moves[moveList->count - count[j] - 1] = scores[i][1];
  }

  return;
}

static inline int quiesce(int alpha, int beta, Board* board) {
  nodes++;
  int stand_pat = eval(board);
  if( stand_pat >= beta )
    return beta;
  if( alpha < stand_pat )
    alpha = stand_pat;
  moves moveList;
  moveList.count = 0;
  generateForcingMoves(&moveList, board);
  sortMoves(&moveList, board);
  int score;

  Board cBoard;
  for (int moveCount = 0; moveCount < moveList.count; moveCount++) {

    cBoard = *board;
    if (!makeMove(moveList.moves[moveCount], &cBoard))
      continue;

    score = -quiesce(-beta, -alpha, &cBoard);
    if (score >= beta)
      return beta;   //  fail hard beta-cutoff
    if (score > alpha) {
      alpha = score; // alpha acts like max in MiniMax
    }
  }
  return alpha;
}

static inline int alphaBeta(int alpha, int beta, int depthleft, Board* board, int ply) {
  nodes++;


  if (depthleft == 0)
    return -quiesce(-beta, -alpha, board);

  char foundPV = 0;

  moves moveList;
  generateForcingMoves(&moveList, board);
  generateMoves(&moveList, board);
  sortMoves(&moveList, board);
  int score;
  char legalMoves = 0;
  Board cBoard;
  for (int moveCount = 0; moveCount < moveList.count; moveCount++) {

    cBoard = *board;
    if (!makeMove(moveList.moves[moveCount], &cBoard))
      continue;
    legalMoves++;

    if (foundPV)
    {
        score = -alphaBeta(-alpha - 1, -alpha , depthleft - 1, &cBoard, ply + 1);
        
        if ((score > alpha) && (score < beta))
            score = -alphaBeta(-beta, -alpha, depthleft - 1, &cBoard, ply + 1);
    }
    
    else
    {
        score = -alphaBeta(-beta, -alpha, depthleft - 1, &cBoard, ply + 1);
    }

    if (score >= beta) {
      if (!getCapture(moveList.moves[moveCount])) {
        killerMoves[1][ply] = killerMoves[0][ply];
        killerMoves[0][ply] = moveList.moves[moveCount];
      }
      return beta;   //  fail hard beta-cutoff
    }
    if (score > alpha) {
      alpha = score; // alpha acts like max in MiniMax
      if (!getCapture(moveList.moves[moveCount]))
        historyMoves[getPiece(moveList.moves[moveCount])][getTarget(moveList.moves[moveCount])] = 1; // TODO += depth

      foundPV = 1;
    }
  }
  if (legalMoves == 0)
    {
      // king is in check
      if (isAttacked((board->side == white) ? ffs(board->bitboards[K]) - 1 : ffs(board->bitboards[k]) - 1, board->side ^ 1, board))
        return -49000;

      else
        return 0;
    }
  return alpha;
}


int alphaBetaRoot(int, Board*);


  void* searchThreaded(void*);

#endif
