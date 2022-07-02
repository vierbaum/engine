#ifndef SEARCH_H_
#define SEARCH_H_

#include "movegen.h"
#include "board.h"
#include "uci.h"
#include <vector>
#include <thread>
#include <cmath>

struct Data {
  std::vector<Board> moves;
  int depthleft;
  Board* bmove;
  int n;
  bool color;
  UCI* uci;
  int* currMove;
};

double alphaBetaMax(UCI*, Board*, double, double, int);

double alphaBetaMin(UCI*, Board*, double, double, int);

double alphaBetaRoot(UCI*, Board*, double, double, int);

double searchThreaded(Data*);
#endif // SEARCH_H_