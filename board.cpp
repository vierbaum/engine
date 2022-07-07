#include "board.h"

unsigned int random_state = 1804289383;

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
U64 random64() {
    U64 u1, u2, u3, u4;
    u1 = (U64)(random32()) & 0xFFFF;
    u2 = (U64)(random32()) & 0xFFFF;
    u3 = (U64)(random32()) & 0xFFFF;
    u4 = (U64)(random32()) & 0xFFFF;
    return u1 | (u2 << 16) | (u3 << 32) | (u4 << 48);
}

int transform(U64 b, U64 magic, int bits) {
#if defined(USE_32_BIT_MULTIPLICATIONS)
  return
    (unsigned)((int)b*(int)magic ^ (int)(b>>32)*(int)(magic>>32)) >> (32-bits);
#else
  return (int)((b * magic) >> (64 - bits));
#endif
}

void printBitBoard(U64 board) {
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++)
            printf("%d ", (board & (1ULL << (y * 8 + x))) != 0);
        printf("\n");
    }
    printf("\n");
}

void setPiece(U64* board, int pos) {
    *board |= (1ULL << pos);
}

void removePiece(U64* board, int pos) {
    *board ^= (1ULL << pos);
}

U64 genPawnAttacks(int pos, bool color) {
    U64 bb = 0ULL;
    U64 attacks = 0ULL;
    setPiece(&bb, pos);

    if (!color) {
        attacks |= (bb >> 8);
        if (pos % 8 != 7)
            attacks |= (bb >> 7);
        if (pos % 8 != 0)
            attacks |= (bb >> 9);
        if (pos >= A2)
            attacks |= (bb >> 16);
    } 
    else {
        attacks |= (bb << 8);
        if (pos % 8 != 7)
            attacks |= (bb << 9);
        if (pos % 8 != 0)
            attacks |= (bb << 7);
        if (pos <= H7)
            attacks |= (bb << 16);
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

U64 genKingAttacks(int pos, bool color) {
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
            if (color && (bb & (1ULL << E1)) != 0)
                attacks |= ((1ULL << C1) | (1ULL << G1));
        }
        else if (pos <= H8) {
            attacks |= (bb >> 1);
            attacks |= (bb << 1);
            attacks |= (bb << 8);
            attacks |= (bb << 7);
            attacks |= (bb << 9);
            if (!color && (bb & (1ULL << E8)) != 0)
                attacks |= ((1ULL << C8) | (1ULL << G8));
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

U64 genBishopOccupancy(int sq) {
  U64 result = 0ULL;
  int rk = sq/8, fl = sq%8, r, f;
  for(r=rk+1, f=fl+1; r<=6 && f<=6; r++, f++) result |= (1ULL << (f + r*8));
  for(r=rk+1, f=fl-1; r<=6 && f>=1; r++, f--) result |= (1ULL << (f + r*8));
  for(r=rk-1, f=fl+1; r>=1 && f<=6; r--, f++) result |= (1ULL << (f + r*8));
  for(r=rk-1, f=fl-1; r>=1 && f>=1; r--, f--) result |= (1ULL << (f + r*8));
  return result;
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

int pop1stBit(U64 *bb) {
  U64 b = *bb ^ (*bb - 1);
  unsigned int fold = (unsigned) ((b & 0xffffffff) ^ (b >> 32));
  *bb &= (*bb - 1);
  return BitTable[(fold * 0x783a9b23) >> 26];
}

U64 setOccupancy(int index, int bits, U64 m) {
  int i, j;
  U64 result = 0ULL;
  for(i = 0; i < bits; i++) {
    j = pop1stBit(&m);
    if(index & (1 << i)) result |= (1ULL << j);
  }
  return result;
}

U64 genMagicNumber() {
    return random64() & random64() & random64();
}

U64 findMagicNumber(int sq, int m, int bishop) {
  U64 mask, b[4096], a[4096], used[4096], magic;
  int i, j, k, n, fail;

  mask = bishop? genBishopOccupancy(sq) : genRookOccupancy(sq);
  //printf("%llu\n", mask);
  n = countbits(mask);

  for(i = 0; i < (1 << n); i++) {
    b[i] = setOccupancy(i, n, mask);
    a[i] = bishop? genBishopAttack(sq, b[i]) : genRookAttack(sq, b[i]);
    //printf("%llu %llu\n", a[i], b[i]);
  }
  for(k = 0; k < 100000000; k++) {
    magic = genMagicNumber();
    if(countbits((mask * magic) & 0xFF00000000000000ULL) < 6) continue;
    for(i = 0; i < 4096; i++) used[i] = 0ULL;
    for(i = 0, fail = 0; !fail && i < (1 << n); i++) {
      //j = transform(b[i], magic, m);
      j = (int)((b[i] * magic) >> (64 - m));

      //printf("%d\n", j);
      if(used[j] == 0ULL) {
        used[j] = a[i];
        //printf("%d %llu\n", i, used[j]);
      } 
      else if(used[j] != a[i]){
        fail = 1;
        //printf("%d\n", i);
      } 
    }
    if(!fail) return magic;
  }
  //printf("***Failed***\n");
  return 0ULL;
}

void initPawnAttacks() {
    for (int color = 0; color < 2; color++)
        for (int pos = 0; pos < 64; pos++)
            pawnAttacks[color][pos] =  genPawnAttacks(pos, color);
}

void initKnightAttacks() {
    for (int pos = 0; pos < 64; pos++)
        knightAttacks[pos] = genKnightAttacks(pos);
}

void initKingAttacks() {
    for (int color = 0; color < 2; color++)
        for (int pos = 0; pos < 64; pos++)
            kingAttacks[color][pos] = genKingAttacks(pos, color);
}

void initSliderAttacks() {
    for (int pos = 0; pos < 64; pos++) {
        U64 attackMask = genBishopOccupancy(pos);
        int bits = countbits(attackMask);
        int occInd = (1 << bits);

        for (int index = 0; index < occInd; index++) {
            U64 occ = setOccupancy(index, bits, attackMask);
            int magicIndex = (occ * bishopMN[pos]) >> (64 - bishopOccBits[pos]);
            bishopAttacks[pos][magicIndex] = genBishopAttack(pos, occ);
        }
    }
    for (int pos = 0; pos < 64; pos++) {
        U64 attackMask = genRookOccupancy(pos);
        int bits = countbits(attackMask);
        int occInd = (1 << bits);

        for (int index = 0; index < occInd; index++) {
            U64 occ = setOccupancy(index, bits, attackMask);
            int magicIndex = (occ * rookMN[pos]) >> (64 - rookOcckBits[pos]);
            rookAttacks[pos][magicIndex] = genRookAttack(pos, occ);
        }
    }
}

void initMagicNumbers() {
    for (int square = 0; square < 64; square++)
        //printf("%llx\n", findMagicNumber(square, rookOcckBits[square], rook));
        rookMN[square] = findMagicNumber(square, rookOcckBits[square], rook);

    for (int square = 0; square < 64; square++)
        //printf("%llx\n", findMagicNumber(square, bishopOccBits[square], bishop));
        bishopMN[square] = findMagicNumber(square, bishopOccBits[square], bishop);
}
