#ifndef BOARD_H_
#define BOARD_H_

#include <stdio.h>
#include <stdlib.h>

#define U64 unsigned long long
#define countbits(board) __builtin_popcountll(board)
#define ffs(board) __builtin_ffs(board)
#define USE_32_BIT_MULTIPLICATIONS

const U64 onA = 72340172838076673ULL;
const U64 onB = 144680345676153346ULL;
const U64 onH = 9259542123273814144ULL;
const U64 onG = 4629771061636907072ULL;

enum {
  A8, B8, C8, D8, E8, F8, G8, H8,
  A7, B7, C7, D7, E7, F7, G7, H7,
  A6, B6, C6, D6, E6, F6, G6, H6,
  A5, B5, C5, D5, E5, F5, G5, H5,
  A4, B4, C4, D4, E4, F4, G4, H4,
  A3, B3, C3, D3, E3, F3, G3, H3,
  A2, B2, C2, D2, E2, F2, G2, H2,
  A1, B1, C1, D1, E1, F1, G1, H1
};

enum {rook, bishop};

enum {white, black};

const int bishopOccBits[64] = {
    6, 5, 5, 5, 5, 5, 5, 6, 
    5, 5, 5, 5, 5, 5, 5, 5, 
    5, 5, 7, 7, 7, 7, 5, 5, 
    5, 5, 7, 9, 9, 7, 5, 5, 
    5, 5, 7, 9, 9, 7, 5, 5, 
    5, 5, 7, 7, 7, 7, 5, 5, 
    5, 5, 5, 5, 5, 5, 5, 5, 
    6, 5, 5, 5, 5, 5, 5, 6
};

const int rookOcckBits[64] = {
    12, 11, 11, 11, 11, 11, 11, 12, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    12, 11, 11, 11, 11, 11, 11, 12
};

const int BitTable[64] = {
  63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
  51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
  26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
  58, 20, 37, 17, 36, 8
};
extern U64 pawnAttacks[2][64];
extern U64 knightAttacks[64];
extern U64 kingAttacks[2][64];
extern U64 rookMN[64];
extern U64 bishopMN[64];
extern U64 bishopAttacks[64][512];
extern U64 rookAttacks[64][4096];

void printBitBoard(U64);

void setPiece(U64*, int);

void removePiece(U64*, int);

U64 random_uint64();

U64 random_uint64_fewbits();

int transform(U64 b, U64 magic, int bits);

U64 genPawnAttacks(int, bool);

U64 genKnightAttacks(int);

U64 genKingAttacks(int, bool);

U64 genBishopOccupancy(int);

U64 genRookOccupancy(int);

U64 genBishopAttack(int, U64);

U64 genRookAttack(int, U64);

int pop1stBit(U64*);

U64 setOccupancy(int, int, U64);

U64 findMagicNumber(int, int, U64);

void initMagicNumbers();

void initPawnAttacks();

void initKnightAttacks();

void initKingAttacks();

void initSliderAttacks();
#endif // BOARD_H_