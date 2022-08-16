#ifndef MOVEGEN_H_
#define MOVEGEN_H_

#include "board.h"
#include "makemove.h"

static inline void generateMoves(moves* moveList) {
    moveList->count = 0;
    char cp, np;
    U64 bb, attacks;

    if (side == white) {
        // white pawn
        bb = bitboards[P];
        while (bb) {
            cp = rem1stBit(&bb);

            np = cp - 8;
            if(!(occupancies[both] & (1ULL << np))) {
                if(np <= H8) { // promotions
                    addMove(moveList, encMove(cp, np, P, Q, 0, 0, 0, 0));
                    addMove(moveList, encMove(cp, np, P, R, 0, 0, 0, 0));
                    addMove(moveList, encMove(cp, np, P, N, 0, 0, 0, 0));
                }
                else // normal moce
                    addMove(moveList, encMove(cp, np, P, 0, 0, 0, 0, 0));
                if(cp >= A2 && !(occupancies[both] & (1ULL << (np - 8)))) // double pawn move
                    addMove(moveList, encMove(cp, (np - 8), P, 0, 0, 1, 0, 0));
            }

            // capture left
            if (occupancies[black] & (1ULL << (cp - 9)) && !(onA & (1ULL << cp))) {
                if(np <= H8) { // promotions
                    addMove(moveList, encMove(cp, (cp - 9), P, Q, 1, 0, 0, 0));
                    addMove(moveList, encMove(cp, (cp - 9), P, R, 1, 0, 0, 0));
                    addMove(moveList, encMove(cp, (cp - 9), P, N, 1, 0, 0, 0));
                }
                else
                    addMove(moveList, encMove(cp, (cp - 9), P, 0, 1, 0, 0, 0));
            }
            // capture right
            if (occupancies[black] & (1ULL << (cp - 7)) && !(onA & (1ULL << cp))) {
                if(np <= H8) { // promotions
                    addMove(moveList, encMove(cp, (cp - 7), P, Q, 1, 0, 0, 0));
                    addMove(moveList, encMove(cp, (cp - 7), P, R, 1, 0, 0, 0));
                    addMove(moveList, encMove(cp, (cp - 7), P, N, 1, 0, 0, 0));
                }
                else
                    addMove(moveList, encMove(cp, (cp - 7), P, 0, 1, 0, 0, 0));
            }

            if (enP != notOnBoard) {
                printf("%d %d\n", enP, cp);
                if (enP == cp - 7 && !(cp & onA))
                    addMove(moveList, encMove(cp, (cp - 7), P, 0, 0, 0, 1, 0));
                if (enP == cp - 9 && !(cp & onH))
                    addMove(moveList, encMove(cp, (cp - 9), P, 0, 0, 0, 1, 0));
            }
        }

        // white bishops
        bb = bitboards[B];
        while (bb) {
            cp = rem1stBit(&bb);
            attacks = getBishopAttacks(cp, occupancies[both]);
            while (attacks) {
                np = rem1stBit(&attacks);
                if (!(occupancies[both] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, B, 0, 0, 0, 0, 0));
                if ((occupancies[black] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, B, 0, 1, 0, 0, 0));
            }
        }

        // white knight
        bb = bitboards[N];
        while (bb) {
            cp = rem1stBit(&bb);
            attacks = knightAttacks[cp];
            while (attacks) {
                np = rem1stBit(&attacks);
                if (!(occupancies[both] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, N, 0, 0, 0, 0, 0));
                if ((occupancies[black] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, N, 0, 1, 0, 0, 0));
            }
        }

        // white rook
        bb = bitboards[R];
        while (bb) {
            cp = rem1stBit(&bb);
            attacks = getRookAttacks(cp, occupancies[both]);
            while (attacks) {
                np = rem1stBit(&attacks);
                if (!(occupancies[both] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, R, 0, 0, 0, 0, 0));
                if ((occupancies[black] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, R, 0, 1, 0, 0, 0));
            }
        }

        // white queen
        bb = bitboards[Q];
        while (bb) {
            cp = rem1stBit(&bb);
            attacks = getBishopAttacks(cp, occupancies[both]);
            while (attacks) {
                np = rem1stBit(&attacks);
                if (!(occupancies[both] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, Q, 0, 0, 0, 0, 0));
                if ((occupancies[black] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, Q, 0, 1, 0, 0, 0));
            }
            attacks = getRookAttacks(cp, occupancies[both]);
            while (attacks) {
                np = rem1stBit(&attacks);
                if (!(occupancies[both] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, Q, 0, 0, 0, 0, 0));
                if ((occupancies[black] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, Q, 0, 1, 0, 0, 0));
            }
        }

        // white king
        bb = bitboards[K];
        cp = rem1stBit(&bb);
        attacks = kingAttacks[cp];
        while (attacks) {
            np = rem1stBit(&attacks);
                if (!(occupancies[both] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, K, 0, 0, 0, 0, 0));
                if ((occupancies[black] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, K, 0, 1, 0, 0, 0));
        }
        // TODO
        if (castling & WKC && !getBit(occupancies[both], F1) && !getBit(occupancies[both], G1) && !isAttacked(E1, black) && !isAttacked(F1, black))
            addMove(moveList, encMove(E1, G1, K, 0, 0, 0, 0, 1));
        if (castling & WQC && !getBit(occupancies[both], D1) && !getBit(occupancies[both], C1) && !isAttacked(D1, black) && !isAttacked(C1, black))
            addMove(moveList, encMove(E1, C1, K, 0, 0, 0, 0, 1));
    }
    else {
        //black pawns
        bb = bitboards[p];
        while (bb) {
            cp = rem1stBit(&bb);

            np = cp + 8;
            if(!(occupancies[both] & (1ULL << np))) {
                if(np <= H8) {
                    addMove(moveList, encMove(cp, np, p, q, 0, 0, 0, 0));
                    addMove(moveList, encMove(cp, np, p, r, 0, 0, 0, 0));
                    addMove(moveList, encMove(cp, np, p, n, 0, 0, 0, 0));
                }
                else
                    addMove(moveList, encMove(cp, np, p, 0, 0, 0, 0, 0));
                if(cp <= H7 && !(occupancies[both] & (1ULL << (np + 8))))
                    addMove(moveList, encMove(cp, (np + 8), p, 0, 0, 1, 0, 0));
            }

            // capture left
            if (occupancies[white] & (1ULL << (cp + 7)) && !(onA & (1ULL << cp))) {
                if(np <= H8) {
                    addMove(moveList, encMove(cp, (cp + 7), p, q, 1, 0, 0, 0));
                    addMove(moveList, encMove(cp, (cp + 7), p, r, 1, 0, 0, 0));
                    addMove(moveList, encMove(cp, (cp + 7), p, n, 1, 0, 0, 0));
                }
                else
                    addMove(moveList, encMove(cp, (cp + 7), p, 0, 1, 0, 0, 0));
            }
            // capture left
            if (occupancies[white] & (1ULL << (cp + 9)) && !(onA & (1ULL << cp))) {
                if(np <= H8) {
                    addMove(moveList, encMove(cp, (cp + 9), p, q, 1, 0, 0, 0));
                    addMove(moveList, encMove(cp, (cp + 9), p, r, 1, 0, 0, 0));
                    addMove(moveList, encMove(cp, (cp + 9), p, n, 1, 0, 0, 0));
                }
                else
                    addMove(moveList, encMove(cp, (cp + 9), p, 0, 1, 0, 0, 0));
            }

            if (enP != notOnBoard) {
                if (enP == cp + 9 && !(cp & onA))
                    addMove(moveList, encMove(cp, (cp + 9), p, 0, 0, 0, 1, 0));
                if (enP == cp + 7 && !(cp & onH))
                    addMove(moveList, encMove(cp, (cp + 7), p, 0, 0, 0, 1, 0));
            }
        }

        // black bishops
        bb = bitboards[b];
        while (bb) {
            cp = rem1stBit(&bb);
            attacks = getBishopAttacks(cp, occupancies[both]);
            while (attacks) {
                np = rem1stBit(&attacks);
                if (!(occupancies[both] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, b, 0, 0, 0, 0, 0));
                if ((occupancies[white] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, b, 0, 1, 0, 0, 0));
            }
        }

        // black knight
        bb = bitboards[n];
        while (bb) {
            cp = rem1stBit(&bb);
            attacks = knightAttacks[cp];
            while (attacks) {
                np = rem1stBit(&attacks);
                if (!(occupancies[both] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, n, 0, 0, 0, 0, 0));
                if ((occupancies[white] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, n, 0, 1, 0, 0, 0));
            }
        }

        // black rook
        bb = bitboards[r];
        while (bb) {
            cp = rem1stBit(&bb);
            attacks = getRookAttacks(cp, occupancies[both]);
            while (attacks) {
                np = rem1stBit(&attacks);
                if (!(occupancies[both] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, r, 0, 0, 0, 0, 0));
                if ((occupancies[white] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, r, 0, 1, 0, 0, 0));
            }
        }

        // black queen
        bb = bitboards[q];
        while (bb) {
            cp = rem1stBit(&bb);
            attacks = getBishopAttacks(cp, occupancies[both]);
            while (attacks) {
                np = rem1stBit(&attacks);
                if (!(occupancies[both] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, q, 0, 0, 0, 0, 0));
                if ((occupancies[white] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, q, 0, 1, 0, 0, 0));
            }
            attacks = getRookAttacks(cp, occupancies[both]);
            while (attacks) {
                np = rem1stBit(&attacks);
                if (!(occupancies[both] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, q, 0, 0, 0, 0, 0));
                if ((occupancies[white] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, q, 0, 1, 0, 0, 0));
            }
        }

        // black king
        bb = bitboards[k];
        cp = rem1stBit(&bb);
        attacks = kingAttacks[cp];
        while (attacks) {
            np = rem1stBit(&attacks);
                if (!(occupancies[both] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, k, 0, 0, 0, 0, 0));
                if ((occupancies[white] & (1ULL << np)))
                    addMove(moveList, encMove(cp, np, k, 0, 1, 0, 0, 0));
        }
        if (castling & BKC && !getBit(occupancies[both], F8) && !getBit(occupancies[both], G8) && !isAttacked(E8, white) && !isAttacked(F8, white))
            addMove(moveList, encMove(E8, G8, k, 0, 0, 0, 0, 1));
        if (castling & BQC && !getBit(occupancies[both], D8) && !getBit(occupancies[both], C8) && !isAttacked(D8, white) && !isAttacked(C8, white))
            addMove(moveList, encMove(E8, C8, k, 0, 0, 0, 0, 1));
    }
    return;
}

#endif