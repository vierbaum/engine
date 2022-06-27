#include "main.h"
#include "search.h"

int main(int argc, char *argv[]) {
  char s[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

  UCI uciobj;
  Board board;
  board.fromFen(s);

  board.genBitBoards();
  //printBitBoard(board.bbW);
  //printBitBoard(board.bbB);
  alphaBetaMax(&uciobj, board, -100000, 100000, 9);
  uciobj.moves.printHist();
  return 0;
}
