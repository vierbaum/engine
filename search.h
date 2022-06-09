#ifndef SEARCH_H_
#define SEARCH_H_

#include "board.h"
#include "eval.h"
#include "genmove.h"
#include <vector>

Board bestBoard;

double alphaBetaMax(Board*, double, double, int, bool);

double alphaBetaMin(Board* board, double alpha, double beta, int depthleft, bool root) {
  Board bboard;
  if ( depthleft == 0 )
    return 1 * eval(board);

  std::vector<Board> moves = genMove(board, 0);
  for (int i = 0; i < moves.size(); i++) {
    double score = alphaBetaMax(&moves[i], alpha, beta, depthleft - 1, 0);
    if( score <= alpha )
      return alpha; // fail hard alpha-cutoff
    if( score < beta )
      beta = score; // beta acts like min in MiniMax
  }
  return beta;
}

double alphaBetaMax(Board* board, double alpha, double beta, int depthleft, bool root) {
   if (depthleft == 0)
     return eval(board);

   std::vector<Board> moves = genMove(board, 1);
   for (int i = 0; i < moves.size(); i++) {
      double score = alphaBetaMin(&moves[i], alpha, beta, depthleft - 1, 0);
      if(score >= beta)
         return beta;   // fail hard beta-cutoff
      if(score > alpha) {
         alpha = score; // alpha acts like max in MiniMax
         bestBoard = moves[i];
      }
   }
   return alpha;
}

#endif // SEARCH_H_
