#include <iostream>
#include <string>
#include "board.h"

#include "search.h"

int main(int argc, char *argv[]) {


  char s[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
  //char s[] = "r1bq1rk1/1p3pp1/p1np4/2pPp2p/2P4P/2NP2P1/PP3PB1/R1Q2RK1";
  //char s[] = "r1bq1rk1/1p3pp1/p1Pp4/2p1p2p/2P4P/2NP2P1/PP3PB1/R1Q2RK1";
  //char s[] = "r1bq1rk1/5pp1/p1pp4/2p1p2p/2P4P/2NP2P1/PP3PB1/R1Q2RK1";
  char* t = s;
  Board board;
  board.fromFen(t);

  //wchar_t star = 0x2656;
  //wprintf(L"\x1b[37;45m%lc\x1b[1;37;40m", 0x2656);

  board.print();


  printf("\n%f\n", alphaBetaMax(board, -1000, 1000, 6, 1));

  board.moveHist();





  return 0;
}

