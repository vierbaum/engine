#include "genmove.h"

bool isInCheck(Board* board, bool color, int x, int y) {
  int nightMoves[8][2] = {{-1, 2}, {1, 2}, {2, 1}, {2, -1}, {-1, -2}, {1, -2}, {-2, -1}, {-2, 1}};
  int cDown = x + y; // y = -x + c => c = x + y
  int cUp = y - x; // y = x + c => c = y - x

  if (color) {
    for (int xc = x; xc < 7; xc++) {
      if (board->board[xc][y] == 'r' || board->board[xc][y] == 'q')
        return 1;
      else if (board->board[xc][y] != 48)
        break;
    }
    for (int xc = x; xc >= 0; xc--) {
      if (board->board[xc][y] == 'r' || board->board[xc][y] == 'q')
        return 1;
      else if (board->board[xc][y] != 48)
        break;
    }

    for (int yc = y; yc < 7; yc++) {
      if (board->board[x][yc] == 'r' || board->board[x][yc] == 'q')
        return 1;
      else if (board->board[x][yc] != 48)
        break;
    }
    for (int yc = y; yc >= 0; yc--) {
      if (board->board[x][yc] == 'r' || board->board[x][yc] == 'q')
        return 1;
      else if (board->board[x][yc] != 48)
        break;
    }
    for (int xc = x - 1; xc >= 0; xc--) { // left Down
      int yc = cDown - xc;
      if (board->board[xc][yc] == 'b' || board->board[xc][yc] == 'q')
        return 1;
      else if (board->board[xc][yc] != 48)
        break;
    }

    for (int xc = x - 1; xc >= 0; xc--) { // left Up
      int yc = xc + cUp;
      if (board->board[xc][yc] == 'b' || board->board[xc][yc] == 'q')
        return 1;
      else if (board->board[xc][yc] != 48)
        break;
    }

    for (int xc = x + 1; xc < 8; xc++) { // right Down
      int yc = cDown - xc;
      if (board->board[xc][yc] == 'b' || board->board[xc][yc] == 'q')
        return 1;
      else if (board->board[xc][yc] != 48)
        break;
    }

    for (int xc = x + 1; xc < 8; xc++) { // right Up
      int yc = xc + cUp;
      if (board->board[xc][yc] == 'b' || board->board[xc][yc] == 'q')
        return 1;
      else if (board->board[xc][yc] != 48)
        break;
    }

    for(int i = 0; i < 8; i++) {
      int xc = x + nightMoves[i][0];
      int yc = y + nightMoves[i][1];
      if (board->board[xc][yc] == 'k')
        return 1;
      else if (board->board[xc][yc] != 48)
        break;
    }
  }
  else {
    for (int xc = x; x < 7; x++) {
      if (board->board[xc][y] == 'R' || board->board[xc][y] == 'Q')
        return 1;
      else if (board->board[xc][y] != 48)
        break;
    }
    for (int xc = x; x >= 0; x--) {
      if (board->board[xc][y] == 'R' || board->board[xc][y] == 'Q')
        return 1;
      else if (board->board[xc][y] != 48)
        break;
    }

    for (int yc = y; y < 7; y++) {
      if (board->board[x][yc] == 'R' || board->board[x][yc] == 'Q')
        return 1;
      else if (board->board[x][yc] != 48)
        break;
    }
    for (int yc = y; y >= 0; y--) {
      if (board->board[x][yc] == 'R' || board->board[x][yc] == 'Q')
        return 1;
      else if (board->board[x][yc] != 48)
        break;
    }
    for (int xc = x - 1; xc >= 0; xc--) { // left Down
      int yc = cDown - xc;
      if (board->board[xc][yc] == 'R' || board->board[xc][yc] == 'Q')
        return 1;
      else if (board->board[xc][yc] != 48)
        break;
    }

    for (int xc = x - 1; xc >= 0; xc--) { // left Up
      int yc = xc + cUp;
      if (board->board[xc][yc] == 'R' || board->board[xc][yc] == 'Q')
        return 1;
      else if (board->board[xc][yc] != 48)
        break;
    }

    for (int xc = x + 1; xc < 8; xc++) { // right Down
      int yc = cDown - xc;
      if (board->board[xc][yc] == 'R' || board->board[xc][yc] == 'Q')
        return 1;
      else if (board->board[xc][yc] != 48)
        break;
    }

    for (int xc = x + 1; xc < 8; xc++) { // right Up
      int yc = xc + cUp;
      if (board->board[xc][yc] == 'R' || board->board[xc][yc] == 'Q')
        return 1;
      else if (board->board[xc][yc] != 48)
        break;
    }

    for(int i = 0; i < 8; i++) {
      int xc = x + nightMoves[i][0];
      int yc = y + nightMoves[i][1];
      if (board->board[xc][yc] == 'R' || board->board[xc][yc] == 'Q')
        return 1;
      else if (board->board[xc][yc] != 48)
        break;
    }

  }
  return 0;
}

