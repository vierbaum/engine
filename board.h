#ifndef BOARD_H_
#define BOARD_H_

#include <iostream>
#include <cstring>
#include <vector>
#include <array>

#define SIZE 120
#define SIZEX 10
#define SIZEY 12

#define EMPTY 12
#define OUTOFBOUNDS 13

/*
#define wP 'P'
#define wN 'N'
#define wB 'B'
#define wR 'R'
#define wQ 'Q'
#define wK 'K'

#define bP 'p'
#define bN 'n'
#define bB 'b'
#define bR 'r'
#define bQ 'q'
#define bK 'k'
*/
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

const char PIECECHARS[] = {'P', 'N', 'B', 'R', 'Q', 'K', 'p', 'n', 'b', 'r', 'q', 'k', '-', '.'};
const char FILES[] = {'A', 'B', 'C', 'C', 'E', 'F', 'G', 'H'};

class Board {
  public:
  char board[SIZE];
  bool castlingRihghts[4] = {1, 1, 1, 1};
  bool color = 1;
  int enPassant;
  // TODO
  int numPieces[13] = {0};
  int pieceList[13][10];
  std::vector<std::array<int, 2>> hist;
  unsigned long long bbW;
  unsigned long long bbB;


  void genBitBoards () {
    bbW = 0;
    bbB = 0;
    for (int i = 0; i < SIZE; i++) {
      if (board[i] <= wK)
        bbW |= (1ULL << B120to64(i));
      else if (board[i] > wK && board[i] < EMPTY)
        bbB |= (1ULL << B120to64(i));

    }
  }

  void makeMove120(int from, int to) {
    board[to] = board[from];
    board[to] = EMPTY;
    // TODO everything
    hist.push_back({from, to});
  }

  void fromFen (char* fen) {
    for (int pos = 0; pos < SIZE; pos++) {
      board[pos] = OUTOFBOUNDS;
    }

    int x = 0;
    int y = 0;
    char c;
    for (int i = 0; i < strlen(fen); i++) {
      c = fen[i];
      if (c == '/') {
        x = 0;
        y++;
      }
      else if (c == '1') {
        board[B64to120((7 - y) * 8 + x)] = EMPTY;
        x++;
      }

      else if (c > '1' && c < '9') {
        for (int p = x; p < c - '0'; p++) {
          board[B64to120((7 - y) * 8 + p)] = EMPTY;
          x += 1;
        }

      }
      else {
        int pos = (7 - y) * 8 + x;
        //printf("%d, %c, %d, %d, %d\n", pos, c, i, x, y);
        switch (c) {
        case 'P':
          board[B64to120(pos)] = wP;
          pieceList[wP][numPieces[wP]] = B64to120(pos);
          numPieces[wP]++;
          break;
        case 'N':
          board[B64to120(pos)] = wN;
          pieceList[wN][numPieces[wN]] = B64to120(pos);
          numPieces[wN]++;
          break;
        case 'B':
          board[B64to120(pos)] = wB;
          pieceList[wB][numPieces[wB]] = B64to120(pos);
          numPieces[wB]++;
          break;
        case 'R':
          board[B64to120(pos)] = wR;
          pieceList[wR][numPieces[wR]] = B64to120(pos);
          numPieces[wR]++;
          break;
        case 'Q':
          board[B64to120(pos)] = wQ;
          pieceList[wQ][numPieces[wQ]] = B64to120(pos);
          numPieces[wQ]++;
          break;
        case 'K':
          board[B64to120(pos)] = wK;
          pieceList[wK][numPieces[wK]] = B64to120(pos);
          numPieces[wK]++;
          break;
        case 'p':
          board[B64to120(pos)] = bP;
          pieceList[bP][numPieces[bP]] = B64to120(pos);
          numPieces[bP]++;
          break;
        case 'n':
          board[B64to120(pos)] = bN;
          pieceList[bN][numPieces[bN]] = B64to120(pos);
          numPieces[bN]++;
          break;
        case 'b':
          board[B64to120(pos)] = bB;
          pieceList[bB][numPieces[bB]] = B64to120(pos);
          numPieces[bB]++;
          break;
        case 'r':
          board[B64to120(pos)] = bR;
          pieceList[bR][numPieces[bR]] = B64to120(pos);
          numPieces[bR]++;
          break;
        case 'q':
          board[B64to120(pos)] = bQ;
          pieceList[bQ][numPieces[bQ]] = B64to120(pos);
          numPieces[bQ]++;
          break;
        case 'k':
          board[B64to120(pos)] = bK;
          pieceList[bK][numPieces[bK]] = B64to120(pos);
          numPieces[bK]++;
          break;
        }
        x += 1;
      }
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
    return square - 1;
  }


  void print() {
    for (int y = SIZEY - 1; y >= 0; y--) {
      for (int x = 0; x < SIZEX; x++)
          printf("%c", PIECECHARS[board[y * SIZEX + x]]);
      printf("\n");
    }
  }

  void lastMove() {
    int from = B120to64(hist[hist.size() - 1][0]);
    int fromx = from % 8;
    int fromy = from / 8;
    int to = B120to64(hist[hist.size() - 1][1]);
    int tox = to % 8;
    int toy = to / 8;
    printf("%c%d %c%d\n", FILES[fromx], fromy + 1, FILES[tox], toy + 1);
  }
};

void printBitBoard (unsigned long long);

#endif // BOARD_H_
