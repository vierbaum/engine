#include "board.h"

U64 findMagicNumber(int sq, int m, int bishop) {
  U64 mask, b[4096], a[4096], used[4096], magic;
  int i, j, k, n, fail;

  mask = bishop? genBishopOccupancy(sq) : genRookOccupancy(sq);
  n = countbits(mask);

  for(i = 0; i < (1 << n); i++) {
    b[i] = setOccupancy(i, n, mask);
    a[i] = bishop? genBishopAttack(sq, b[i]) : genRookAttack(sq, b[i]);
  }
  for(k = 0; k < 100000000; k++) {
    magic = random64() & random64() & random64();
    if(countbits((mask * magic) & 0xFF00000000000000ULL) < 6) continue;
    for(i = 0; i < 4096; i++) used[i] = 0ULL;
    for(i = 0, fail = 0; !fail && i < (1 << n); i++) {
      j = (int)((b[i] * magic) >> (64 - m));

      if(used[j] == 0ULL) {
        used[j] = a[i];
      } 
      else if(used[j] != a[i]){
        fail = 1;
      } 
    }
    if(!fail) return magic;
  }
  return 0ULL;
}

U64 genBishopAttack(int pos, U64 block) {
    // result attacks bitboard
    U64 attacks = 0ULL;
    
    int r, f;
    
    int tr = pos / 8;
    int tf = pos % 8;
    
    for (r = tr + 1, f = tf + 1; r <= 7 && f <= 7; r++, f++) {
        attacks |= (1ULL << (r * 8 + f));
        if ((1ULL << (r * 8 + f)) & block)
            break;
    }
    
    for (r = tr - 1, f = tf + 1; r >= 0 && f <= 7; r--, f++) {
        attacks |= (1ULL << (r * 8 + f));
        if ((1ULL << (r * 8 + f)) & block)
            break;
    }
    
    for (r = tr + 1, f = tf - 1; r <= 7 && f >= 0; r++, f--) {
        attacks |= (1ULL << (r * 8 + f));
        if ((1ULL << (r * 8 + f)) & block)
            break;
    }
    
    for (r = tr - 1, f = tf - 1; r >= 0 && f >= 0; r--, f--) {
        attacks |= (1ULL << (r * 8 + f));
        if ((1ULL << (r * 8 + f)) & block)
            break;
    }
    
    return attacks; 
}

U64 genBishopOccupancy(int sq) {
  U64 result = 0ULL;
  int rk = sq/8, fl = sq%8, r, f;
  for(r=rk+1, f=fl+1; r<=6 && f<=6; r++, f++) result |= (1ULL << (f + r*8));
  for(r=rk+1, f=fl-1; r<=6 && f>=1; r++, f--) result |= (1ULL << (f + r*8));
  for(r=rk-1, f=fl+1; r>=1 && f<=6; r--, f++) result |= (1ULL << (f + r*8));
  for(r=rk-1, f=fl-1; r>=1 && f>=1; r--, f--) result |= (1ULL << (f + r*8));
  return result;
}

