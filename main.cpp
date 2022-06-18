#include <iostream>
#include <string>
#include "board.h"

#include "genmove.h"
#include "search.h"
#include<fstream>
#include <vector>

int main(int argc, char *argv[]) {


  char s[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
  //char s[] = "r7/kbQ2p2/1pP4p/p2R4/4P3/8/2PP1PPP/1NB1KBNR";
  //char s[] = "r1bq1rk1/1p3pp1/p1np4/2pPp2p/2P4P/2NP2P1/PP3PB1/R1Q2RK1";
  //char s[] = "r1bq1rk1/1p3pp1/p1Pp4/2p1p2p/2P4P/2NP2P1/PP3PB1/R1Q2RK1";
  //char s[] = "r1bq1rk1/5pp1/p1pp4/2p1p2p/2P4P/2NP2P1/PP3PB1/R1Q2RK1";
  Board board;
  board.fromFen(s);
  //wchar_t star = 0x2656;
  //wprintf(L"\x1b[37;45m%lc\x1b[1;37;40m", 0x2656);

  std::string input;


  bool done = false;

  while (!done) {
    std::getline(std::cin, input);

    if (input == "isready")
      printf("readyok\n");

    if (input == "uci")
      printf("id name engine\nid author nld\n\noption name test type spin default 1 min 1 max 512\nuciok\n");

    if (input.substr(0, 17) == "position startpos") {
      board.fromFen(s);
      board.castlingRights[0] = 1;
      board.castlingRights[1] = 1;
      board.castlingRights[2] = 1;
      board.castlingRights[3] = 1;
    }

    if (input.substr(0, 23) == "position startpos moves") {
      for (int i = 24; i < input.size(); i += 5) {
        if (input.size() > i + 4 && input[i + 4] != ' ') {
          int from[] = {input[i] - 97, input[i + 1] - 49};
          int to[] = {input[i + 2] - 97, input[i + 3] - 49};
          board.makeMove(from, to, true);
          i++;
        }
        else {
          int from[] = {input[i] - 97, input[i + 1] - 49};
          int to[] = {input[i + 2] - 97, input[i + 3] - 49};
          board.makeMove(from, to);
        }
      }

    }

    if (input.substr(0, 2) == "go") {
      alphaBetaMax(board, -10000, 10000, 4, 1);
    }

    if (input == "print") {
      board.print();
    }

    if (input == "quit")
      done = true;
  }

  return 0;
}

