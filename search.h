#ifndef SEARCH_H_
#define SEARCH_H_

#include "board.h"
#include "genmove.h"
#include <vector>
#include <thread>
#include <cmath>

struct Data {
  std::vector<Board> moves;
  int depthleft;
  Board* bmove;
  int n;
};

double alphaBetaMin(Board, double, double, int);

double alphaBetaMax(Board, double, double, int);

double alphaBetaRoot(Board, double, double, int);

double searchThreaded (Data*);

#endif // SEARCH_H_