U64 genKingAttacks(int pos) {
    U64 bb = 0ULL;
    U64 attacks = 0ULL;
    setPiece(&bb, pos);

    if ((bb & onA) != 0) {
        if (pos == A1) {
            attacks |= (bb << 1);
            attacks |= (bb >> 8);
            attacks |= (bb >> 7);
        }
        else if (pos == A8) {
            attacks |= (bb << 1);
            attacks |= (bb << 8);
            attacks |= (bb << 9);
        }
        else {
            attacks |= (bb << 1);
            attacks |= (bb >> 8);
            attacks |= (bb << 8);
            attacks |= (bb >> 7);
            attacks |= (bb << 9);
        }
    }
    else if ((bb & onH) != 0) {
        if (pos == H1) {
            attacks |= (bb >> 1);
            attacks |= (bb >> 8);
            attacks |= (bb >> 9);
        }
        else if (pos == H8) {
            attacks |= (bb >> 1);
            attacks |= (bb << 8);
            attacks |= (bb << 7);
        }
        else {
            attacks |= (bb >> 1);
            attacks |= (bb >> 8);
            attacks |= (bb >> 9);
            attacks |= (bb << 8);
            attacks |= (bb << 7);
        }
    }
    else {
        if (pos >= A1) {
            attacks |= (bb >> 1);
            attacks |= (bb << 1);
            attacks |= (bb >> 8);
            attacks |= (bb >> 7);
            attacks |= (bb >> 9);
        }
        else if (pos <= H8) {
            attacks |= (bb >> 1);
            attacks |= (bb << 1);
            attacks |= (bb << 8);
            attacks |= (bb << 7);
            attacks |= (bb << 9);
        }
        else {
            attacks |= (bb >> 1);
            attacks |= (bb << 1);
            attacks |= (bb >> 7);
            attacks |= (bb << 7);
            attacks |= (bb >> 8);
            attacks |= (bb << 8);
            attacks |= (bb << 9);
            attacks |= (bb >> 9);
        }

    }

    return attacks;
}

U64 genKnightAttacks(int pos) {
    U64 bb = 0ULL;
    U64 attacks = 0ULL;
    setPiece(&bb, pos);

    //checking if on a file 
    if ((bb & onA) != 0) {
        if (pos <= A3)
            attacks |= (bb << 17);
        if (pos <= A2)
            attacks |= (bb << 10);
        if (pos >= A6)
            attacks |= (bb >> 15);
        if (pos >= A7)
            attacks |= (bb >> 6);
    }
    else if ((bb & onB) != 0) {
        if (pos <= B3) {
            attacks |= (bb << 17);
            attacks |= (bb << 15);
        }
        if (pos <= B2)
            attacks |= (bb << 10);
        if (pos >= B6) {
            attacks |= (bb >> 15);
            attacks |= (bb >> 17);
        }
        if (pos >= B7)
            attacks |= (bb >> 6);

    }
    else if ((bb & onG) != 0) {
        if (pos <= G3) {
            attacks |= (bb << 17);
            attacks |= (bb << 15);
        }
        if (pos <= G2)
            attacks |= (bb << 6);
        if (pos >= G6) {
            attacks |= (bb >> 15);
            attacks |= (bb >> 17);
        }
        if (pos >= G7)
            attacks |= (bb >> 10);

    }
    else if ((bb & onH) != 0) {
        if (pos <= H3)
            attacks |= (bb << 15);
        if (pos <= H2)
            attacks |= (bb << 6);
        if (pos >= H6)
            attacks |= (bb >> 17);
        if (pos >= H7)
            attacks |= (bb >> 10);

    }
    else {
        if (pos <= F3) {
            attacks |= (bb << 17);
            attacks |= (bb << 15);
        }
        if (pos <= F2) {
            attacks |= (bb << 10);
            attacks |= (bb << 6);
        }
        if (pos >= C6) {
            attacks |= (bb >> 15);
            attacks |= (bb >> 17);
        }
        if (pos >= C7) {
            attacks |= (bb >> 6);
            attacks |= (bb >> 10);
        }
    }
    return attacks;
}

U64 genPawnAttacks(int pos, char color) {
    U64 bb = 0ULL;
    U64 attacks = 0ULL;
    setPiece(&bb, pos);

    if (!color) {
        if (pos % 8 != 7)
            attacks |= (bb >> 7);
        if (pos % 8 != 0)
            attacks |= (bb >> 9);
    } 
    else {
        if (pos % 8 != 7)
            attacks |= (bb << 9);
        if (pos % 8 != 0)
            attacks |= (bb << 7);
    }
    return attacks;
}

