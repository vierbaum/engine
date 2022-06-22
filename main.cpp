#include "main.h"

int main(int argc, char *argv[]) {
  char s[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

  Board board;
  board.fromFen(s);
  board.print();

  printf("%d", board.B64to120(16));
  return 0;
}
