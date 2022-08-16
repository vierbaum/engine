#include "perf.h"

U64 pawnAttacks[2][64];
U64 knightAttacks[64];
U64 kingAttacks[64];
U64 rookMN[64];
U64 bishopMN[64];
U64 bishopAttacks[64][512];
U64 rookAttacks[64][4096];
U64 bishopMasks[64];
U64 rookMasks[64];
U64 bitboards[12];
U64 occupancies[3];
char castling;
char enP = notOnBoard;
char side = white;
void initAll();


int main(int argc, char *argv[]) {
  char s[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -";

  initAll();
  U64 board = 0ULL;
  setUpBoardFromFen(s);

  clock_t start, stop;
  printf("START\n");
  start = clock();
  perftTest(6);
  stop = clock();

  printf("%f\n", (double)(stop - start) / CLOCKS_PER_SEC);

  return 0;
}

void initAll() {
  initPawnAttacks();
  initKnightAttacks();
  initKingAttacks();
  initMagicNumbers();
  initSliderAttacks();
  for (int i = 0; i <= k; i++) bitboards[i] = 0ULL;
}
