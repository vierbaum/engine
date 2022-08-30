#include "board.h"
#include "eval.h"
#include "makemove.h"
#include "perf.h"
#include "uci.h"
#include <stdio.h>
#include "search.h"

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
int PAWNEVAL[2][3][64]; 
int KNIGHTEVAL[2][3][64]; 
int BISHOPEVAL[2][3][64]; 
int ROOKEVAL[2][3][64]; 
int QUEENEVAL[2][3][64]; 
int KINGEVAL[2][3][64]; 
char castling;
char enP = notOnBoard;
char side = white;
char stage = 0;
void initAll();


int main(int argc, char *argv[]) {
  Board gBoard;
  printf("Chess engine by vierbaum\n");
  initAll();
  //char s[] = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - "; // Kiwipete
  //char s[] = "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - "; // pos3
  //char s[] = "r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1"; // pos 4
  //char s[] = "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8  "; // pos 5
  //char s[] = "r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10 "; // pos 6


  /*
  clock_t start, stop;
  printf("START\n");
  start = clock();
  perftTest(5);
  stop = clock();

  printf("%f\n", (double)(stop - start) / CLOCKS_PER_SEC);
  */
  FILE *fp;
  think("position startpos", &gBoard);
  printf("%d\n", alphaBeta(-1000000, 1000000, 8, &gBoard));
  printMoveUCI(bMove);
  /*
  char* input;
  size_t size = 128;
  input = (char*) malloc(size * sizeof(char));
  char c, i = 0;
  while (1) {
    while ((c = getchar()) != '\n') {
      *(input + i) = c;
      i++;
    }
    *(input + i) = '\0';
    i = 0;
    fp = fopen("log", "a");
    fprintf(fp, ">%s\n", input);
    fclose(fp);
    if(!think(input)) return 0;
  }
  */
  return 0;
}

void initAll() {
  initPawnAttacks();
  initKnightAttacks();
  initKingAttacks();
  initMagicNumbers();
  initSliderAttacks();
  for (int i = 0; i <= k; i++) bitboards[i] = 0ULL;
  readEvals();
}