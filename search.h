#ifndef SEARCH_H_
#define SEARCH_H_

#include "movegen.h"
#include "makemove.h"
#include "board.h"
#include "eval.h"
#include "pthread.h"

typedef struct {
   moves* moveList;
   int depthleft;
   int* currMove;
}Data;

static int gAlpha, gBeta;
static int bMove;
static int nodes = 0;

static inline int alphaBeta(int alpha, int beta, int depthleft, Board* board) {
   if (depthleft == 0)
      return eval(board);
   nodes++;
   moves moveList;
   generateMoves(&moveList, board);
   int score;

   Board cBoard;
   for (int moveCount = 0; moveCount < moveList.count; moveCount++) {   

      cBoard = *board;
         if (!makeMove(moveList.moves[moveCount], &cBoard))
            continue;

      score = -alphaBeta(-beta, -alpha, depthleft - 1, &cBoard);
      if (score >= beta)
         return beta;   //  fail hard beta-cutoff
      if (score > alpha) {
         alpha = score; // alpha acts like max in MiniMax

      }
   }
   return alpha;
}


int alphaBetaRoot(int, Board*);

static inline int quiesce(int alpha, int beta, Board* board) {

   nodes++;
    int stand_pat = eval(board);
    if( stand_pat >= beta )
        return beta;
    if( alpha < stand_pat )
        alpha = stand_pat;
   moves moveList;
   generateForcingMoves(&moveList, board);
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

void searchThreaded(void*);


#endif
