#include "main.h"
#include "board.h"
#include "movegen.h"

int main(int argc, char *argv[]) {
  char s[] = "rnbqkbnr/pppppppp/8/8/8/B7/PPPPPPPP/RNBQKBNR";

  Board board;
  board.fromFen(s);

  board.genBitBoards();
  std::vector<Board> moves;
  genmoves(board, &moves);
  for (int i = 0; i < moves.size(); i++) {
    moves[i].lastMove();
  }

  board.print();
  board.genBitBoards();
  //printBitBoard(board.bbW);
  //printBitBoard(board.bbB);
  for (int i = 21; i < 99; i++)
    printf("%c", PIECECHARS[board.board[i]]);
  return 0;
}
