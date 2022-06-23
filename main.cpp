#include "main.h"
#include "movegen.h"

int main(int argc, char *argv[]) {
  char s[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

  Board board;
  board.fromFen(s);
  board.print();

  printf("%d\n", board.B64to120(16));

  printf("%d\n", board.board[31]);

  std::vector<Board> moves;
  genmoves(board, &moves);
  for (int i = 0; i < moves.size(); i++) {
    moves[i].lastMove();
  }
  return 0;
}
