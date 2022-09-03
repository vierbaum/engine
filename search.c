#include "search.h"

int alphaBetaRoot(int depthleft, Board* board) {
    nodes++;
    moves moveList;
    generateMoves(&moveList, board);
    int score;

    Board cBoard;
    int alpha = -1000000;
    for (int moveCount = 0; moveCount < moveList.count; moveCount++) {   

        cBoard = *board;
            if (!makeMove(moveList.moves[moveCount], &cBoard))
            continue;

        score = 0;
        score = -alphaBeta(-1000000, 1000000, depthleft - 1, &cBoard);
        if (score > alpha) {
            alpha = score; // alpha acts like max in MiniMax
            bMove = moveList.moves[moveCount];
            printf("BESTMOVE ");

        }
        printf("info %d %d %d ", score, nodes, alpha);
        printMoveUCI(moveList.moves[moveCount]);
    }
    printf("bestmove ");
    printMoveUCI(bMove);
    return alpha;
}

void searchThreaded(void*);