#ifndef MOVEGEN_H_
#define MOVEGEN_H_

#include "board.h"
#include "makemove.h"

static inline void generateMoves(moves* moveList, Board* board) {
    moveList->count = 0;
    char cp, np;
    U64 bb, attacks;

    if (board->side == white) {

        // white bishops
        bb = board->bitboards[B];
        while (bb) {
            cp = rem1stBit(&bb);
            attacks = getBishopAttacks(cp, board->occupancies[both]);
            while (attacks) {
                np = rem1stBit(&attacks);
                if (!(board->occupancies[both] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, B, 0, 0, 0, 0, 0));
                if ((board->occupancies[black] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, B, 0, 1, 0, 0, 0));
            }
        }

        // white knight
        bb = board->bitboards[N];
        while (bb) {
            cp = rem1stBit(&bb);
            attacks = knightAttacks[cp];
            while (attacks) {
                np = rem1stBit(&attacks);
                if (!(board->occupancies[both] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, N, 0, 0, 0, 0, 0));
                if ((board->occupancies[black] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, N, 0, 1, 0, 0, 0));
            }
        }

        // white pawn
        bb = board->bitboards[P];
        while (bb) {
            cp = rem1stBit(&bb);

            np = cp - 8;
            if(!(board->occupancies[both] & (1ULL << np))) {
                if(np <= H8) { // promotions
                    addMove(moveList, encMove(cp, np, P, Q, 0, 0, 0, 0));
                    addMove(moveList, encMove(cp, np, P, R, 0, 0, 0, 0));
                    addMove(moveList, encMove(cp, np, P, N, 0, 0, 0, 0));
                    addMove(moveList, encMove(cp, np, P, B, 0, 0, 0, 0));
                }
                else // normal moce
                    addMove(moveList, encMove(cp, np, P, 0, 0, 0, 0, 0));

                if(cp >= A2 && !(board->occupancies[both] & (1ULL << (np - 8)))) // double pawn move
                    addMove(moveList, encMove(cp, (np - 8), P, 0, 0, 1, 0, 0));
            }

            // capture left
            if (board->occupancies[black] & (1ULL << (cp - 9)) && !(onA & (1ULL << cp))) {
                if(np <= H8) { // promotions
                    addMove(moveList, encMove(cp, (cp - 9), P, Q, 1, 0, 0, 0));
                    addMove(moveList, encMove(cp, (cp - 9), P, R, 1, 0, 0, 0));
                    addMove(moveList, encMove(cp, (cp - 9), P, N, 1, 0, 0, 0));
                    addMove(moveList, encMove(cp, (cp - 9), P, B, 1, 0, 0, 0));
                }
                else
                    addMove(moveList, encMove(cp, (cp - 9), P, 0, 1, 0, 0, 0));
            }
            // capture right
            if (board->occupancies[black] & (1ULL << (cp - 7)) && !(onH & (1ULL << cp))) {
                if(np <= H8) { // promotions
                    addMove(moveList, encMove(cp, (cp - 7), P, Q, 1, 0, 0, 0));
                    addMove(moveList, encMove(cp, (cp - 7), P, R, 1, 0, 0, 0));
                    addMove(moveList, encMove(cp, (cp - 7), P, N, 1, 0, 0, 0));
                    addMove(moveList, encMove(cp, (cp - 7), P, B, 1, 0, 0, 0));
                }
                else
                    addMove(moveList, encMove(cp, (cp - 7), P, 0, 1, 0, 0, 0));
            }

            if (board->enP != notOnBoard) {
                if (board->enP == cp - 7 && !((1ULL << cp) & onH))
                    addMove(moveList, encMove(cp, (cp - 7), P, 0, 0, 0, 1, 0));
                if (board->enP == cp - 9 && !((1ULL << cp) & onA)) {
                    addMove(moveList, encMove(cp, (cp - 9), P, 0, 0, 0, 1, 0));
                }
            }
        }

        // white rook
        bb = board->bitboards[R];
        while (bb) {
            cp = rem1stBit(&bb);
            attacks = getRookAttacks(cp, board->occupancies[both]);
            while (attacks) {
                np = rem1stBit(&attacks);
                if (!(board->occupancies[both] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, R, 0, 0, 0, 0, 0));
                if ((board->occupancies[black] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, R, 0, 1, 0, 0, 0));
            }
        }

        // white queen
        bb = board->bitboards[Q];
        while (bb) {
            cp = rem1stBit(&bb);
            attacks = getBishopAttacks(cp, board->occupancies[both]);
            while (attacks) {
                np = rem1stBit(&attacks);
                if (!(board->occupancies[both] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, Q, 0, 0, 0, 0, 0));
                if ((board->occupancies[black] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, Q, 0, 1, 0, 0, 0));
            }
            attacks = getRookAttacks(cp, board->occupancies[both]);
            while (attacks) {
                np = rem1stBit(&attacks);
                if (!(board->occupancies[both] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, Q, 0, 0, 0, 0, 0));
                if ((board->occupancies[black] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, Q, 0, 1, 0, 0, 0));
            }
        }

        // white king
        bb = board->bitboards[K];
        cp = rem1stBit(&bb);
        attacks = kingAttacks[cp];
        while (attacks) {
            np = rem1stBit(&attacks);
                if (!(board->occupancies[both] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, K, 0, 0, 0, 0, 0));
                if ((board->occupancies[black] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, K, 0, 1, 0, 0, 0));
        }
        // TODO
        if (board->castling & WKC && !getBit(board->occupancies[both], F1) && !getBit(board->occupancies[both], G1) && !isAttacked(E1, black, board) && !isAttacked(F1, black, board))
            addMove(moveList, encMove(E1, G1, K, 0, 0, 0, 0, 1));
        if (board->castling & WQC && !getBit(board->occupancies[both], D1) && !getBit(board->occupancies[both], B1) && !getBit(board->occupancies[both], C1) && !isAttacked(E1, black, board) && !isAttacked(D1, black, board) && !isAttacked(C1, black, board))
            addMove(moveList, encMove(E1, C1, K, 0, 0, 0, 0, 1));
    }
    else {

        // black bishops
        bb = board->bitboards[b];
        while (bb) {
            cp = rem1stBit(&bb);
            attacks = getBishopAttacks(cp, board->occupancies[both]);
            while (attacks) {
                np = rem1stBit(&attacks);
                if (!(board->occupancies[both] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, b, 0, 0, 0, 0, 0));
                if ((board->occupancies[white] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, b, 0, 1, 0, 0, 0));
            }
        }

        // black knight
        bb = board->bitboards[n];
        while (bb) {
            cp = rem1stBit(&bb);
            attacks = knightAttacks[cp];
            while (attacks) {
                np = rem1stBit(&attacks);
                if (!(board->occupancies[both] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, n, 0, 0, 0, 0, 0));
                if ((board->occupancies[white] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, n, 0, 1, 0, 0, 0));
            }
        }

        //black pawns
        bb = board->bitboards[p];
        while (bb) {
            cp = rem1stBit(&bb);

            np = cp + 8;
            if(!(board->occupancies[both] & (1ULL << np))) {
                if(np >= A1) {
                    addMove(moveList, encMove(cp, np, p, q, 0, 0, 0, 0));
                    addMove(moveList, encMove(cp, np, p, r, 0, 0, 0, 0));
                    addMove(moveList, encMove(cp, np, p, n, 0, 0, 0, 0));
                    addMove(moveList, encMove(cp, np, p, b, 0, 0, 0, 0));
                }
                else
                    addMove(moveList, encMove(cp, np, p, 0, 0, 0, 0, 0));
                if(cp <= H7 && !(board->occupancies[both] & (1ULL << (np + 8))))
                    addMove(moveList, encMove(cp, (np + 8), p, 0, 0, 1, 0, 0));
            }

            // capture left
            if (board->occupancies[white] & (1ULL << (cp + 7)) && !(onA & (1ULL << cp))) {
                if(np >= A1) {
                    addMove(moveList, encMove(cp, (cp + 7), p, q, 1, 0, 0, 0));
                    addMove(moveList, encMove(cp, (cp + 7), p, r, 1, 0, 0, 0));
                    addMove(moveList, encMove(cp, (cp + 7), p, n, 1, 0, 0, 0));
                    addMove(moveList, encMove(cp, (cp + 7), p, b, 1, 0, 0, 0));
                }
                else
                    addMove(moveList, encMove(cp, (cp + 7), p, 0, 1, 0, 0, 0));
            }
            // capture left
            if (board->occupancies[white] & (1ULL << (cp + 9)) && !(onH & (1ULL << cp))) {
                if(np >= A1) {
                    addMove(moveList, encMove(cp, (cp + 9), p, q, 1, 0, 0, 0));
                    addMove(moveList, encMove(cp, (cp + 9), p, r, 1, 0, 0, 0));
                    addMove(moveList, encMove(cp, (cp + 9), p, n, 1, 0, 0, 0));
                    addMove(moveList, encMove(cp, (cp + 9), p, b, 1, 0, 0, 0));
                }
                else
                    addMove(moveList, encMove(cp, (cp + 9), p, 0, 1, 0, 0, 0));
            }

            if (board->enP != notOnBoard) {
                if (board->enP == cp + 9 && !((1ULL << cp) & onH))
                    addMove(moveList, encMove(cp, (cp + 9), p, 0, 0, 0, 1, 0));
                if (board->enP == cp + 7 && !((1ULL << cp) & onA))
                    addMove(moveList, encMove(cp, (cp + 7), p, 0, 0, 0, 1, 0));
            }
        }

        // black rook
        bb = board->bitboards[r];
        while (bb) {
            cp = rem1stBit(&bb);
            attacks = getRookAttacks(cp, board->occupancies[both]);
            while (attacks) {
                np = rem1stBit(&attacks);
                if (!(board->occupancies[both] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, r, 0, 0, 0, 0, 0));
                if ((board->occupancies[white] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, r, 0, 1, 0, 0, 0));
            }
        }

        // black queen
        bb = board->bitboards[q];
        while (bb) {
            cp = rem1stBit(&bb);
            attacks = getBishopAttacks(cp, board->occupancies[both]);
            while (attacks) {
                np = rem1stBit(&attacks);
                if (!(board->occupancies[both] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, q, 0, 0, 0, 0, 0));
                if ((board->occupancies[white] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, q, 0, 1, 0, 0, 0));
            }
            attacks = getRookAttacks(cp, board->occupancies[both]);
            while (attacks) {
                np = rem1stBit(&attacks);
                if (!(board->occupancies[both] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, q, 0, 0, 0, 0, 0));
                if ((board->occupancies[white] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, q, 0, 1, 0, 0, 0));
            }
        }

        // black king
        bb = board->bitboards[k];
        cp = rem1stBit(&bb);
        attacks = kingAttacks[cp];
        while (attacks) {
            np = rem1stBit(&attacks);
                if (!(board->occupancies[both] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, k, 0, 0, 0, 0, 0));
                if ((board->occupancies[white] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, k, 0, 1, 0, 0, 0));
        }
        if (board->castling & BKC && !getBit(board->occupancies[both], F8) && !getBit(board->occupancies[both], G8) && !isAttacked(E8, white, board) && !isAttacked(F8, white, board))
            addMove(moveList, encMove(E8, G8, k, 0, 0, 0, 0, 1));
        if (board->castling & BQC && !getBit(board->occupancies[both], D8) && !getBit(board->occupancies[both], B8) && !getBit(board->occupancies[both], C8) && !isAttacked(D8, white, board) && !isAttacked(E8, white, board) && !isAttacked(C8, white, board))
            addMove(moveList, encMove(E8, C8, k, 0, 0, 0, 0, 1));
    }
    return;
}

