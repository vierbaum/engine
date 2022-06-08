#include <iostream>
#include "board.h"
#include "genmove.h"

int main(int argc, char *argv[]) {


  char s[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
  char* t = s;
  Board board;
  board.fromFen(t);
  board.print();

  genMove(&board);

  return 0;
}

