#include "search.h"
#include <pthread.h>
#include <stdlib.h>

int alphaBetaRoot(int depthleft, Board* board) {
    nodes = 0;
    int currMove = 0;
    int alpha = -1000000;
    int beta = -alpha;
    int legM = 0;
    board->ply = 0;

    moves moveList;
    Data data;
    data.currMove = &currMove;
    data.moveList = &moveList;
    data.depthleft = depthleft;
    data.board = board;
    data.alpha = &alpha;
    data.beta = &beta;
    data.legalMoves = &legM;
    generateForcingMoves(&moveList, board);
    generateMoves(&moveList, board);

    pthread_t tid[4];
    for (int i = 0; i <= 3; i++)
        pthread_create(tid + i, NULL, searchThreaded, (void *)&data);

    for (int i = 0; i <= 3; i++)
        pthread_join(tid[i], NULL);
    char* c = (char*) malloc(6);
    printMoveUCI(bMove, c);
    printf("bestmove %s\n NODES %d\n", c, nodes);
    free(c);
    return bMove;
}

void* searchThreaded(void* dataP) {
    Data* data = (Data*) dataP;

    Board cBoard;
    int move;
    int score;
    char* c = (char*) malloc(6);
    loop:
        if( *data->currMove >= data->moveList->count) {
            return 0;
            free(c);
        }
        cBoard = *data->board;
        move = data->moveList->moves[*data->currMove];
        (*data->currMove)++;
        printMoveUCI(move, c);
        printf("info %s\n", c);

        if (!makeMove(move, &cBoard))
            goto loop;
        (*data->legalMoves)++;
        score = -alphaBeta(-*data->beta, -*data->alpha, data->depthleft - 1, &cBoard, 1);
        printf("info %s %d\n", c, score);
        if (score > *data->alpha) {
            *data->alpha = score; // alpha acts like max in MiniMax
            bMove = move;
        }
    goto loop;
}