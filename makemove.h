#ifndef MAKEMOVE_H_
#define MAKEMOVE_H_

#include "board.h"

#define SOURCESQUARE 63
#define TARGETSQUARE 4032
#define PIECE 61440
#define PROMOTED 983040
#define CAPTURE 1048576
#define DOUBLEPUSH 2097152
#define ENPASSANT 4194304
#define CASTLING 8388608

#define encMove(source, target, piece, promoted, capture, double, enpassant, castling) (source) | (target << 6) | (piece << 12) | (promoted << 16) | (capture << 20) | (double << 21) | (enpassant << 22) | (castling << 23)
#define getSource(move) (move) & (SOURCESQUARE)
#define getTarget(move) ((move) & (TARGETSQUARE)) >> 6
#define getPiece(move) ((move) & (PIECE)) >> 12
#define getPromoted(move) ((move) & (PROMOTED)) >> 16
#define getCapture(move) ((move) & (CAPTURE))
#define getDouble(move) ((move) & (DOUBLEPUSH))
#define getEnPassant(move) ((move) & (ENPASSANT))
#define getCastling(move) ((move) & (CASTLING))

#define copyBoard() U64 bitboardsC[12], occupanciesC[3]; int sideC, enpassantC, castleC; memcpy(bitboardsC, bitboards, 96); memcpy(occupanciesC, occupancies, 24); sideC = side, enpassantC = enP, castleC = castling;

// restore board state
#define restoreBoard() memcpy(bitboards, bitboardsC, 96); memcpy(occupancies, occupanciesC, 24); side = sideC, enP = enpassantC, castling = castleC;

static const char promotedPieces[] = {
    [Q] = 'q',
    [R] = 'r',
    [B] = 'b',
    [N] = 'n',
    [q] = 'q',
    [r] = 'r',
    [b] = 'b',
    [n] = 'n'
};

static const int castlingRights[64] = {
     7, 15, 15, 15,  3, 15, 15, 11,
    15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15,
    13, 15, 15, 15, 12, 15, 15, 14
};

typedef struct {
    int moves[1024];
    int count;
} moves;

static inline void addMove(moves *moveList, int move) {
    moveList->moves[moveList->count] = move;
    moveList->count++;
}


void printMove(int);

static inline int makeMove(int move, Board* board) {
    int cp, np, piece, promotion, dpush, enPas;
    cp = getSource(move);
    np = getTarget(move);
    piece = getPiece(move);
    promotion = getPromoted(move);
    dpush = getDouble(move);
    enPas = getEnPassant(move);

    Board cBoard = *board;
    removePiece(board->bitboards + piece, cp);

    if(getCapture(move)) {
        if (board->side == white)
            for (char cpiece = p; cpiece <= k; cpiece++) {
                if (getBit(board->bitboards[cpiece], np)) {
                    removePiece(board->bitboards + cpiece, np);
                    break;
                }
            }

        else for (char cpiece = P; cpiece <= K; cpiece++) {
                if (getBit(board->bitboards[cpiece], np)) {
                    removePiece(board->bitboards + cpiece, np);
                    break;
                }
        }
    }
    if(promotion) {
        setPiece(board->bitboards + promotion, np);
    }
    else
        setPiece(board->bitboards + piece, np);

    if (enPas)
        (board->side == white) ? removePiece(board->bitboards + p, np + 8) : removePiece(board->bitboards + P, np - 8);

    board->enP = notOnBoard;

    if (dpush)
        (board->side == white) ? (board->enP = np + 8) : (board->enP = np - 8);

  if (getCastling(move))
        {
            switch (np)
            {
                case (G1):
                    removePiece(board->bitboards + R, H1);
                    setPiece(board->bitboards + R, F1);
                    break;

                case (C1):
                    removePiece(board->bitboards + R, A1);
                    setPiece(board->bitboards + R, D1);
                    break;

                case (G8):
                    removePiece(board->bitboards + r, H8);
                    setPiece(board->bitboards + r, F8);
                    break;

                case (C8):
                    removePiece(board->bitboards + r, A8);
                    setPiece(board->bitboards + r, D8);
                    break;
            }
        }
        board->castling &= castlingRights[cp];
        board->castling &= castlingRights[np];

        memset(board->occupancies, 0ULL, 24);

        for (int bb_piece = P; bb_piece <= K; bb_piece++)
            board->occupancies[white] |= board->bitboards[bb_piece];

        for (int bb_piece = p; bb_piece <= k; bb_piece++)
            board->occupancies[black] |= board->bitboards[bb_piece];

        board->occupancies[both] |= board->occupancies[white];
        board->occupancies[both] |= board->occupancies[black];

        board->side ^= 1;

        if (isAttacked((board->side == white) ? ffs(board->bitboards[k]) - 1 : ffs(board->bitboards[K]) - 1, board->side, board))
        {
            // return illegal move
            *board = cBoard;
            return 0;
        }
        return 1;
}


void printMoveList(moves*);

void printMoveUCI(int);

# endif