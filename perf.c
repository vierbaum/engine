#include "perf.h"
#include "makemove.h"
#include "movegen.h"

long nodes;
long captures;

// perft driver
void perftDriver(int depth, Board* board)
{
    if (depth == 0) {
        nodes++;
        return;
    }
    
    Board cBoard;
    moves moveList;
    generateForcingMoves(&moveList, board);;
    generateMoves(&moveList, board);
    for (int moveCount = 0; moveCount < moveList.count; moveCount++) {   

        cBoard = *board;
        if (!makeMove(moveList.moves[moveCount], &cBoard))
            continue;
        
        perftDriver(depth - 1, &cBoard);
    }
}

void perftTest(int depth, Board* board)
{
    moves moveList;
    
    Board cBoard;
    generateForcingMoves(&moveList, board);;
    generateMoves(&moveList, board);
    for (int moveCount = 0; moveCount < moveList.count; moveCount++)
    {   
        cBoard = *board; 
        // make move
        if (!makeMove(moveList.moves[moveCount], &cBoard))
            continue;
        
        long cummulative_nodes = nodes;
        perftDriver(depth - 1, &cBoard);

        long old_nodes = nodes - cummulative_nodes;
        if (getPromoted(moveList.moves[moveCount]))
            printf("%s%s%c: %ld\n", SQUARER[getSource(moveList.moves[moveCount])], SQUARER[getTarget(moveList.moves[moveCount])], promotedPieces[getPromoted(moveList.moves[moveCount])],old_nodes);
        else
            printf("%s%s: %ld\n", SQUARER[getSource(moveList.moves[moveCount])], SQUARER[getTarget(moveList.moves[moveCount])],old_nodes);
    }
    
    // print results
    printf("\n    Depth: %d\n", depth);
    printf("    Nodes: %ld\n", nodes);
    printf("    Captures: %ld\n", captures);
}