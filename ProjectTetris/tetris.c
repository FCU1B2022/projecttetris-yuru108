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

void setBlock(Block *block, Color color, ShapeID shape, bool current)
{
    block->color = color;
    block->shape = shape;
    block->current = current;
}

void resetBlock(Block *block)
{
    block->color = BLACK;
    block->shape = EMPTY;
    block->current = false;
}

void printCanvas(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], State *state)
{
    printf("\033[0;0H\n");
    for (int i = 0; i < CANVAS_HEIGHT; i++) {
        printf("|");
        for (int j = 0; j < CANVAS_WIDTH; j++) {
            printf("\033[%dm\u3000", canvas[i][j].color);
        }
        printf("\033[0m|\n");
    }
    return;
}

bool move(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], int original_X, int original_Y, int original_Rotate, int new_X, int new_Y, int new_Rotate, ShapeID shapeID)
{
    Shape shapeData = shapes[shapeID];
    int size = shapeData.size;

    // check if the new position is valid to place the block
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            if (shapeData.rotates[new_Rotate][i][j])
            {
                if(new_X + j < 0 || new_X + j >= CANVAS_WIDTH || new_Y + i < 0 || new_Y + i >= CANVAS_HEIGHT)
                    return false;
                if(!canvas[new_Y + i][new_X + j].current && canvas[new_Y + i][new_X + j].shape != ENPTY)
                    retunr false;
            }
        }
    }

    // remove the old position
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            if(shapeData.rotates[original_Rotate][i][j])
                resetBlock(&canvas[original_X + i][original_X + j]);
        }
    }

    // move the block
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            if(shapeData.rotates[new_Rotate][i][j])
                setBlock(&canvas[new_X + i][new_X + j], shapeData.color, shapeID, true);
        }
    }

    return true;
}

void logic(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], State *state)
{
    if(move(canvas, state->x, state->y, state->rotate, state->x, state->y + 1, state->rotate, state->queue[0]))
        state -> y++;
    return;
}