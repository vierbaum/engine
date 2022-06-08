#ifndef GENMOVE_H_
#define GENMOVE_H_
#include <vector>
#include "board.h"

std::vector<Board> genMove(Board* board) {
  std::vector<Board> moves;
  for (int x = 0; x <= 7; x++) {
    for (int y = 0; y <= 7; y++) {
      Board b = *board;
      switch (board->board[x][y]) {
      case 'K':
        for (int yc = y - 1; yc <= y + 1; yc++) {
          for (int xc = x - 1; xc <= x + 1; xc++) {
            if (xc >= 0 && yc >= 0 && xc < 8 && yc < 8 && (board->board[xc][yc] == 48 || board->board[xc][yc] > 96)) {
              printf("K: %d %d, %c, %d\n",xc, yc, board->board[xc][yc], board->board[xc][yc]);
            }

          }
        }
        // TODO castling
        break;

      case 'k':
        for (int yc = y - 1; yc <= y + 1; yc++) {
          for (int xc = x - 1; xc <= x + 1; xc++) {
            if (xc >= 0 && yc >= 0 && xc < 8 && yc < 8 && (board->board[xc][yc] == 48 || board->board[xc][yc] < 97)) {
              printf("k: %d %d, %c, %d\n", xc, yc, board->board[xc][yc], board->board[xc][yc]);
            }

          }
        }
        // TODO castling
        break;

      case 'R':
        for (int yc = y + 1; yc >= 0; yc++) {
          if (x >= 0 && yc >= 0 && x < 8 && yc < 8 && board->board[x][yc] == 48) { // looking for '0', advance
            printf("R: %d %d, %c, %d\n",x, yc, board->board[x][yc], board->board[x][yc]);
          }
          else if (x >= 0 && yc >= 0 && x < 8 && yc < 8 && board->board[x][yc] > 96) { // if black piece, add pos, dont advance
            printf("R: %d %d, %c, %d\n",x, yc, board->board[x][yc], board->board[x][yc]);
            break;
          }
          else if (board->board[x][yc] < 96) // hit own piece
            break;
        }

        for (int yc = y - 1; yc >= 0; yc--) {
          if (x >= 0 && yc >= 0 && x < 8 && yc < 8 && board->board[x][yc] == 48) { // looking for '0', advance
            printf("R: %d %d, %c, %d\n",x, yc, board->board[x][yc], board->board[x][yc]);
          }
          else if (x >= 0 && yc >= 0 && x < 8 && yc < 8 && board->board[x][yc] > 96) { // if black piece, add pos, dont advance
            printf("R: %d %d, %c, %d\n",x, yc, board->board[x][yc], board->board[x][yc]);
            break;
          }
          else if (board->board[x][yc] < 96) // hit own piece
            break;
        }

        for (int xc = x + 1; xc >= 0; xc++) {
          if (xc >= 0 && y >= 0 && xc < 8 && y < 8 && board->board[xc][y] == 48) { // looking for '0', advance
            printf("R: %d %d, %c, %d\n",xc, y, board->board[xc][y], board->board[xc][y]);
          }
          else if (xc >= 0 && y >= 0 && xc < 8 && y < 8 && board->board[xc][y] > 96) { // if black piece, add pos, dont advance
            printf("R: %d %d, %c, %d\n",xc, y, board->board[xc][y], board->board[xc][y]);
            break;
          }
          else if (board->board[xc][y] < 96) // hit own piece
            break;
        }

        for (int xc = x - 1; x >= 0; xc--) {
          if (xc >= 0 && y >= 0 && xc < 8 && y < 8 && board->board[xc][y] == 48) { // looking for '0', advance
            printf("R: %d %d, %c, %d\n",xc, y, board->board[xc][y], board->board[xc][y]);
          }
          else if (xc >= 0 && y >= 0 && xc < 8 && y < 8 && board->board[xc][y] > 96) { // if black piece, add pos, dont advance
            printf("R: %d %d, %c, %d\n",xc, y, board->board[xc][y], board->board[xc][y]);
            break;
          }
          else if (board->board[xc][y] < 96) // hit own piece
            break;
        }
        break;

      case 'r':
        for (int yc = y + 1; yc >= 0; yc++) {
          if (x >= 0 && yc >= 0 && x < 8 && yc < 8 && board->board[x][yc] == 48) { // looking for '0', advance
            printf("R: %d %d, %c, %d\n",x, yc, board->board[x][yc], board->board[x][yc]);
          }
          else if (x >= 0 && yc >= 0 && x < 8 && yc < 8 && board->board[x][yc] < 96) { // if black piece, add pos, dont advance
            printf("R: %d %d, %c, %d\n",x, yc, board->board[x][yc], board->board[x][yc]);
            break;
          }
          else if (board->board[x][yc] > 96) // hit own piece
            break;
        }

        for (int yc = y - 1; yc >= 0; yc--) {
          if (x >= 0 && yc >= 0 && x < 8 && yc < 8 && board->board[x][yc] == 48) { // looking for '0', advance
            printf("R: %d %d, %c, %d\n",x, yc, board->board[x][yc], board->board[x][yc]);
          }
          else if (x >= 0 && yc >= 0 && x < 8 && yc < 8 && board->board[x][yc] < 96) { // if black piece, add pos, dont advance
            printf("R: %d %d, %c, %d\n",x, yc, board->board[x][yc], board->board[x][yc]);
            break;
          }
          else if (board->board[x][yc] > 96) // hit own piece
            break;
        }

        for (int xc = x + 1; xc >= 0; xc++) {
          if (xc >= 0 && y >= 0 && xc < 8 && y < 8 && board->board[xc][y] == 48) { // looking for '0', advance
            printf("R: %d %d, %c, %d\n",xc, y, board->board[xc][y], board->board[xc][y]);
          }
          else if (xc >= 0 && y >= 0 && xc < 8 && y < 8 && board->board[xc][y] < 96) { // if black piece, add pos, dont advance
            printf("R: %d %d, %c, %d\n",xc, y, board->board[xc][y], board->board[xc][y]);
            break;
          }
          else if (board->board[xc][y] > 96) // hit own piece
            break;
        }

        for (int xc = x - 1; x >= 0; xc--) {
          if (xc >= 0 && y >= 0 && xc < 8 && y < 8 && board->board[xc][y] == 48) { // looking for '0', advance
            printf("R: %d %d, %c, %d\n",xc, y, board->board[xc][y], board->board[xc][y]);
          }
          else if (xc >= 0 && y >= 0 && xc < 8 && y < 8 && board->board[xc][y] < 96) { // if black piece, add pos, dont advance
            printf("R: %d %d, %c, %d\n",xc, y, board->board[xc][y], board->board[xc][y]);
            break;
          }
          else if (board->board[xc][y] > 96) // hit own piece
            break;
        }
        break;

      case 'P':
        if (board->board[x][y - 1] == 48) {
            printf("P: %d %d, %c, %d\n",x, y - 1, board->board[x][y - 1], board->board[x][y - 1]);
            if (y == 6 && board->board[x][y - 2] == 48) {
              printf("P: %d %d, %c, %d\n",x, y - 2, board->board[x][y - 2], board->board[x][y - 1]);
            }
          // TODO en passant
        }
        break;

      case 'p':
        if (board->board[x][y + 1] == 48) {
            printf("p: %d %d, %c, %d\n",x, y + 1, board->board[x][y + 1], board->board[x][y - 1]);
            if (y == 1 && board->board[x][y + 2] == 48) {
              printf("p: %d %d, %c, %d\n",x, y + 2, board->board[x][y + 2], board->board[x][y - 1]);
            }
          // TODO en passant
        }
        break;
      }
    }
  }
  return moves;
}



#endif // GENMOVE_H_
