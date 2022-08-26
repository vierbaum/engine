#include "uci.h"
#include "makemove.h"
#include "movegen.h"
#include "eval.h"
#include <stdarg.h>

int convMove(char* move) {
    char from, to, promotionflag = 0;
    from = (move[0] - 'a') + (8 - move[1] + '0') * 8;
    to = (move[2] - 'a') + (8 - move[3] + '0') * 8;
    if (move[4] != '\0')
        promotionflag = move[4];
    moves moveList;
    generateMoves(&moveList);
    for (int i = 0; i < moveList.count; i++) {
        if ((getSource(moveList.moves[i])) == from && (getTarget(moveList.moves[i])) == to && getPromoted(moveList.moves[i]) == promotionflag)
            return moveList.moves[i];
    }
    return 0;
}

void setPos(char* pos) {
    char* move;
    move = (char*) malloc(6 * sizeof(char));
    *(move + 5) = '\0';

    if(!(strncmp(pos, "startpos", 8))) {
        setUpBoardFromFen(STARTPOS);
        pos += 8;
    }

    if(!(strncmp(pos, "fen", 3))) {
        pos += 4;
        setUpBoardFromFen(pos);
    }

    if(!(strncmp(pos, " moves", 5))) {
        pos += 7;
        while(1) {
            if(*(pos + 4) == ' ' || *(pos + 4) == '\0') {
                *(move) = *pos;
                *(move + 1) = *(pos + 1);
                *(move + 2) = *(pos + 2);
                *(move + 3) = *(pos + 3);
                makeMove(convMove(move));
                pos +=5;
            }
            else
                break;
        }
    }

    free(move);
}

int think(char* command) {
    if(!strcmp(command, "isready"))
        uciOut("readyok\n");
    if(!(strncmp(command, "uci", 3))) {
        uciOut("id name madaChess\nid author vierbaum\noption name test type spin default 1 min 1 max 32\nuciok\n");
    }


    if(!strcmp(command, "register")) {
    }
    if(!(strncmp(command, "quit", 4)))
        return 0;
    if(!(strncmp(command, "print", 5)))
        printBoard();
    if(!(strncmp(command, "position", 8)))
        setPos(command + 9);
    if(!(strncmp(command, "go", 2))) {
        moves moveList;
        generateMoves(&moveList);
        printf("bestmove ");
        printMoveUCI(moveList.moves[(int) (moveList.count * 0.75)]);
    }
    if(!(strncmp(command, "eval", 4))) {
        uciOut("%d\n", eval());

    }
    return 1;
}

void uciOut(char* format, ...) {
    // varargs
    va_list argp;
    va_start(argp, format);

    FILE* fp;
    fp = fopen("log", "a");
    fputc('<', fp);
    char newLine = 0;

    while (*format != '\0') {
        if (newLine) {
            newLine = 0;
            fputc('<', fp);
        }
        if (*format == '%') {
            format++;
            if (*format == '%')
                printf("%%");
            else if (*format == 'd') {
                int numToPrint = va_arg(argp, int);
                printf("%d", numToPrint);
                fprintf(fp, "%d", numToPrint);
            }
            else if (*format == 'f') {
                double numToPrint = va_arg(argp, double);
                printf("%f", numToPrint);
                fprintf(fp, "%f", numToPrint);
            }
            else if (*format == 's') {
                char* numToPrint = va_arg(argp, char*);
                printf("%s", numToPrint);
                fprintf(fp, "%s", numToPrint);
            }
            else if (*format == 'c') {
                int numToPrint = va_arg(argp, int);
                printf("%c", numToPrint);
                fprintf(fp, "%c", numToPrint);
            }
            else
                printf("ERROR\n");
        }
        else {
            printf("%c", *format);
            fputc(*format, fp);

        }
        if (*format == '\n')
            newLine = 1;
        format++;
    }
    va_end(argp);
    fclose(fp);
}