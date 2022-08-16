#include "perf.h"
#include "movegen.h"

long nodes;
long captures;

// perft driver
void perftDriver(int depth)
{
    if (depth == 0) {
        nodes++;
        return;
    }
    
    moves moveList;
    generateMoves(&moveList);
    for (int moveCount = 0; moveCount < moveList.count; moveCount++) {   
        if (getCapture(moveList.moves[moveCount]))
            captures++;

        copyBoard()
        if (!makeMove(moveList.moves[moveCount]))
            continue;
        
        perftDriver(depth - 1);
        restoreBoard()
    }
}

void perftTest(int depth)
{
    moves moveList;
    
    generateMoves(&moveList);
    for (int moveCount = 0; moveCount < moveList.count; moveCount++)
    {   
        copyBoard()
        
        // make move
        if (!makeMove(moveList.moves[moveCount]))
            continue;
        
        long cummulative_nodes = nodes;
        perftDriver(depth - 1);
        long old_nodes = nodes - cummulative_nodes;
        restoreBoard()
        printf("     move: %s%s%c  nodes: %ld\n", SQUARER[getSource(moveList.moves[moveCount])], SQUARER[getTarget(moveList.moves[moveCount])], getPromoted(moveList.moves[moveCount]) ? promotedPieces[getPromoted(moveList.moves[moveCount])] : ' ',old_nodes);
    }
    
    // print results
    printf("\n    Depth: %d\n", depth);
    printf("    Nodes: %ld\n", nodes);
    printf("    Captures: %ld\n", captures);
}