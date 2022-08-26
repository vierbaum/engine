#ifndef EVAL_H_
#define EVAL_H_
#include "board.h"

extern int PAWNEVAL[2][3][64]; 
extern int KNIGHTEVAL[2][3][64]; 
extern int BISHOPEVAL[2][3][64]; 
extern int ROOKEVAL[2][3][64]; 
extern int QUEENEVAL[2][3][64]; 
extern int KINGEVAL[2][3][64]; 

static inline int eval() {
    int eval;
    eval += countbits(bitboards[P]) * 100;
    eval += countbits(bitboards[N]) * 300;
    eval += countbits(bitboards[B]) * 325;
    eval += countbits(bitboards[R]) * 500;
    eval += countbits(bitboards[Q]) * 1000;

    eval -= countbits(bitboards[p]) * 100;
    eval -= countbits(bitboards[n]) * 300;
    eval -= countbits(bitboards[b]) * 325;
    eval -= countbits(bitboards[r]) * 500;
    eval -= countbits(bitboards[q]) * 1000;
    return (side == white) ? eval : -eval;
}

int getNum(char*);

int power(int, int);

void printPieceTable(int*);

void readEvals();

#endif