U64 genRookAttack(int pos, U64 block) {
    U64 attacks = 0ULL;
    
    int r, f;
    int tr = pos / 8;
    int tf = pos % 8;
    
    for (r = tr + 1; r <= 7; r++)
    {
        attacks |= (1ULL << (r * 8 + tf));
        if ((1ULL << (r * 8 + tf)) & block)
            break;
    }
    
    for (r = tr - 1; r >= 0; r--)
    {
        attacks |= (1ULL << (r * 8 + tf));
        if ((1ULL << (r * 8 + tf)) & block) 
            break;
    }
    
    for (f = tf + 1; f <= 7; f++)
    {
        attacks |= (1ULL << (tr * 8 + f));
        if ((1ULL << (tr * 8 + f)) & block)
            break;
    }
    
    for (f = tf - 1; f >= 0; f--)
    {
        attacks |= (1ULL << (tr * 8 + f));
        if ((1ULL << (tr * 8 + f)) & block)
            break;
    }
    
    return attacks;
}

U64 genRookOccupancy(int pos) {
    U64 attacks = 0ULL;
    int r, f;
    
    int tr = pos / 8;
    int tf = pos % 8;
    
    for (r = tr + 1; r <= 6; r++)
        attacks |= (1ULL << (r * 8 + tf));
    for (r = tr - 1; r >= 1; r--)
        attacks |= (1ULL << (r * 8 + tf));
    for (f = tf + 1; f <= 6; f++)
        attacks |= (1ULL << (tr * 8 + f));
    for (f = tf - 1; f >= 1; f--)
        attacks |= (1ULL << (tr * 8 + f));
    return attacks;
}



void initMagicNumbers() {
    for (int square = 0; square < 64; square++)
        //printf("%llx\n", findMagicNumber(square, rookOcckBits[square], rook));
        rookMN[square] = findMagicNumber(square, rookOccBits[square], rook);

    for (int square = 0; square < 64; square++)
        //printf("%llx\n", findMagicNumber(square, bishopOccBits[square], bishop));
        bishopMN[square] = findMagicNumber(square, bishopOccBits[square], bishop);
}

void initKingAttacks() {
    for (int pos = 0; pos < 64; pos++)
        kingAttacks[pos] = genKingAttacks(pos);
}

void initKnightAttacks() {
    for (int pos = 0; pos < 64; pos++)
        knightAttacks[pos] = genKnightAttacks(pos);
}

void initPawnAttacks() {
    for (int color = 0; color < 2; color++)
        for (int pos = 0; pos < 64; pos++)
            pawnAttacks[color][pos] =  genPawnAttacks(pos, color);
}

void initSliderAttacks() {
    for (int pos = 0; pos < 64; pos++) {
        bishopMasks[pos] = genBishopOccupancy(pos);
        int bits = countbits(bishopMasks[pos]);
        int occInd = (1 << bits);

        for (int index = 0; index < occInd; index++) {
            U64 occ = setOccupancy(index, bits, bishopMasks[pos]);
            int magicIndex = (occ * bishopMN[pos]) >> (64 - bishopOccBits[pos]);
            bishopAttacks[pos][magicIndex] = genBishopAttack(pos, occ);
        }
    }
    for (int pos = 0; pos < 64; pos++) {
        rookMasks[pos] = genRookOccupancy(pos);
        int bits = countbits(rookMasks[pos]);
        int occInd = (1 << bits);

        for (int index = 0; index < occInd; index++) {
            U64 occ = setOccupancy(index, bits, rookMasks[pos]);
            int magicIndex = (occ * rookMN[pos]) >> (64 - rookOccBits[pos]);
            rookAttacks[pos][magicIndex] = genRookAttack(pos, occ);
        }
    }
}

U64 random64() {
    U64 u1, u2, u3, u4;
    u1 = (U64)(random32()) & 0xFFFF;
    u2 = (U64)(random32()) & 0xFFFF;
    u3 = (U64)(random32()) & 0xFFFF;
    u4 = (U64)(random32()) & 0xFFFF;
    return u1 | (u2 << 16) | (u3 << 32) | (u4 << 48);
}