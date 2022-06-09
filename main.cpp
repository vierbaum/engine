#include <iostream>
#include "board.h"
#include "genmove.h"


int main(int argc, char *argv[]) {


  char s[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
  char* t = s;
  Board board;
  board.fromFen(t);

  setlocale(LC_CTYPE, "");
  //wchar_t star = 0x2656;
  //wprintf(L"\x1b[37;45m%lc\x1b[1;37;40m", 0x2656);

  std::vector<Board> posMoves = genMove(&board);

  board.print();

  printf("%d", posMoves.size());
  for (int i = 0; i < posMoves.size(); i++) {
    printf("%d, %d\n", i, genMove(&posMoves[i]).size());
  }
  return 0;
}

