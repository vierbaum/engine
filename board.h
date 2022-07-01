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
const char FILES[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
const double pieceValue[] = {1, 3, 3.25, 5, 10, 1000, -1, -3, -3.25, -5, -10, -750};
class Board {
  public:
  char board[SIZE];
  bool castlingRights[4] = {1, 1, 1, 1};
  bool color = 1;
  int enPassant;
  // TODO
  int numPieces[13] = {0};
  int pieceList[13][10];
  std::vector<std::array<int, 2>> hist;
  unsigned long long bbW;
  unsigned long long bbB;
  double evalllist[12][3][64];
  int gamephase = 0;


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
    enPassant = false;

    // castling
    if (from == E1 && to == C1 && castlingRights[0]) { // white queenside
      board[C1] = wK;
      board[D1] = wR;
      board[A1] = EMPTY;
      board[E1] = EMPTY;
      castlingRights[0] = false;
      castlingRights[1] = false;
    }
    else if (from == 25 && to == 27 && castlingRights[1]) { // white kingside
      board[G1] = wK;
      board[F1] = wR;
      board[G1] = EMPTY;
      board[E1] = EMPTY;
      castlingRights[0] = false;
      castlingRights[1] = false;
    }
    else if (from == 95 && to == 93 && castlingRights[2]) { // black queenside
      board[C8] = wK;
      board[D8] = wR;
      board[A8] = EMPTY;
      board[E8] = EMPTY;
      castlingRights[2] = false;
      castlingRights[3] = false;
    }
    else if (from == 95 && to == 97 && castlingRights[3]) { // white kingside
      board[G8] = wK;
      board[F8] = wR;
      board[G8] = EMPTY;
      board[E8] = EMPTY;
      castlingRights[2] = false;
      castlingRights[3] = false;
    } else {
      if (board[to] != EMPTY) {
        //numPieces[board[to]]--;
        board[to] = board[from];
        board[from] = EMPTY;
        genPiecelist();
      } else {
        for (int i = 0; i < numPieces[board[from]]; i++)
          if (pieceList[board[from]][i] == from) {
            pieceList[board[from]][i] = to;
            break;
          }
        board[to] = board[from];
        board[from] = EMPTY;
      }

    }

    // TODO everything
    hist.push_back({from, to});

    if (from == 21 && castlingRights[0])
      castlingRights[0] = false;
    else if (from == 28 && castlingRights[1])
      castlingRights[1] = false;
    else if (from == 91 && castlingRights[2])
      castlingRights[2] = false;
    else if (from == 98 && castlingRights[3])
      castlingRights[3] = false;
    else if (from == 25) {
      castlingRights[0] = false;
      castlingRights[1] = false;
    }
    else if (from == 95 && castlingRights[3]) {
      castlingRights[2] = false;
      castlingRights[3] = false;
    }
    genBitBoards();
    color = !color;
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

      else if (c > '1' && c < '8') {
        for (int p = x; p <= c - '0'; p++) {
          board[B64to120((7 - y) * 8 + p)] = EMPTY;
          x += 1;
        }

      }
      else if (c == '8') {
        for (int cx = 0; cx < 8; cx++) {
          board[B64to120((7 - y) * 8 + cx)] = EMPTY;
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
    if (hist.size() == 0) {
      printf("\n");
      return;
    }

    int from = B120to64(hist[hist.size() - 1][0]);
    int fromx = from % 8;
    int fromy = from / 8;
    int to = B120to64(hist[hist.size() - 1][1]);
    int tox = to % 8;
    int toy = to / 8;
    printf("%c%d%c%d\n", FILES[fromx], fromy + 1, FILES[tox], toy + 1);
  }

  void printHist() {
    for (int i = 0; i < hist.size(); i++) {
      int from = B120to64(hist[i][0]);
      int fromx = from % 8;
      int fromy = from / 8;
      int to = B120to64(hist[i][1]);
      int tox = to % 8;
      int toy = to / 8;
      printf("%c%d%c%d\n", FILES[fromx], fromy + 1, FILES[tox], toy + 1);
    }
  }

  void genPiecelist() {
    for (int i = 0; i <= bK; i++)
      numPieces[i] = 0;

    for (int pos = 0; pos < SIZE; pos++) {
      if (board[pos] <= bK) {
        pieceList[board[pos]][numPieces[board[pos]]] = pos;
        numPieces[board[pos]]++;
      }
    }
  }

  double eval() {
    double eval = 0;
    for (int i = 0; i < 64; i++) 
      if (board[B64to120(i)] != EMPTY && board[B64to120(i)] != OUTOFBOUNDS) {
        eval += evalllist[board[B64to120(i)]][gamephase][i];
      }
    return eval;
  }
};

void printBitBoard (unsigned long long);

void readEval(double(*) [12][3][64]);

void printPieceTable(double table[64]);

#endif // BOARD_H_
