#include "tetris.h"

State *init()
{
    State state = (State*)malloc(sizeof(State));
    
    state = {
        .x = CANVAS_WIDTH / 2,
        .y = 0,
        .score = 0,
        .rotate = 0,
        .fallTime = 0
    };

    for(int i=0; i<4; i++)
        state.queue[i] = rand() % 7;

    Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH];
    for(int i=0; i<CANVAS_HEIGHT; i++)
    {
        for(int j=0; j<CANVAS_WIDTH; j++)
            resetBlock(&canvas[i][j]);
    }

    return state;
}

void resetBlock(Block *block)
{
    block->color = BLACK;
    block->shape = EMPTY;
    block->current = false;
}