Board newBoard(Board* board, int x, int y, int xc, int yc) {
  Board b = *board;
  int from[2] = {x, y};
  int to[2] = {xc, yc};
  b.makeMove(from, to);
  return b;
}

void moveDiagonal(int x, int y, std::vector<Board>* moves, Board* board, bool color) {
  int cDown = x + y; // y = -x + c => c = x + y
  int cUp = y - x; // y = x + c => c = y - x
  if (color) {
    for (int xc = x - 1; xc >= 0; xc--) { // left Down
      int yc = cDown - xc;
      if (yc >= 0 && yc < 8 && board->board[xc][yc] == 48)
        moves->push_back(newBoard(board, x, y, xc, yc));
      else if (yc >= 0 && yc < 8 && board->board[xc][yc] > 96) {
        moves->push_back(newBoard(board, x, y, xc, yc));
        break;
      }
      else
        break;
    }
    for (int xc = x - 1; xc >= 0; xc--) { // left Up
      int yc = xc + cUp;
      if (yc >= 0 && yc < 8 && board->board[xc][yc] == 48)
        moves->push_back(newBoard(board, x, y, xc, yc));
      else if (yc >= 0 && yc < 8 && board->board[xc][yc] > 96) {
        moves->push_back(newBoard(board, x, y, xc, yc));
        break;
      }
      else
        break;
    }
    for (int xc = x + 1; xc < 8; xc++) { // right Down
      int yc = cDown - xc;
      if (yc >= 0 && yc < 8 && board->board[xc][yc] == 48)
        moves->push_back(newBoard(board, x, y, xc, yc));
      else if (yc >= 0 && yc < 8 && board->board[xc][yc] > 96) {
        moves->push_back(newBoard(board, x, y, xc, yc));
        break;
      }
      else
        break;
    }
    for (int xc = x + 1; xc < 8; xc++) { // right Up
      int yc = xc + cUp;
      if (yc >= 0 && yc < 8 && board->board[xc][yc] == 48)
        moves->push_back(newBoard(board, x, y, xc, yc));
      else if (yc >= 0 && yc < 8 && board->board[xc][yc] > 96) {
        moves->push_back(newBoard(board, x, y, xc, yc));
        break;
      }
      else
        break;
    }
  }
  else {
    for (int xc = x - 1; xc >= 0; xc--) { // left Down
      int yc = cDown - xc;
      if (yc >= 0 && yc < 8 && (board->board[xc][yc] == 48 || board->board[xc][yc] < 96))
        moves->push_back(newBoard(board, x, y, xc, yc));
      else
        break;
    }
    for (int xc = x - 1; xc >= 0; xc--) { // left Up
      int yc = xc + cUp;
      if (yc >= 0 && yc < 8 && (board->board[xc][yc] == 48 || board->board[xc][yc] < 96))
        moves->push_back(newBoard(board, x, y, xc, yc));
      else
        break;
    }
    for (int xc = x + 1; xc < 8; xc++) { // right Down
      int yc = cDown - xc;
      if (yc >= 0 && yc < 8 && (board->board[xc][yc] == 48 || board->board[xc][yc] < 96))
        moves->push_back(newBoard(board, x, y, xc, yc));
      else
        break;
    }
    for (int xc = x + 1; xc < 8; xc++) { // left Up
      int yc = xc + cUp;
      if (yc >= 0 && yc < 8 && (board->board[xc][yc] == 48 || board->board[xc][yc] < 96))
        moves->push_back(newBoard(board, x, y, xc, yc));
      else
        break;
    }
  }
}

