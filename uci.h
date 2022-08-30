#ifndef UCI_H_
#define UCI_H_

#include "board.h"
#include "makemove.h"
#include "movegen.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

static char STARTPOS[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"; // start

int convMove(char*, Board*);

void setPos(char*, Board*);

int think(char*, Board*);

void uciOut(char*, ...);


#endif
