#ifndef BOOK_H_
#define BOOK_H_

#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define BOOKFILE "book"

char* enc256(int);

int readMove(Board*);

void writeToBook(int*, char*, int, int);

#endif