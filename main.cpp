#include "main.h"
#include "board.h"
#include "search.h"

int main(int argc, char *argv[]) {
  char s[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

  UCI uciobj;
  Board board;
  board.fromFen(s);
  board.genBitBoards();
  readEval(&board.evalllist);

  alphaBetaRoot(&uciobj, &board, -100000, 100000, 6);
  //uciobj.moves.printHist();

  //alphaBetaMax(&uciobj, &board, -100000, 100000, 2);
  uciobj.moves.printHist();
  printf("%d", uciobj.nodes);
  
  return 0;
}
