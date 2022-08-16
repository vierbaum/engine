#include "board.h"
#include "movegen.h"
#include "makemove.h"

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
  //char s[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -";
  char s[] = "2b5/1P6/4B3/8/4N2n/3Q4/1P1p4/4K2R w KQkq -";
  initAll();

  U64 board = 0ULL;

  //auto start = std::chrono::high_resolution_clock::now();
  //auto finish = std::chrono::high_resolution_clock::now();
  //printf("%f", std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() * 0.000000001);

  setUpBoardFromFen(s);
  //printBoard();

  moves moveList;
  generateMoves(&moveList);

  copyBoard();

    for (int move_count = 0; move_count < moveList.count; move_count++)
    {
        // init move
        int move = moveList.moves[move_count];
        
        // preserve board state
        
        // make move
        if (!makeMove(move))
            continue;
        
        printMove(move);
        printBoardSimple();
        restoreBoard()
    }
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
