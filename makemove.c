#include "makemove.h"

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

void printMoveUCI(int move) {
    printf("%s%s%c\n", SQUARER[getSource(move)], SQUARER[getTarget(move)], promotedPieces[getPromoted(move)]);
}
