#ifndef BOARD_H_
#define BOARD_H_

#include <stdio.h>
#include <string.h>

#define U64 unsigned long long
#define countbits(board) __builtin_popcountll(board)
#define ffs(board) __builtin_ffsll(board)
#define USE_32_BIT_MULTIPLICATIONS
#define BLACKPRINT "\x1b[30;41m"

static const U64 onA = 72340172838076673ULL;
static const U64 onB = 144680345676153346ULL;
static const U64 onH = 9259542123273814144ULL;
static const U64 onG = 4629771061636907072ULL;
enum { 
  A8, B8, C8, D8, E8, F8, G8, H8,
  A7, B7, C7, D7, E7, F7, G7, H7,
  A6, B6, C6, D6, E6, F6, G6, H6,
  A5, B5, C5, D5, E5, F5, G5, H5,
  A4, B4, C4, D4, E4, F4, G4, H4,
  A3, B3, C3, D3, E3, F3, G3, H3,
  A2, B2, C2, D2, E2, F2, G2, H2,
  A1, B1, C1, D1, E1, F1, G1, H1, notOnBoard
};

enum {WKC = 1, WQC = 2, BKC = 4, BQC = 8};

enum {P, N, B, R, Q, K, p, n, b, r, q, k};

enum {rook, bishop};

enum {white, black, both};

static const int charToPieces[] = {
    ['P'] = P,
    ['N'] = N,
    ['B'] = B,
    ['R'] = R,
    ['Q'] = Q,
    ['K'] = K,
    ['p'] = p,
    ['n'] = n,
    ['b'] = b,
    ['r'] = r,
    ['q'] = q,
    ['k'] = k
};

static const char* SQUARER[] = {
  "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
  "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
  "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
  "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
  "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
  "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
  "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
  "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1", "NAN"
};

static const char* PIECER = "PNBRQKpnbrqk";

static const int bishopOccBits[64] = {
    6, 5, 5, 5, 5, 5, 5, 6, 
    5, 5, 5, 5, 5, 5, 5, 5, 
    5, 5, 7, 7, 7, 7, 5, 5, 
    5, 5, 7, 9, 9, 7, 5, 5, 
    5, 5, 7, 9, 9, 7, 5, 5, 
    5, 5, 7, 7, 7, 7, 5, 5, 
    5, 5, 5, 5, 5, 5, 5, 5, 
    6, 5, 5, 5, 5, 5, 5, 6
};

static const int rookOccBits[64] = {
    12, 11, 11, 11, 11, 11, 11, 12, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    12, 11, 11, 11, 11, 11, 11, 12
};

static const int BitTable[64] = {
  63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
  51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
  26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
  58, 20, 37, 17, 36, 8
};

extern U64 pawnAttacks[2][64];
extern U64 knightAttacks[64];
extern U64 kingAttacks[64];
extern U64 rookMN[64];
extern U64 bishopMN[64];
extern U64 bishopAttacks[64][512];
extern U64 rookAttacks[64][4096];
extern U64 bishopMasks[64];
extern U64 rookMasks[64];
extern U64 bitboards[12];
extern U64 occupancies[3];
extern char side;
extern char castling;
extern char enP;

U64 findMagicNumber(int, int, int);

U64 genBishopAttack(int, U64);

U64 genBishopOccupancy(int);

U64 genKingAttacks(int);

U64 genKnightAttacks(int);

U64 genPawnAttacks(int, char);

U64 genRookAttack(int, U64);

U64 genRookOccupancy(int);

static inline U64 getBishopAttacks(int pos, U64 occ) {
    occ &= bishopMasks[pos];
    occ *= bishopMN[pos];
    occ >>= 64 - bishopOccBits[pos];
    return bishopAttacks[pos][occ];
}

static inline char getBit(U64 board, int pos) {
  return (board & (1ULL << pos)) != 0;
}

static inline U64 getRookAttacks(int pos, U64 occ) {
    occ &= rookMasks[pos];
    occ *= rookMN[pos];
    occ >>= 64 - rookOccBits[pos];
    return rookAttacks[pos][occ];
}

static inline U64 getQueenAttacks(int pos, U64 occ) {
  U64 bishop = 0;
  U64 occ1 = occ;
  occ &= bishopMasks[pos];
  occ *= bishopMN[pos];
  occ >>= 64 - bishopOccBits[pos];
  bishop = bishopAttacks[pos][occ];

  occ1 &= rookMasks[pos];
  occ1 *= rookMN[pos];
  occ1 >>= 64 - rookOccBits[pos];
  return rookAttacks[pos][occ1] | bishop;
}

static inline char isAttacked(int square, int cSide) {
  if ((cSide == white) && (pawnAttacks[black][square] & bitboards[P])) return 1;
  if ((cSide == black) && (pawnAttacks[white][square] & bitboards[p])) return 1;
  if (knightAttacks[square] & ((cSide == white) ? bitboards[N] : bitboards[n])) return 1;
  if (getBishopAttacks(square, occupancies[both]) & ((cSide == white) ? bitboards[B] : bitboards[b])) return 1;
  if (getRookAttacks(square, occupancies[both]) & ((cSide == white) ? bitboards[R] : bitboards[r])) return 1;    
  if (getQueenAttacks(square, occupancies[both]) & ((cSide == white) ? bitboards[Q] : bitboards[q])) return 1;
  if ((cSide == white) && kingAttacks[square] & ((cSide == white) ? bitboards[K] : bitboards[k])) return 1;
  if ((cSide == black) && kingAttacks[square] & ((cSide == white) ? bitboards[K] : bitboards[k])) return 1;
  // by default return false
  return 0;
}

void initKingAttacks();

void initKnightAttacks();

void initMagicNumbers();

void initPawnAttacks();

void initSliderAttacks();

int pop1stBit(U64*);

void printAttackedSquares(char);

void printBitBoard(U64);

void printBoard();

void printBoardSimple();

unsigned int random32();

U64 random64();

static inline char rem1stBit(U64* b) {
    int p = ffs(*b) - 1;
    *b ^= (1ULL << p);
    return p;
}

void removePiece(U64*, int);

U64 setOccupancy(int, int, U64);

void setUpBoardFromFen(char*);

void setPiece(U64*, int);

#endif // BOARD_H_