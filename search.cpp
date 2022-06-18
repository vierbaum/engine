#include "search.h"
#include <vector>

double alphaBetaMax(Board board, double alpha, double beta, int depthleft, bool root) {
  if (depthleft == 0)
    return board.eval();

  Board move;
  std::vector<Board> moves;
  genMove(&board, 1, &moves);
  if (moves.size() == 0)
    return 0;

  for (int i = 0; i < moves.size(); i++) {
    if(root) {
      printf("info currmove ");
      moves[i].lastMove();
    }
    double score = alphaBetaMin(moves[i], alpha, beta, depthleft - 1, 0);

    if (score >= beta)
      return beta;

    if (score > alpha) {
      alpha = score;
      move = moves[i];
      if (root)
        printf("info score cp %d\n", (int) (beta));
    }
  }
  if (root) {
    printf("info score cp %d\n", (int) (beta - 10000));
    move.lastMove();
  }
  return alpha;

}

double alphaBetaMin(Board board, double alpha, double beta, int depthleft, bool root) {
  if (depthleft == 0)
    return board.eval();

  Board move;


  std::vector<Board> moves;
  genMove(&board, 0, &moves);
  if (moves.size() == 0)
    return 0;

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
    move.lastMove();
  return beta;
}

