#include "makemove.h"
#include "board.h"

void printMove(int move) {
    printf("\nSOURCE TARGET PIEC PROM C D E C\n");
    for (int i = 0; i < 24; i++) {
        printf("%d", (move & (1U << i)) != 0);
        if (i == 5 || i == 11 || i == 15 || i >= 19)
            printf(" ");
    }
    printf("\n  %s     %s    %c\n", SQUARER[getSource(move)], SQUARER[getTarget(move)], PIECER[getPiece(move)]);
    return;
}

void printMoveList(moves* list){
    for (int i = 0; i < list->count; i++) {
        printf("%d ", i);
        printMove(list->moves[i]);
    }
}

void printMoveUCI(int move, char* p) {
    //printf("%s%s%c\n", SQUARER[getSource(move)], SQUARER[getTarget(move)], promotedPieces[getPromoted(move)]);
    *p = SQUARER[getSource(move)][0];
    *(p + 1) = SQUARER[getSource(move)][1];
    *(p + 2) = SQUARER[getTarget(move)][0];
    *(p + 3) = SQUARER[getTarget(move)][1];
    *(p + 4) = promotedPieces[getPromoted(move)];
    *(p + 5) = '\0';
}
