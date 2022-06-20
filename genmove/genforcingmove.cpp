#include "genmove.h"

void forcingMoveDiagonal(int x, int y, std::vector<Board>* moves, Board* board, bool color) {
  int cDown = x + y; // y = -x + c => c = x + y
  int cUp = y - x; // y = x + c => c = y - x
  if (color) {
    for (int xc = x - 1; xc >= 0; xc--) { // left Down
      int yc = cDown - xc;
      if (yc >= 0 && yc < 8 && board->board[xc][yc] == 48)
        continue;
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
        continue;
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
        continue;
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
        continue;
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
      if (yc >= 0 && yc < 8 && board->board[xc][yc] == 48)
        continue;
      else if (yc >= 0 && yc < 8 && board->board[xc][yc] < 96) {
        moves->push_back(newBoard(board, x, y, xc, yc));
        break;
      }
      else
        break;
    }
    for (int xc = x - 1; xc >= 0; xc--) { // left Up
      int yc = xc + cUp;
      if (yc >= 0 && yc < 8 && board->board[xc][yc] == 48)
        continue;
      else if (yc >= 0 && yc < 8 && board->board[xc][yc] < 96) {
        moves->push_back(newBoard(board, x, y, xc, yc));
        break;
      }
      else
        break;
    }
    for (int xc = x + 1; xc < 8; xc++) { // right Down
      int yc = cDown - xc;
      if (yc >= 0 && yc < 8 && board->board[xc][yc] == 48)
        continue;
      else if (yc >= 0 && yc < 8 && board->board[xc][yc] < 96) {
        moves->push_back(newBoard(board, x, y, xc, yc));
        break;
      }
      else
        break;
    }
    for (int xc = x + 1; xc < 8; xc++) { // right Up
      int yc = xc + cUp;
      if (yc >= 0 && yc < 8 && board->board[xc][yc] == 48)
        continue;
      else if (yc >= 0 && yc < 8 && board->board[xc][yc] < 96) {
        moves->push_back(newBoard(board, x, y, xc, yc));
        break;
      }
      else
        break;
    }


  }
}

void forcingRookMove(int x, int y, std::vector<Board>* moves, Board* board, bool color) {
  if (color) {
    for (int yc = y + 1; yc < 8; yc++) {
      if (x >= 0 && yc >= 0 && x < 8 && yc < 8 && board->board[x][yc] == 48)
        continue;
      else if (x >= 0 && yc >= 0 && x < 8 && yc < 8 && board->board[x][yc] > 96) { // if black piece, add pos, dont advance
        moves->push_back(newBoard(board, x, y, x, yc));
        break;
      }
      else if (board->board[x][yc] < 96) // hit own piece
        break;
    }

    if (y != 0)
      for (int yc = y - 1; yc >= 0; yc--) {
        if (x >= 0 && yc >= 0 && x < 8 && yc < 8 && board->board[x][yc] == 48)
          continue;
        else if (x >= 0 && yc >= 0 && x < 8 && yc < 8 && board->board[x][yc] > 96) { // if black piece, add pos, dont advance
          moves->push_back(newBoard(board, x, y, x, yc));
          break;
        }
        else if (board->board[x][yc] < 96) // hit own piece
          break;
      }

    for (int xc = x + 1; xc < 8; xc++) {

      if (xc >= 0 && y >= 0 && xc < 8 && y < 8 && board->board[xc][y] == 48)
        continue;
      else if (xc >= 0 && y >= 0 && xc < 8 && y < 8 && board->board[xc][y] > 96) { // if black piece, add pos, dont advance
        moves->push_back(newBoard(board, x, y, xc, y));
        break;
      }
      else if (board->board[xc][y] < 96) // hit own piece
        break;
    }

    if (x != 0)
      for (int xc = x - 1; x >= 0; xc--) {
        if (xc >= 0 && y >= 0 && xc < 8 && y < 8 && board->board[xc][y] > 96) { // if black piece, add pos, dont advance
          moves->push_back(newBoard(board, x, y, xc, y));
          break;
        }
        else if (board->board[xc][y] < 96) // hit own piece
          break;
      }
  }
  else {
    for (int yc = y + 1; yc < 8; yc++) {
      if (x >= 0 && yc >= 0 && x < 8 && yc < 8 && board->board[x][yc] == 48)
        continue;
      else if (x >= 0 && yc >= 0 && x < 8 && yc < 8 && board->board[x][yc] < 96) { // if black piece, add pos, dont advance
        moves->push_back(newBoard(board, x, y, x, yc));
        break;
      }
      else if (board->board[x][yc] > 96) // hit own piece
        break;
    }

    if (y != 0)
      for (int yc = y - 1; yc >= 0; yc--) {
        if (x >= 0 && yc >= 0 && x < 8 && yc < 8 && board->board[x][yc] == 48)
          continue;
        else if (x >= 0 && yc >= 0 && x < 8 && yc < 8 && board->board[x][yc] < 96) { // if black piece, add pos, dont advance
          moves->push_back(newBoard(board, x, y, x, yc));
          break;
        }
        else if (board->board[x][yc] > 96) // hit own piece
          break;
      }

    for (int xc = x + 1; xc < 8; xc++) {

      if (xc >= 0 && y >= 0 && xc < 8 && y < 8 && board->board[xc][y] == 48)
        continue;
      else if (xc >= 0 && y >= 0 && xc < 8 && y < 8 && board->board[xc][y] < 96) { // if black piece, add pos, dont advance
        moves->push_back(newBoard(board, x, y, xc, y));
        break;
      }
      else if (board->board[xc][y] > 96) // hit own piece
        break;
    }

    if (x != 0)
      for (int xc = x - 1; x >= 0; xc--) {
        if (xc >= 0 && y >= 0 && xc < 8 && y < 8 && board->board[xc][y] < 96) { // if black piece, add pos, dont advance
          moves->push_back(newBoard(board, x, y, xc, y));
          break;
        }
        else if (board->board[xc][y] > 96) // hit own piece
          break;
      }
    return;
  }
}

