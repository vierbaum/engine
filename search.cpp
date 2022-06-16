#include "search.h"
#include <vector>

double alphaBetaMax(Board board, double alpha, double beta, int depthleft, bool root) {
  if (depthleft == 0)
    return board.eval();

  Board move;
  std::vector<Board> moves;
  genMove(&board, 1, &moves);
  for (int i = 0; i < moves.size(); i++) {
    double score = alphaBetaMin(moves[i], alpha, beta, depthleft - 1, 0);

    if (score >= beta)
      return beta;

    if (score > alpha) {
      alpha = score;
      move = moves[i];
    }
  }
  if (root)
    move.moveHist();
  return alpha;

}

double alphaBetaMin(Board board, double alpha, double beta, int depthleft, bool root) {
  if (depthleft == 0)
    return board.eval();

  Board move;


  std::vector<Board> moves;
  genMove(&board, 0, &moves);
  for (int i = 0; i < moves.size(); i++) {
    double score = alphaBetaMax(moves[i], alpha, beta, depthleft - 1, 0);

    if (score <= alpha)
      return alpha;

    if (score < beta) {
      beta = score;
      move = moves[i];
    }
  }
  if (root)
    move.moveHist();
  return beta;
}

