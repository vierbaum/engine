#include "search.h"

double alphaBetaMax(UCI* uci, Board board, double alpha, double beta, int depthleft) {
  uci->nodes++;
  if (depthleft == 0)
    return board.eval();

  std::vector<Board> moves;
  genmoves(board, &moves);

  double score;
  for (int i = 0; i < moves.size(); i++) {
    score = alphaBetaMin(uci, moves[i], alpha, beta, depthleft - 1);

    if (score >= beta)
      return beta; // fail hard beta-cutoff
    if (score > alpha) {
      alpha = score; // alpha acts like max in MiniMax
      uci->moves = moves[i];
    }
  }

return beta;
}

double alphaBetaMin(UCI* uci, Board board, double alpha, double beta, int depthleft) {
  uci->nodes++;
  if (depthleft == 0)
    return -board.eval();

  std::vector<Board> moves;
  genmoves(board, &moves);

  double score;
  for (int i = 0; i < moves.size(); i++) {

    score = alphaBetaMax(uci, moves[i], alpha, beta, depthleft - 1);
    if (score <= alpha)
      return alpha; // fail hard alpha-cutoff
    if (score < beta) {
      beta = score; // beta acts like min in MiniMax
      uci->moves = moves[i];
    }
  }
  return beta;
}