void genForcingMoves(Board* board, bool color, std::vector<Board>* moves) {
  int nightMoves[8][2] = {{-1, 2}, {1, 2}, {2, 1}, {2, -1}, {-1, -2}, {1, -2}, {-2, -1}, {-2, 1}};


  int cDown; // y = -x + c => c = x + y
  int cUp; // y = x + c => c = y - x
  if (board->color) {
    for (int x = 0; x <= 7; x++) {
      for (int y = 0; y <= 7; y++) {
        cDown = x + y; // y = -x + c => c = x + y
        cUp = y - x; // y = x + c => c = y - x
        switch (board->board[x][y]) {
        case 'K':
          for (int yc = y - 1; yc <= y + 1; yc++) {
            for (int xc = x - 1; xc <= x + 1; xc++) {
              if (xc >= 0 && yc >= 0 && xc < 8 && yc < 8 && board->board[xc][yc] > 96) {
                moves->push_back(newBoard(board, x, y, xc, yc));
              }

            }
            break;
          }

        case 'R':
          forcingRookMove(x, y, moves, board, 1);
          break;

        case 'B':
          forcingMoveDiagonal(x, y, moves, board, 1);
          break;

        case 'Q':
          forcingRookMove(x, y, moves, board, 1);
          forcingMoveDiagonal(x, y, moves, board, 1);
          break;

        case 'P':
            if (x - 1 >= 0 && x - 1 < 8 && y + 1 >= 0 && y + 1 < 8 && board->board[x - 1][y + 1] > 96)
              moves->push_back(newBoard(board, x, y, x - 1, y + 1));

            if (x + 1 >= 0 && x + 1 < 8 && y + 1 >= 0 && y + 1 < 8 && board->board[x + 1][y + 1] > 96)
              moves->push_back(newBoard(board, x, y, x + 1, y + 1));
          break;

        case 'N':
          for(int i = 0; i < 8; i++) {
            int xc = x + nightMoves[i][0];
            int yc = y + nightMoves[i][1];
            if (xc >= 0 && yc >= 0 && xc < 8 && yc < 8 && board->board[xc][yc] > 96) {
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
          forcingRookMove(x, y, moves, board, 0);
          break;

        case 'b':
          forcingMoveDiagonal(x, y, moves, board, 0);
          break;

        case 'q':
          forcingRookMove(x, y, moves, board, 0);
          forcingMoveDiagonal(x, y, moves, board, 0);
          break;

        case 'p':
            if (x + 1 >= 0 && x + 1 < 8 && y - 1 >= 0 && y - 1 < 8 && board->board[x + 1][y - 1] < 97 && board->board[x + 1][y - 1] != 48)
              moves->push_back(newBoard(board, x, y, x + 1, y - 1));
            if (x - 1 >= 0 && x - 1 < 8 && y - 1 >= 0 && y - 1 < 8 && board->board[x - 1][y - 1] < 97 && board->board[x - 1][y - 1] != 48)
              moves->push_back(newBoard(board, x, y, x - 1, y - 1));
            // TODO en passant
          break;

        case 'n':
          for(int i = 0; i < 8; i++) {
            int xc = x + nightMoves[i][0];
            int yc = y + nightMoves[i][1];
            if (xc >= 0 && yc >= 0 && xc < 8 && yc < 8)
            if ((board->board[xc][yc] != 48 && board->board[xc][yc] < 96)) {
              moves->push_back(newBoard(board, x, y, xc, yc));
            }
          }
          break;
        }
      }
    }
  }
  return;
}
