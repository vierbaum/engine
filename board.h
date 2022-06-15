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
  char* fen;
  std::vector<std::array<std::array<int, 2>, 2>> moves;
  bool castlingRights[4] = {1, 1, 1, 1};
  char board[8][8];

  void makeMove(int from[2], int to[2]) {
    //moves.push_back({{from[0], from[1]}, {to[0], to[1]}});
    std::array<std::array<int, 2>, 2> move;
    move[0] = {from[0], from[1]};
    move[1] = {to[0], to[1]};
    moves.push_back(move);
    board[to[0]][to[1]] = board[from[0]][from[1]];
    board[from[0]][from[1]] = '0';
  }

  void moveHist() {
    for (int i = 0; i < moves.size(); i++) {
      printf("%d. %c%d%c%d\n", i + 1, moves[i][0][0] + 97, moves[i][0][1] + 1, moves[i][1][0] + 97, moves[i][1][1] + 1);
    }

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
    setlocale(LC_CTYPE, "");
    //wprintf(L"%lc\n", 0x2650);

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


  double eval() {
    double eval = 0;
    for (int x = 0; x < 8; x++) {
      for (int y = 0; y < 8; y++) {
        switch (board[x][y]) {
        case 'P':
          eval += PAWN;
          break;

        case 'p':
          eval -= PAWN;
          break;

        case 'N':
          eval += KNIGHT;
          break;

        case 'n':
          eval -= KNIGHT;
          break;

        case 'B':
          eval += BISHOP;
          break;

        case 'b':
          eval -= BISHOP;
          break;

        case 'R':
          eval += ROOK;
          break;

        case 'r':
          eval -= ROOK;
          break;

        case 'Q':
          eval += QUEEN;
          break;

        case 'q':
          eval -= QUEEN;
          break;

        case 'K':
          eval += KING;
          break;

        case 'k':
          eval -= KING;
          break;

        }
      }
    }


    return eval;
  }
};


#endif // BOARD_H_
