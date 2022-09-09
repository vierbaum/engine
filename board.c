#include "board.h"

void printAttackedSquares(char cSide, Board* board) {
    int r = 0, f;
    for (; r < 8; r++)
    {
        for (f = 0; f < 8; f++)
            printf("%d ", isAttacked(r * 8 + f, board->side, board) != 0);
        printf("\n");
    }
}

void printBitBoard(U64 board) {
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++)
            printf("%d ", (board & (1ULL << (y * 8 + x))) != 0);
        printf("\n");
    }
    printf("\n");
}

void printBoard(Board* board) {
    for (int y = 7; y >= 0; y--) {
        for (int x = 0; x < 8; x++) {
            char hasPiece = 0;
            for (int piece = P; piece <= k; piece++) {
                if ((board->bitboards[piece] & (1ULL << ((7 - y) * 8 + x))) != 0) {
                    if ((x + y) % 2)
                        printf("%s%s ", BLACKPRINT, unicodePieces[piece]);
                    else
                        printf("\x1b[30;47m%s ", unicodePieces[piece]);
                    hasPiece = 1;
                    break;
                }
            }
            if (!hasPiece) {
                    if ((x + y) % 2)
                        printf("%s  ", BLACKPRINT);
                    else
                        printf("\x1b[30;47m  ");

            }
        }
        printf("\x1b[1;37;40m\n");
    }
    printf("en passant\t%d\ncastling\t%d\nside\t\t%d\n", board->enP, board->castling, board->side);
}

void printBoardSimple(Board* board) {
    for (int y = 7; y >= 0; y--) {
        for (int x = 0; x < 8; x++) {
            char hasPiece = 0;
            for (int piece = P; piece <= k; piece++) {
                if ((board->bitboards[piece] & (1ULL << ((7 - y) * 8 + x))) != 0) {
                    if ((x + y) % 2)
                        printf("%s ", unicodePieces[piece]);
                    else
                        printf("%s ", unicodePieces[piece]);
                    hasPiece = 1;
                    break;
                }
            }
            if (!hasPiece) {
                    printf(". ");

            }
        }
        printf("\n");
    }
    printf("en passant\t%d\ncastling\t%d\nside\t\t%d\n", board->enP, board->castling, board->side);

}

unsigned int random32() {
    // get current state
    unsigned int number = random_state;
    
    // XOR shift algorithm
    number ^= number << 13;
    number ^= number >> 17;
    number ^= number << 5;
    
    // update random number state
    random_state = number;
    
    // return random number
    return number;
}

void setUpBoardFromFen(char* fen, Board* board) {
    for(int a = 0; a <= k; a++) board->bitboards[a] = 0ULL;
    for(int a = 0; a <= 2; a++) board->occupancies[a] = 0ULL;
    board->castling = 0;
    board->enP = notOnBoard;
    board->stage = 0;
    board->ply = 0;
    int i = 0, s = 0, e = 0, pos = 0;
    for (;i < strlen(fen); i++) {
        if (fen[i] == ' ')
            s = 1;
        else if (e) {
            board->enP = e - 'a' + (8 - fen[i] + '0') * 8;
            e = 0;
        }
        else if (!s && fen[i] > '0' && fen[i] < '9')
            pos += fen[i] - '0';
        else if (!s && fen[i] != '/') {
            board->bitboards[charToPieces[fen[i]]] |= (1ULL << (pos));
            board->occupancies[both] |= (1ULL << pos);
            if (charToPieces[fen[i]] < p)
                board->occupancies[white] |= (1ULL << pos);
            else 
                board->occupancies[black] |= (1ULL << pos);

            pos++;
        }
        else if (s && fen[i] == 'w')
            board->side = white;
        else if (s && fen[i] == 'b')
            board->side = black;
        else if (s && fen[i] == 'K')
            board->castling += WKC;
        else if (s && fen[i] == 'Q')
            board->castling += WQC;
        else if (s && fen[i] == 'k')
            board->castling += BKC;
        else if (s && fen[i] == 'q')
            board->castling += BQC;
        else if (s && fen[i] >= 'a' && fen[i] <= 's')
            e = fen[i];
        else if (s && fen[i] == '-' && board->castling)
            board->enP = notOnBoard;
    }
}