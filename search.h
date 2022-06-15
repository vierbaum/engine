#ifndef SEARCH_H_
#define SEARCH_H_

#include "board.h"
#include "genmove.h"
#include <vector>


double alphaBetaMin(Board, double, double, int, bool);

double alphaBetaMax(Board, double, double, int, bool);


#endif // SEARCH_H_
