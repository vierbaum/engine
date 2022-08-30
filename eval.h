#ifndef EVAL_H_
#define EVAL_H_
#include "board.h"

extern int PAWNEVAL[2][3][64]; 
extern int KNIGHTEVAL[2][3][64]; 
extern int BISHOPEVAL[2][3][64]; 
extern int ROOKEVAL[2][3][64]; 
extern int QUEENEVAL[2][3][64]; 
extern int KINGEVAL[2][3][64]; 

static inline int eval(Board* board) {
    int eval = 0;
    char pos;
    U64 bb; 
    bb = board->bitboards[P];
    while(bb) {
        pos = rem1stBit(&bb);
        eval += PAWNEVAL[white][board->stage][pos];
    }

    bb = board->bitboards[p];
    while(bb) {
        pos = rem1stBit(&bb);
        eval += PAWNEVAL[black][board->stage][pos];
    }

    bb = board->bitboards[B];
    while(bb) {
        pos = rem1stBit(&bb);
        eval += BISHOPEVAL[white][board->stage][pos];
    }

    bb = board->bitboards[b];
    while(bb) {
        pos = rem1stBit(&bb);
        eval += BISHOPEVAL[black][board->stage][pos];
    }

    bb = board->bitboards[N];
    while(bb) {
        pos = rem1stBit(&bb);
        eval += KNIGHTEVAL[white][board->stage][pos];
    }

    bb = board->bitboards[n];
    while(bb) {
        pos = rem1stBit(&bb);
        eval += KNIGHTEVAL[black][board->stage][pos];
    }

    bb = board->bitboards[R];
    while(bb) {
        pos = rem1stBit(&bb);
        eval += ROOKEVAL[white][board->stage][pos];
    }

    bb = board->bitboards[r];
    while(bb) {
        pos = rem1stBit(&bb);
        eval += ROOKEVAL[black][board->stage][pos];
    }

    bb = board->bitboards[Q];
    while(bb) {
        pos = rem1stBit(&bb);
        eval += QUEENEVAL[white][board->stage][pos];
    }

    bb = board->bitboards[q];
    while(bb) {
        pos = rem1stBit(&bb);
        eval += QUEENEVAL[black][board->stage][pos];
    }

    bb = board->bitboards[K];
    while(bb) {
        pos = rem1stBit(&bb);
        eval += KINGEVAL[white][board->stage][pos];
    }

    bb = board->bitboards[k];
    while(bb) {
        pos = rem1stBit(&bb);
        eval += KINGEVAL[black][board->stage][pos];
    }
    if (board->side == white)
        return eval;
    else
        return -eval;
}

int getNum(char*);

int power(int, int);

void printPieceTable(int*);

void readEvals();

#endif