void rookMove(int x, int y, std::vector<Board>* moves, Board* board, bool color) {
  if (color) {
    for (int yc = y + 1; yc < 8; yc++) {
      if (x >= 0 && yc >= 0 && x < 8 && yc < 8 && board->board[x][yc] == 48) { // looking for '0', advance
        moves->push_back(newBoard(board, x, y, x, yc));
      }
      else if (x >= 0 && yc >= 0 && x < 8 && yc < 8 && board->board[x][yc] > 96) { // if black piece, add pos, dont advance
        moves->push_back(newBoard(board, x, y, x, yc));
        break;
      }
      else if (board->board[x][yc] < 96) // hit own piece
        break;
    }

    for (int yc = y - 1; yc >= 0; yc--) {
      if (x >= 0 && yc >= 0 && x < 8 && yc < 8 && board->board[x][yc] == 48) { // looking for '0', advance
        moves->push_back(newBoard(board, x, y, x, yc));
      }
      else if (x >= 0 && yc >= 0 && x < 8 && yc < 8 && board->board[x][yc] > 96) { // if black piece, add pos, dont advance
        moves->push_back(newBoard(board, x, y, x, yc));
        break;
      }
      else if (board->board[x][yc] < 96) // hit own piece
        break;
    }

    for (int xc = x + 1; xc < 8; xc++) {
      if (xc >= 0 && y >= 0 && xc < 8 && y < 8 && board->board[xc][y] == 48) { // looking for '0', advance
        moves->push_back(newBoard(board, x, y, xc, y));
      }
      else if (xc >= 0 && y >= 0 && xc < 8 && y < 8 && board->board[xc][y] > 96) { // if black piece, add pos, dont advance
        moves->push_back(newBoard(board, x, y, xc, y));
        break;
      }
      else if (board->board[xc][y] < 96) // hit own piece
        break;
    }

    if (x != 0)
      for (int xc = x - 1; x >= 0; xc--) {
        if (xc >= 0 && y >= 0 && xc < 8 && y < 8 && board->board[xc][y] == 48) { // looking for '0', advance
          moves->push_back(newBoard(board, x, y, xc, y));
        }
        else if (xc >= 0 && y >= 0 && xc < 8 && y < 8 && board->board[xc][y] > 96) { // if black piece, add pos, dont advance
          moves->push_back(newBoard(board, x, y, xc, y));
          break;
        }
        else if (board->board[xc][y] < 96) // hit own piece
          break;
      }
  }
  else {
    for (int yc = y + 1; yc < 8; yc++) {
      if (x >= 0 && yc >= 0 && x < 8 && yc < 8 && board->board[x][yc] == 48) { // looking for '0', advance
        moves->push_back(newBoard(board, x, y, x, yc));
      }
      else if (x >= 0 && yc >= 0 && x < 8 && yc < 8 && board->board[x][yc] < 96) { // if black piece, add pos, dont advance
        moves->push_back(newBoard(board, x, y, x, yc));
        break;
      }
      else if (board->board[x][yc] > 96) // hit own piece
        break;
    }

    for (int yc = y - 1; yc >= 0; yc--) {
      if (x >= 0 && yc >= 0 && x < 8 && yc < 8 && board->board[x][yc] == 48) { // looking for '0', advance
        moves->push_back(newBoard(board, x, y, x, yc));
      }
      else if (x >= 0 && yc >= 0 && x < 8 && yc < 8 && board->board[x][yc] < 96) { // if black piece, add pos, dont advance
        moves->push_back(newBoard(board, x, y, x, yc));
        break;
      }
      else if (board->board[x][yc] > 96) // hit own piece
        break;
    }

    for (int xc = x + 1; xc < 8; xc++) {
      if (xc >= 0 && y >= 0 && xc < 8 && y < 8 && board->board[xc][y] == 48) { // looking for '0', advance
        moves->push_back(newBoard(board, x, y, xc, y));
      }
      else if (xc >= 0 && y >= 0 && xc < 8 && y < 8 && board->board[xc][y] < 96) { // if black piece, add pos, dont advance
        moves->push_back(newBoard(board, x, y, xc, y));
        break;
      }
      else if (board->board[xc][y] > 96) // hit own piece
        break;
    }

    if (x != 0)
      for (int xc = x - 1; x >= 0; xc--) {
        if (xc >= 0 && y >= 0 && xc < 8 && y < 8 && board->board[xc][y] == 48) { // looking for '0', advance
          moves->push_back(newBoard(board, x, y, xc, y));
        }
        else if (xc >= 0 && y >= 0 && xc < 8 && y < 8 && board->board[xc][y] < 96) { // if black piece, add pos, dont advance
          moves->push_back(newBoard(board, x, y, xc, y));
          break;
        }
        else if (board->board[xc][y] > 96) // hit own piece
          break;
      }
  }
  return;
}


