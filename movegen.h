#ifndef MOVEGEN_H_
#define MOVEGEN_H_
#include "board.h"
#include <vector>

std::vector<Board>* genmoves(Board, std::vector<Board>*);

Board newMove (Board, int, int);
#endif // MOVEGEN_H_
