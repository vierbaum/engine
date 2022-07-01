#include "search.h"
#include "board.h"
#include "movegen.h"
#include "old/search.h"
#include <cstdio>
#include <thread>

double gAlpha;
double gBeta;

double alphaBetaMax(UCI* uci, Board* board, double alpha, double beta, int depthleft) {
  uci->nodes++;
  if (depthleft == 0)
    return board->eval();

  std::vector<Board> moves;
  genmoves(board, &moves);

  double score = 0;
  for (int i = 0; i < moves.size(); i++) {
    score = alphaBetaMin(uci, &moves[i], alpha, beta, depthleft - 1);

    if (score >= beta)
      return beta; // fail hard beta-cutoff
    if (score > alpha)
      alpha = score; // alpha acts like max in MiniMax
  }

  return alpha;
}

double alphaBetaMin(UCI* uci, Board* board, double alpha, double beta, int depthleft) {
  uci->nodes++;
  if (depthleft == 0) {
    return board->eval();
  }

  std::vector<Board> moves;
  genmoves(board, &moves);

  double score;
  for (int i = 0; i < moves.size(); i++) {
    double score = alphaBetaMax(uci, &moves[i], alpha, beta, depthleft - 1);
    if (score <= alpha)
      return alpha; // fail hard alpha-cutoff
    if (score < beta)
      beta = score; // beta acts like min in MiniMax
  }
  return beta;
}

double alphaBetaRoot(UCI *uci, Board* board, double alpha, double beta, int depthleft) {
  gAlpha = -100000;
  gBeta = 100000;

  static Board bmove;
  std::vector<Board> moves;
  genmoves(board, &moves);

  int cutoff = moves.size() / 4;
  std::vector<Board> slices[4];

  for (int n = 0; n <= 3; n++)
    for (int i = cutoff * n; i < cutoff * (n + 1); i++)
      slices[n].push_back(moves[i]);

  if (cutoff * 4 < moves.size() - 1)
    slices[3].push_back(moves[cutoff * 3 + 1]);

  Data data[4];
  for (int i = 0; i < 4; i++) {
    data[i].depthleft = depthleft;
    data[i].bmove = &bmove;
    data[i].moves = slices[i];
    data[i].n = i;
    data[i].uci = uci;
  }

  std::thread t1(searchThreaded, &data[0]);
  std::thread t2(searchThreaded, &data[1]);
  std::thread t3(searchThreaded, &data[2]);
  std::thread t4(searchThreaded, &data[3]);

  t1.join();
  t2.join();
  t3.join();
  t4.join();
  return 0;
}

double searchThreaded (Data* data) {
  std::vector<Board> moves = data->moves;
  int depthleft = data->depthleft;
  Board* bmove = data->bmove;
  UCI* uci = data->uci;

  double score = 0;
  for (int i = 0; i < moves.size(); i++) {
  loop:
  printf("info Thread %d, currmove ", data->n);
  moves[i].lastMove();
    if (!moves[i].color) { // max
      score = alphaBetaMin(uci, &moves[i], gAlpha, gBeta, depthleft - 1);

      if (score >= gBeta) {
        i++;
        goto loop;
      }
      if (score > gAlpha) {
        gAlpha = score; // alpha acts like max in MiniMax
        uci->moves = moves[i];
      }
    }
    else { // min
      double score;

      score = alphaBetaMax(uci, &moves[i], gAlpha, gBeta, depthleft - 1);
      if (score <= gAlpha) {
        i++;
        goto loop;
      }
      if (score < gBeta) {
        gBeta = score; // beta acts like min in MiniMax
        uci->moves = moves[i];
      }
    }
  }
  return 0;
}