static inline void generateForcingMoves(moves* moveList, Board* board) {
    moveList->count = 0;
    char cp, np;
    U64 bb, attacks;

    if (board->side == white) {
        // white pawn
        bb = board->bitboards[P];
        while (bb) {
            cp = rem1stBit(&bb);
            // capture left
            if (board->occupancies[black] & (1ULL << (cp - 9)) && !(onA & (1ULL << cp))) {
                if(np <= H8) { // promotions
                    addMove(moveList, encMove(cp, (cp - 9), P, Q, 1, 0, 0, 0));
                    addMove(moveList, encMove(cp, (cp - 9), P, R, 1, 0, 0, 0));
                    addMove(moveList, encMove(cp, (cp - 9), P, N, 1, 0, 0, 0));
                    addMove(moveList, encMove(cp, (cp - 9), P, B, 1, 0, 0, 0));
                }
                else
                    addMove(moveList, encMove(cp, (cp - 9), P, 0, 1, 0, 0, 0));
            }
            // capture right
            if (board->occupancies[black] & (1ULL << (cp - 7)) && !(onH & (1ULL << cp))) {
                if(np <= H8) { // promotions
                    addMove(moveList, encMove(cp, (cp - 7), P, Q, 1, 0, 0, 0));
                    addMove(moveList, encMove(cp, (cp - 7), P, R, 1, 0, 0, 0));
                    addMove(moveList, encMove(cp, (cp - 7), P, N, 1, 0, 0, 0));
                    addMove(moveList, encMove(cp, (cp - 7), P, B, 1, 0, 0, 0));
                }
                else
                    addMove(moveList, encMove(cp, (cp - 7), P, 0, 1, 0, 0, 0));
            }

            if (board->enP != notOnBoard) {
                if (board->enP == cp - 7 && !((1ULL << cp) & onH))
                    addMove(moveList, encMove(cp, (cp - 7), P, 0, 0, 0, 1, 0));
                if (board->enP == cp - 9 && !((1ULL << cp) & onA)) {
                    addMove(moveList, encMove(cp, (cp - 9), P, 0, 0, 0, 1, 0));
                }
            }
        }

        // white bishops
        bb = board->bitboards[B];
        while (bb) {
            cp = rem1stBit(&bb);
            attacks = getBishopAttacks(cp, board->occupancies[both]);
            while (attacks) {
                np = rem1stBit(&attacks);
                if ((board->occupancies[black] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, B, 0, 1, 0, 0, 0));
            }
        }

        // white knight
        bb = board->bitboards[N];
        while (bb) {
            cp = rem1stBit(&bb);
            attacks = knightAttacks[cp];
            while (attacks) {
                np = rem1stBit(&attacks);
                if ((board->occupancies[black] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, N, 0, 1, 0, 0, 0));
            }
        }

        // white rook
        bb = board->bitboards[R];
        while (bb) {
            cp = rem1stBit(&bb);
            attacks = getRookAttacks(cp, board->occupancies[both]);
            while (attacks) {
                np = rem1stBit(&attacks);
                if ((board->occupancies[black] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, R, 0, 1, 0, 0, 0));
            }
        }

        // white queen
        bb = board->bitboards[Q];
        while (bb) {
            cp = rem1stBit(&bb);
            attacks = getBishopAttacks(cp, board->occupancies[both]);
            while (attacks) {
                np = rem1stBit(&attacks);
                if ((board->occupancies[black] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, Q, 0, 1, 0, 0, 0));
            }
            attacks = getRookAttacks(cp, board->occupancies[both]);
            while (attacks) {
                np = rem1stBit(&attacks);
                if ((board->occupancies[black] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, Q, 0, 1, 0, 0, 0));
            }
        }

        // white king
        bb = board->bitboards[K];
        cp = rem1stBit(&bb);
        attacks = kingAttacks[cp];
        while (attacks) {
            np = rem1stBit(&attacks);
                if ((board->occupancies[black] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, K, 0, 1, 0, 0, 0));
        }
    }
    else {
        //black pawns
        bb = board->bitboards[p];
        while (bb) {
            cp = rem1stBit(&bb);
            // capture left
            if (board->occupancies[white] & (1ULL << (cp + 7)) && !(onA & (1ULL << cp))) {
                if(np >= A1) {
                    addMove(moveList, encMove(cp, (cp + 7), p, q, 1, 0, 0, 0));
                    addMove(moveList, encMove(cp, (cp + 7), p, r, 1, 0, 0, 0));
                    addMove(moveList, encMove(cp, (cp + 7), p, n, 1, 0, 0, 0));
                    addMove(moveList, encMove(cp, (cp + 7), p, b, 1, 0, 0, 0));
                }
                else
                    addMove(moveList, encMove(cp, (cp + 7), p, 0, 1, 0, 0, 0));
            }
            // capture left
            if (board->occupancies[white] & (1ULL << (cp + 9)) && !(onH & (1ULL << cp))) {
                if(np >= A1) {
                    addMove(moveList, encMove(cp, (cp + 9), p, q, 1, 0, 0, 0));
                    addMove(moveList, encMove(cp, (cp + 9), p, r, 1, 0, 0, 0));
                    addMove(moveList, encMove(cp, (cp + 9), p, n, 1, 0, 0, 0));
                    addMove(moveList, encMove(cp, (cp + 9), p, b, 1, 0, 0, 0));
                }
                else
                    addMove(moveList, encMove(cp, (cp + 9), p, 0, 1, 0, 0, 0));
            }

            if (board->enP != notOnBoard) {
                if (board->enP == cp + 9 && !((1ULL << cp) & onH))
                    addMove(moveList, encMove(cp, (cp + 9), p, 0, 0, 0, 1, 0));
                if (board->enP == cp + 7 && !((1ULL << cp) & onA))
                    addMove(moveList, encMove(cp, (cp + 7), p, 0, 0, 0, 1, 0));
            }
        }

        // black bishops
        bb = board->bitboards[b];
        while (bb) {
            cp = rem1stBit(&bb);
            attacks = getBishopAttacks(cp, board->occupancies[both]);
            while (attacks) {
                np = rem1stBit(&attacks);
                if ((board->occupancies[white] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, b, 0, 1, 0, 0, 0));
            }
        }

        // black knight
        bb = board->bitboards[n];
        while (bb) {
            cp = rem1stBit(&bb);
            attacks = knightAttacks[cp];
            while (attacks) {
                np = rem1stBit(&attacks);
                if ((board->occupancies[white] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, n, 0, 1, 0, 0, 0));
            }
        }

        // black rook
        bb = board->bitboards[r];
        while (bb) {
            cp = rem1stBit(&bb);
            attacks = getRookAttacks(cp, board->occupancies[both]);
            while (attacks) {
                np = rem1stBit(&attacks);
                if ((board->occupancies[white] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, r, 0, 1, 0, 0, 0));
            }
        }

        // black queen
        bb = board->bitboards[q];
        while (bb) {
            cp = rem1stBit(&bb);
            attacks = getBishopAttacks(cp, board->occupancies[both]);
            while (attacks) {
                np = rem1stBit(&attacks);
                if ((board->occupancies[white] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, q, 0, 1, 0, 0, 0));
            }
            attacks = getRookAttacks(cp, board->occupancies[both]);
            while (attacks) {
                np = rem1stBit(&attacks);
                if ((board->occupancies[white] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, q, 0, 1, 0, 0, 0));
            }
        }

        // black king
        bb = board->bitboards[k];
        cp = rem1stBit(&bb);
        attacks = kingAttacks[cp];
        while (attacks) {
            np = rem1stBit(&attacks);
                if ((board->occupancies[white] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, k, 0, 1, 0, 0, 0));
        }
    }
    return;
}
#endif