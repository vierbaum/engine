#ifndef MOVEGEN_H_
#define MOVEGEN_H_
#include "board.h"
#include <vector>

const int knightMoves[] = {-12, 8, 19, 21, 12, -8, -19, -21};

void knightMove (Board, int, std::vector<Board>*);

void bishopMove (Board, int, std::vector<Board>*);

void rookMove (Board, int, std::vector<Board>*);

Board newMove (Board, int, int);

std::vector<Board>* genmoves(Board, std::vector<Board>*);

#endif // MOVEGEN_H_
