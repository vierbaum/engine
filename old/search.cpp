#include "search.h"
#include "board.h"
#include "genmove/genmove.h"
#include <vector>

double gAlpha = -10000;
double gBeta = 10000;

double alphaBetaMax(Board board, double alpha, double beta, int depthleft) {
  if (depthleft == 0)
    return quiescenceSearch(board, alpha, beta, 0);
    //return board.eval();

  std::vector<Board> moves;
  genMove(&board, &moves);
  if (moves.size() == 0)
    return 0;

  for (int i = 0; i < moves.size(); i++) {
    double score = alphaBetaMin(moves[i], alpha, beta, depthleft - 1);

    if (score >= beta)
      return beta;

    if (score > alpha) {
      alpha = score;
    }
  }
  return alpha;

}

double alphaBetaMin(Board board, double alpha, double beta, int depthleft) {
  if (depthleft == 0)
    return quiescenceSearch(board, alpha, beta, 0);
    //return board.eval();

  std::vector<Board> moves;
  genMove(&board, &moves);

  if (moves.size() == 0)
    return 0;

  for (int i = 0; i < moves.size(); i++) {
    double score = alphaBetaMax(moves[i], alpha, beta, depthleft - 1);

    if (score <= alpha)
      return alpha;

    if (score < beta)
      beta = score;
  }
  return beta;
}

double alphaBetaRoot(Board board, double alpha, double beta, int depthleft, bool color) {

  printf("info color %d\n", color);

  gAlpha = -10000;
  gBeta = 10000;
  static Board bmove;
  std::vector<Board> moves;
  genMove(&board, &moves);

  int cutoff = moves.size() / 4;

  std::vector<Board> slices[4];


  for (int n = 0; n <= 3; n++)
    for (int i = cutoff * n; i < cutoff * (n + 1); i++)
      slices[n].push_back(moves[i]);

  if (cutoff * 4 < moves.size() - 1)
    slices[3].push_back(moves[cutoff * 3 + 1]);

  Data data0;
  data0.depthleft = depthleft;
  data0.bmove = &bmove;
  data0.moves = slices[0];
  data0.n = 0;
  data0.color = color;
  std::thread t1(searchThreaded, &data0);

  Data data1;
  data1.depthleft = depthleft;
  data1.bmove = &bmove;
  data1.moves = slices[1];
  data1.n = 1;
  data1.color = color;
  std::thread t2(searchThreaded, &data1);

  Data data2;
  data2.depthleft = depthleft;
  data2.bmove = &bmove;
  data2.moves = slices[2];
  data2.n = 2;
  data2.color = color;
  std::thread t3(searchThreaded, &data2);

  Data data3;
  data3.depthleft = depthleft;
  data3.bmove = &bmove;
  data3.moves = slices[3];
  data3.n = 3;
  data3.color = color;
  std::thread t4(searchThreaded, &data3);

  t1.join();
  t2.join();
  t3.join();
  t4.join();


  //for (int i = 0; i < 4; i++) {
    //searchThreaded(slices[i], depthleft, &bmove);
  //}
  bmove.lastMove();
  return 0;
}

double searchThreaded (Data* data) {


  std::vector<Board> moves = data->moves;
  int depthleft = data->depthleft;
  Board* bmove = data->bmove;

  Board move;
  int beta = 10000;

  double score;
  for (int i = 0; i < moves.size(); i++) {
    printf("info thread %d currmove ", data->n);
      moves[i].pMoves();
      if (data->color) {

        score = alphaBetaMin(moves[i], gAlpha, beta, depthleft - 1);
        if (score >= beta)
          return beta;

        if (score > gAlpha) {
          gAlpha = score;
          *bmove = moves[i];
          printf("info score cp %d\n", (int) std::round(gAlpha * 100));
        }
      }
      else {
        score = alphaBetaMax(moves[i], gAlpha, beta, depthleft - 1);
        if (score <= gAlpha)
          return gAlpha;

        if (score < gBeta) {
          gBeta = score;
          *bmove = moves[i];
          printf("info score cp %d\n", (int) std::round(gBeta * 100));

        }
      }

  }
  return 0;
}

double quiescenceSearch(Board board, double alpha, double beta, int qDepth) {
  std::vector<Board> moves;
  genForcingMoves(&board, board.color, &moves);

  double standPat;
  if (board.color)
    standPat = board.eval();
  else
    standPat = -board.eval();

  if (standPat >= beta)
    return beta;
  if (alpha < standPat)
    alpha = standPat;

  double score;
  if (qDepth < 5)
    for (int i = 0; i < moves.size(); i++) {
      score = -quiescenceSearch(moves[i], -beta, -alpha, qDepth + 1);

      if (score >= beta) {
        return beta;
      }
      if (score > alpha) {
        alpha = score;
      }

    }
    return alpha;
}
