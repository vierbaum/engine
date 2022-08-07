#include "board.h"

static inline void generateMoves() {
    char cp, np;
    U64 bb, attacks;

    if (side == white) {
        // white pawn
        bb = bitboards[P];
        while (bb) {
            cp = rem1stBit(&bb);

            np = cp - 8;
            if(!(occupancies[both] & (1ULL << np))) {
                if(np <= H8)
                    printf("PROMOTION W FROM %s TO %s\n", SQUARER[cp], SQUARER[np]);
                else
                    printf("PAWNMOVE W FROM %s TO %s\n", SQUARER[cp], SQUARER[np]);
                if(cp >= A2 && !(occupancies[both] & (1ULL << (np - 8))))
                    printf("DOUBLE PAWNMOVE W FROM %s TO %s\n", SQUARER[cp], SQUARER[np - 8]);
            }

            // capture left
            if (occupancies[black] & (1ULL << (cp - 9)) && !(onA & (1ULL << cp)))
                printf("PAWN CAPTURE W FROM %s TO %s\n", SQUARER[cp], SQUARER[cp - 9]);
            // capture right
            if (occupancies[black] & (1ULL << (cp - 7)) && !(onA & (1ULL << cp)))
                printf("PAWN CAPTURE W FROM %s TO %s\n", SQUARER[cp], SQUARER[cp - 7]);
        }

        // white bishops
        bb = bitboards[B];
        while (bb) {
            cp = rem1stBit(&bb);
            attacks = getBishopAttacks(cp, occupancies[both]);
            while (attacks) {
                np = rem1stBit(&attacks);
                if (!(occupancies[white] & (1ULL << np)))
                    printf("BISHOPS W FROM %s TO %s\n", SQUARER[cp], SQUARER[np]);
            }
        }

        // white knight
        bb = bitboards[N];
        while (bb) {
            cp = rem1stBit(&bb);
            attacks = knightAttacks[cp];
            while (attacks) {
                np = rem1stBit(&attacks);
                if (!(occupancies[white] & (1ULL << np)))
                    printf("KNIGHT W FROM %s TO %s\n", SQUARER[cp], SQUARER[np]);
            }
        }

        // white rook
        bb = bitboards[R];
        while (bb) {
            cp = rem1stBit(&bb);
            attacks = getRookAttacks(cp, occupancies[both]);
            while (attacks) {
                np = rem1stBit(&attacks);
                if (!(occupancies[white] & (1ULL << np)))
                    printf("ROOK W FROM %s TO %s\n", SQUARER[cp], SQUARER[np]);
            }
        }

        // white queen
        bb = bitboards[Q];
        while (bb) {
            cp = rem1stBit(&bb);
            attacks = getBishopAttacks(cp, occupancies[both]);
            while (attacks) {
                np = rem1stBit(&attacks);
                if (!(occupancies[white] & (1ULL << np)))
                    printf("QUEEN B FROM %s TO %s\n", SQUARER[cp], SQUARER[np]);
            }
            attacks = getRookAttacks(cp, occupancies[both]);
            while (attacks) {
                np = rem1stBit(&attacks);
                if (!(occupancies[white] & (1ULL << np)))
                    printf("QUEEN B FROM %s TO %s\n", SQUARER[cp], SQUARER[np]);
            }
        }

        // white king
        bb = bitboards[K];
        cp = rem1stBit(&bb);
        attacks = kingAttacks[cp];
        while (attacks) {
            np = rem1stBit(&attacks);
            if (!(occupancies[white] & (1ULL << np)))
                printf("KING W FROM %s TO %s\n", SQUARER[cp], SQUARER[np]);
        }
        if (castling & WKC && !getBit(occupancies[both], F1) && !getBit(occupancies[both], G1) && !isAttacked(E1, black) && !isAttacked(F1, black))
            printf("WHITE KING CASTLING, %d\n", getBit(occupancies[both], F1));
        if (castling & WQC && !getBit(occupancies[both], D1) && !getBit(occupancies[both], C1) && !isAttacked(D1, black) && !isAttacked(C1, black))
            printf("WHITE QUEEN CASTLING\n");
    }
    else {
        //black pawns
        bb = bitboards[p];
        while (bb) {
            cp = rem1stBit(&bb);

            np = cp + 8;
            if(!(occupancies[both] & (1ULL << np))) {
                if(np <= H8)
                    printf("PROMOTION B FROM %s TO %s\n", SQUARER[cp], SQUARER[np]);
                else
                    printf("PAWNMOVE B FROM %s TO %s\n", SQUARER[cp], SQUARER[np]);
                if(cp <= H7 && !(occupancies[both] & (1ULL << (np + 8))))
                    printf("DOUBLE PAWNMOVE B FROM %s TO %s\n", SQUARER[cp], SQUARER[np - 8]);
            }

            // capture left
            if (occupancies[white] & (1ULL << (cp + 7)) && !(onA & (1ULL << cp)))
                printf("PAWN CAPTURE B FROM %s TO %s\n", SQUARER[cp], SQUARER[cp - 7]);
            // capture left
            if (occupancies[white] & (1ULL << (cp + 9)) && !(onA & (1ULL << cp)))
                printf("PAWN CAPTURE B FROM %s TO %s\n", SQUARER[cp], SQUARER[cp - 9]);
        }

        // black bishops
        bb = bitboards[b];
        while (bb) {
            cp = rem1stBit(&bb);
            attacks = getBishopAttacks(cp, occupancies[both]);
            while (attacks) {
                np = rem1stBit(&attacks);
                if (!(occupancies[black] & (1ULL << np)))
                    printf("BISHOPS B FROM %s TO %s\n", SQUARER[cp], SQUARER[np]);
            }
        }

        // black knight
        bb = bitboards[n];
        while (bb) {
            cp = rem1stBit(&bb);
            attacks = knightAttacks[cp];
            while (attacks) {
                np = rem1stBit(&attacks);
                if (!(occupancies[black] & (1ULL << np)))
                    printf("KNIGHT B FROM %s TO %s\n", SQUARER[cp], SQUARER[np]);
            }
        }

        // black rook
        bb = bitboards[r];
        while (bb) {
            cp = rem1stBit(&bb);
            attacks = getRookAttacks(cp, occupancies[both]);
            while (attacks) {
                np = rem1stBit(&attacks);
                if (!(occupancies[black] & (1ULL << np)))
                    printf("ROOK B FROM %s TO %s\n", SQUARER[cp], SQUARER[np]);
            }
        }

        // black queen
        bb = bitboards[q];
        while (bb) {
            cp = rem1stBit(&bb);
            attacks = getBishopAttacks(cp, occupancies[both]);
            while (attacks) {
                np = rem1stBit(&attacks);
                if (!(occupancies[black] & (1ULL << np)))
                    printf("QUEEN B FROM %s TO %s\n", SQUARER[cp], SQUARER[np]);
            }
            attacks = getRookAttacks(cp, occupancies[both]);
            while (attacks) {
                np = rem1stBit(&attacks);
                if (!(occupancies[black] & (1ULL << np)))
                    printf("QUEEN B FROM %s TO %s\n", SQUARER[cp], SQUARER[np]);
            }
        }

        // black king
        bb = bitboards[k];
        cp = rem1stBit(&bb);
        attacks = kingAttacks[cp];
        while (attacks) {
            np = rem1stBit(&attacks);
            if (!(occupancies[black] & (1ULL << np)))
                printf("KING W FROM %s TO %s\n", SQUARER[cp], SQUARER[np]);
        }
        if (castling & BKC && !getBit(occupancies[both], F8) && !getBit(occupancies[both], G8) && !isAttacked(E8, white) && !isAttacked(F8, white))
            printf("WHITE KING CASTLING, %d\n", getBit(occupancies[both], F1));
        if (castling & BQC && !getBit(occupancies[both], D8) && !getBit(occupancies[both], C8) && !isAttacked(D8, white) && !isAttacked(C8, white))
            printf("WHITE QUEEN CASTLING\n");
    }
    return;
}
