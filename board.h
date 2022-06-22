#ifndef BOARD_H_
#define BOARD_H_

#include <iostream>
#include <cstring>

#define SIZE 120
#define SIZEX 10
#define SIZEY 12

#define EMPTY 48
#define OUTOFBOARDER 46

#define wP 0
#define wN 1
#define wB 2
#define wR 3
#define wQ 4
#define wK 5

#define bP 6
#define bN 7
#define bB 8
#define bR 9
#define bQ 10
#define bK 11

enum {
  A1 = 21, B1, C1, D1, E1, F1, G1, H1,
  A2 = 31, B2, C2, D2, E2, F2, G2, H2,
  A3 = 41, B3, C3, D3, E3, F3, G3, H3,
  A4 = 51, B4, C4, D4, E4, F4, G4, H4,
  A5 = 61, B5, C5, D5, E5, F5, G5, H5,
  A6 = 71, B6, C6, D6, E6, F6, G6, H6,
  A7 = 81, B7, C7, D7, E7, F7, G7, H7,
  A8 = 91, B8, C8, D8, E8, F8, G8, H8
};

class Board {
  public:
  char board[SIZE];
  bool castlingRihghts[4] = {1, 1, 1, 1};
  bool color = 1;
  int enPassant;
  // TODO
  int pieceList[13][8];

  void fromFen (char* fen) {
    for (int pos = 0; pos < SIZE; pos++) {
      board[pos] = OUTOFBOARDER;
    }

    char c;
    int pos = 0;
    for (int i = 0; i < strlen(fen); i++) {
      c = fen[i];
      if (c < 'z' && c > 'A') { // piece
        board[B64to120(pos)] = c;
        printf("%d %c\n", pos, board[B64to120(pos)]);
        pos++;
      }

      else if (c != '/')
        pos += c - '0';
    }

  }

  int B64to120 (int square) {
    int offset = 2 * SIZEX;
    int rowoffset = 1 + 2 * ((int) square / 8);
    int pos = offset + rowoffset + square;
    return pos;
  }

  int B120to64 (int square) {
    square = square - 2 * SIZEX;
    int offset = square / SIZEX;
    square = square - offset * 2;
    printf("%d\n", offset);
    return square - 1;
  }

  void print() {
    for (int i = 0; i < SIZE; i++)
      if ((i + 1) % SIZEX == 0)
        printf("%c\n", board[i]);
      else
        printf("%c", board[i]);
    printf("\n");
  }
};


#endif // BOARD_H_
