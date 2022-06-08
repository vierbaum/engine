#ifndef BOARD_H_
#define BOARD_H_
#include <iostream>
#include <cstring>
#include <vector>

class Board {
  public:
  char* fen;
  //std::vector<int[2][2]> moves;
  bool castlingRights[4] = {1, 1, 1, 1};
  char board[8][8];

  void makeMove(int from[2], int to[2]) {
    //moves.push_back({from, to});
    board[to[0]][to[1]] = board[from[0]][from[1]];
  }

  void fromFen(char* fen) {
    int x = 0;
    int y = 0;
    char c;

    for(int i = 0; i <= strlen(fen); i++) {
      c = fen[i];
      if (c == '/') {
        y += 1;
        x = 0;
      }
      else if (48 < c && c < 56) {
          printf("HERE %d %d\n", c, c -48);
        for (int dx = x; dx <= c - 48 + x; dx++) {
          board[dx][y] = '0';
        }
        x += c - 48;
      }
      else if (c == 56) {
        for (int cx = 0; cx < 8; cx++) {
          board[cx][y] = '0';
        }
      }
      else if (c != 56) {
        board[x][y] = c;
        x += 1;
      }

    }
  }

  void print() {
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
        printf("%c", board[x][y]);
        }
        printf("\n");
    }
  }
};


#endif // BOARD_H_
