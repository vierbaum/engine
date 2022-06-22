#include <iostream>
#include <string>
#include "board.h"

#include "genmove/genmove.h"
#include "search.h"
#include<fstream>
#include <vector>
#include <chrono>

int main(int argc, char *argv[]) {

  bool color = 1;

  char s[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

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
      color = 1;
      board.color = 1;
      for (int i = 24; i < input.size(); i += 5) {
        if (input.size() > i + 4 && input[i + 4] != ' ') {
          int from[] = {input[i] - 97, input[i + 1] - 49};
          int to[] = {input[i + 2] - 97, input[i + 3] - 49};
          board.makeMove(from, to, true);
          i++;
          color = !color;
        }
        else {
          int from[] = {input[i] - 97, input[i + 1] - 49};
          int to[] = {input[i + 2] - 97, input[i + 3] - 49};
          board.makeMove(from, to);
          color = !color;
        }
      }

    }

    if (input.substr(0, 2) == "go") {
      alphaBetaRoot(board, -10000, 10000, 6, color);
    }

    if (input == "eval")
      printf("%f", board.eval());

    if (input == "print") {
      board.print();
    }

    if (input == "quit")
      done = true;
  }

  return 0;
}

