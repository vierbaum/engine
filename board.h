#ifndef BOARD_H_
#define BOARD_H_
#include <iostream>
#include <cstring>
#include <vector>
#include <array>

#include <wchar.h>
#include <locale.h>

#define PAWNW 0x2659
#define ROOKW 0x2656
#define KNIGHTW 0x2658
#define BISHOPW 0x2657
#define QUEENW 0x2655
#define KINGW 0x265A

#define PAWNB 0x265F
#define ROOKB 0x265C
#define KNIGHTB 0x265E
#define BISHOPB 0x265D
#define QUEENB 0x265B
#define KINGB 0x265A

#define PAWN 1
#define KNIGHT 3
#define BISHOP 3.25
#define ROOK 5
#define QUEEN 9
#define KING 1000

class Board {
  public:
  double eval();
  char* fen;
  std::vector<std::array<std::array<int, 2>, 2>> moves;
  bool castlingRights[4] = {1, 1, 1, 1};
  char board[8][8];
  float pawneval[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0}, {1, 1, 1, 0.8f, 0.8f, 1.1f, 1.1f, 1.1f}, {0.75f, 0.5f, 0.5f, 0.8f, 0.8f, 1.1f, 1.1f, 1.1f}, {1.2f, 1.2f, 1.2f, 1.5f, 1.5f, 0.5f, 0.5f, 0.5f}, {1.75f, 1.75f, 1.75f, 1, 1, 0.5f, 0.5f, 0.5f}, {2, 2, 2, 1, 1, 1.75f, 1.75f, 1.75f}, {3, 3, 3, 3, 3, 3, 3, 3}, {10, 10, 10, 10, 10, 10, 10, 10}};
  bool promotion = false;
  bool color = true;

  void makeMove(int from[2], int to[2], bool promotion_=false) {
    color = !color;
    if (promotion)
      promotion = !promotion;

    std::array<std::array<int, 2>, 2> move;
    move[0] = {from[0], from[1]};
    move[1] = {to[0], to[1]};
    moves.push_back(move);

    if ((from[1] == 6 && board[from[0]][from[1]] == 'P' && to[1] == 7)) {
      board[to[0]][to[1]] = 'Q';
      board[from[0]][from[1]] = '0';
      promotion = true;
    }
    if ((from[1] == 1 && board[from[0]][from[1]] == 'p' && to[1] == 0)) {
      board[to[0]][to[1]] = 'q';
      board[from[0]][from[1]] = '0';
    }
    else if (from[0] == 4 && from[1] == 0 && board[from[0]][from[1]] == 'K' && (to[0] == 2 || to[0] == 6)) {
      if (to[0] == 2 && castlingRights[1]) {
        board[4][0] = '0';
        board[0][0] = '0';
        board[3][0] = 'R';
        board[2][0] = 'K';
      }
      if (to[0] == 6 && castlingRights[0]) {
        board[4][0] = '0';
        board[7][0] = '0';
        board[5][0] = 'R';
        board[6][0] = 'K';
      }
    }
    else if (from[0] == 4 && from[1] == 7 && board[from[0]][from[1]] == 'k' && (to[0] == 2 || to[0] == 6)) {
      if (to[0] == 2 && castlingRights[3]) {
        board[4][7] = '0';
        board[0][7] = '0';
        board[3][7] = 'r';
        board[2][7] = 'k';
      }
      if (to[0] == 6 && castlingRights[2]) {
        board[4][7] = '0';
        board[7][7] = '0';
        board[5][7] = 'r';
        board[6][7] = 'k';
      }
    }
    else {
      board[to[0]][to[1]] = board[from[0]][from[1]];
      board[from[0]][from[1]] = '0';
    }


    if (from[0] == 4) {
      if (from[1] == 0) {
        castlingRights[0] = 0;
        castlingRights[1] = 0;
        }
      else if (from[1] == 7) {
        castlingRights[2] = 0;
        castlingRights[3] = 0;
      }
    }
    else if (from[0] == 0) {
      if (from[1] == 0) {
        castlingRights[0] = 0;
        }
      else if (from[1] == 7) {
        castlingRights[2] = 0;
      }
    }
    else if (from[0] == 7) {
      if (from[1] == 0) {
        castlingRights[1] = 0;
        }
      else if (from[1] == 7) {
        castlingRights[3] = 0;
      }
    }

  }

  void moveHist() {
    for (int i = 0; i < moves.size(); i++) {
      printf("%d. %c%d%c%d\n", i + 1, moves[i][0][0] + 97, moves[i][0][1] + 1, moves[i][1][0] + 97, moves[i][1][1] + 1);
    }

  }

  void lastMove() {
    int i = moves.size() - 1;
    if (promotion)
      printf("bestmove %c%d%c%dq\n", moves[i][0][0] + 97, moves[i][0][1] + 1, moves[i][1][0] + 97, moves[i][1][1] + 1);
    else
      printf("bestmove %c%d%c%d\n", moves[i][0][0] + 97, moves[i][0][1] + 1, moves[i][1][0] + 97, moves[i][1][1] + 1);
  }

  void pMoves() {
    int i = moves.size() - 1;
    if (promotion)
      printf("%c%d%c%dq\n", moves[i][0][0] + 97, moves[i][0][1] + 1, moves[i][1][0] + 97, moves[i][1][1] + 1);
    else
      printf("%c%d%c%d\n", moves[i][0][0] + 97, moves[i][0][1] + 1, moves[i][1][0] + 97, moves[i][1][1] + 1);
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
        for (int dx = x; dx <= c - 48 + x; dx++) {
          board[dx][7 - y] = '0';
        }
        x += c - 48;
      }
      else if (c == 56) {
        for (int cx = 0; cx < 8; cx++) {
          board[cx][7 - y] = '0';
        }
      }
      else if (c != 56) {
        board[x][7 - y] = c;
        x += 1;
      }

    }
  }

  void print() {

    for (int y = 7; y >= 0; y--) {
      for (int x = 0; x < 8; x++) {
        if ((x + y) % 2 == 0) {
          if (board[x][y] == 48)
            printf("\x1b[37;45m \x1b[1;37;40m");
          else
            printf("\x1b[37;45m%c\x1b[1;37;40m", board[x][y]);
        }
        else {
          if (board[x][y] == 48)
            printf("\x1b[30;47m \x1b[1;37;40m");
          else
            printf("\x1b[30;47m%c\x1b[1;37;40m", board[x][y]);
        }
      }
      printf("\n");
    }
  }


};


#endif // BOARD_H_
