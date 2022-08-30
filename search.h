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
      if (depthleft == 8) {
         printf("%d ", score);
         printMoveUCI(moveList.moves[moveCount]);
      }
      if (score >= beta)
         return beta;   //  fail hard beta-cutoff
      if (score > alpha) {
         alpha = score; // alpha acts like max in MiniMax
         if(depthleft == 8)
            bMove = moveList.moves[moveCount];

      }
   }
   return alpha;
}


int alphaBetaRoot(int, Board*);

void searchThreaded(void*);

#endif
