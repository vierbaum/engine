#include "main.h"
#include "board.h"

U64 pawnAttacks[2][64];
U64 knightAttacks[64];
U64 kingAttacks[2][64];
U64 rookMN[64];
U64 bishopMN[64];
U64 bishopAttacks[64][512];
U64 rookAttacks[64][4096];

int main(int argc, char *argv[]) {
  char s[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

  //initAll();
  U64 board = 0ULL;

  initAll();
  initSliderAttacks();



}

void initAll() {
  initPawnAttacks();
  initKnightAttacks();
  initKingAttacks();
  initMagicNumbers();
}
