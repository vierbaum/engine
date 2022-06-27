#ifndef MOVEGEN_H_
#define MOVEGEN_H_
#include "board.h"
#include <vector>

const int knightMoves[] = {-12, 8, 19, 21, 12, -8, -19, -21};
const int kingMoves[] = {-1, 9, 10, 11, 1, -9, -10, -11};

void pawnMove (Board, int, std::vector<Board>*);

void knightMove (Board, int, std::vector<Board>*);

void bishopMove (Board, int, std::vector<Board>*);

void rookMove (Board, int, std::vector<Board>*);

void kingMove (Board, int, std::vector<Board>*);

Board newMove (Board*, int, int);

std::vector<Board>* genmoves(Board, std::vector<Board>*);

bool checkCheck (Board, int);

#endif // MOVEGEN_H_
