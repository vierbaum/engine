#ifndef GENMOVE_H_
#define GENMOVE_H_
#include <vector>
#include "board.h"

Board newBoard(Board* , int , int , int , int);

void moveDiagonal(int, int, std::vector<Board>*,  Board*, bool);

void rookMove(int, int, std::vector<Board>*, Board*, bool);

void genMove(Board*, bool, std::vector<Board>*);


#endif // GENMOVE_H_