void genMove(Board* board, bool color, std::vector<Board>* moves) {
  int nightMoves[8][2] = {{-1, 2}, {1, 2}, {2, 1}, {2, -1}, {-1, -2}, {1, -2}, {-2, -1}, {-2, 1}};


  int cDown; // y = -x + c => c = x + y
  int cUp; // y = x + c => c = y - x
  if (color) {
    for (int x = 0; x <= 7; x++) {
      for (int y = 0; y <= 7; y++) {
        cDown = x + y; // y = -x + c => c = x + y
        cUp = y - x; // y = x + c => c = y - x
        switch (board->board[x][y]) {
        case 'K':
          for (int yc = y - 1; yc <= y + 1; yc++) {
            for (int xc = x - 1; xc <= x + 1; xc++) {
              if (xc >= 0 && yc >= 0 && xc < 8 && yc < 8 && (board->board[xc][yc] == 48 || board->board[xc][yc] > 96)) {
                moves->push_back(newBoard(board, x, y, xc, yc));
              }

            }
          }
          // TODO castling
          if (board->castlingRights[0] && board->board[5][0] == 48 && board->board[6][0] == 48 && !isInCheck(board, 1, 5, 0))
            moves->push_back(newBoard(board, 4, 0, 6, 0));

          if (board->castlingRights[1] && board->board[3][0] == 48 && board->board[2][0] == 48 && board->board[1][0] == 48 && !isInCheck(board, 1, 3, 0))
            moves->push_back(newBoard(board, 4, 0, 2, 0));
          break;

        case 'R':
          rookMove(x, y, moves, board, 1);
          break;

        case 'B':
          moveDiagonal(x, y, moves, board, 1);
          break;

        case 'Q':
          rookMove(x, y, moves, board, 1);
          moveDiagonal(x, y, moves, board, 1);
          break;

        case 'P':
          if (board->board[x][y + 1] == 48) {
            Board b = *board;
            int from[2] = {x, y};
            int to[2] = {x, y + 1};
            b.makeMove(from, to);
            moves->push_back(b);
            if (y == 1 && board->board[x][y + 2] == 48) {
              b = *board;
              to[1] = y + 2;
              b.makeMove(from, to);
              moves->push_back(b);
            }
            // TODO en passant
          }
            if (x - 1 >= 0 && x - 1 < 8 && y + 1 >= 0 && y + 1 < 8 && board->board[x - 1][y + 1] > 96)
              moves->push_back(newBoard(board, x, y, x - 1, y + 1));

            if (x + 1 >= 0 && x + 1 < 8 && y + 1 >= 0 && y + 1 < 8 && board->board[x + 1][y + 1] > 96)
              moves->push_back(newBoard(board, x, y, x + 1, y + 1));
          break;

        case 'N':
          for(int i = 0; i < 8; i++) {
            int xc = x + nightMoves[i][0];
            int yc = y + nightMoves[i][1];
            if (xc >= 0 && yc >= 0 && xc < 8 && yc < 8 && (board->board[xc][yc] == 48 || board->board[xc][yc] > 96)) {
              moves->push_back(newBoard(board, x, y, xc, yc));
            }
          }
          break;
        }
      }
    }
  }
  else {
    for (int x = 0; x <= 7; x++) {
      for (int y = 0; y <= 7; y++) {
        cDown = x + y; // y = -x + c => c = x + y
        cUp = y - x; // y = x + c => c = y - x
        switch (board->board[x][y]) {
        case 'k':
          for (int yc = y - 1; yc <= y + 1; yc++) {
            for (int xc = x - 1; xc <= x + 1; xc++) {
              if (xc >= 0 && yc >= 0 && xc < 8 && yc < 8 && (board->board[xc][yc] == 48 || board->board[xc][yc] < 97)) {
                moves->push_back(newBoard(board, x, y, xc, yc));
              }
            }
          }
          // TODO castling
          break;

        case 'r':
          rookMove(x, y, moves, board, 0);
          break;

        case 'b':
          moveDiagonal(x, y, moves, board, 0);
          break;

        case 'q':
          rookMove(x, y, moves, board, 0);
          moveDiagonal(x, y, moves, board, 0);
          break;

        case 'p':
          if (board->board[x][y - 1] == 48) {
            Board b = *board;
            int from[2] = {x, y};
            int to[2] = {x, y - 1};
            b.makeMove(from, to);
            moves->push_back(b);
            if (y == 6 && board->board[x][y - 2] == 48) {
              b = *board;
              to[1] = y - 2;
              b.makeMove(from, to);
              moves->push_back(b);
            }
            if (x + 1 >= 0 && x + 1 < 8 && y - 1 >= 0 && y - 1 < 8 && board->board[x + 1][y - 1] < 97 && board->board[x + 1][y - 1] != 48)
              moves->push_back(newBoard(board, x, y, x + 1, y - 1));
            if (x - 1 >= 0 && x - 1 < 8 && y - 1 >= 0 && y - 1 < 8 && board->board[x - 1][y - 1] < 97 && board->board[x - 1][y - 1] != 48)
              moves->push_back(newBoard(board, x, y, x - 1, y - 1));
            // TODO en passant
          }
          break;

        case 'n':
          for(int i = 0; i < 8; i++) {
            int xc = x + nightMoves[i][0];
            int yc = y + nightMoves[i][1];
            if (xc >= 0 && yc >= 0 && xc < 8 && yc < 8)
            if ((board->board[xc][yc] == 48 || board->board[xc][yc] < 96)) {
              moves->push_back(newBoard(board, x, y, xc, yc));
            }
          }
          break;
        }
      }
    }
  }
}
