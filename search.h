#ifndef SEARCH_H_
#define SEARCH_H_

#include "movegen.h"
#include "board.h"
#include "uci.h"

double alphaBetaMax(UCI*, Board, double, double, int);

double alphaBetaMin(UCI*, Board, double, double, int);

#endif // SEARCH_H_