#include "tetris.h"

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

bool move(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], int original_X, int original_Y, int original_Rotate, int new_X, int new_Y, int new_Rotate, ShapeID shapeID)
{
    Shape shapeData = shapes[shapeID];
    int size = shapeData.size;

    // check if the new position is valid to place the block
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (shapeData.rotates[new_Rotate][i][j])
            {
                if (new_X + j < 0 || new_X + j >= CANVAS_WIDTH || new_Y + i < 0 || new_Y + i >= CANVAS_HEIGHT)
                    return false;
                if (!canvas[new_Y + i][new_X + j].current && canvas[new_Y + i][new_X + j].shape != EMPTY)
                    return false;
            }
        }
    }

    // remove the old position
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (shapeData.rotates[original_Rotate][i][j])
                resetBlock(&canvas[original_Y + i][original_X + j]);
        }
    }

    // move the block
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (shapeData.rotates[new_Rotate][i][j])
                setBlock(&canvas[new_Y + i][new_X + j], shapeData.color, shapeID, true);
        }
    }

    return true;
}

void printCanvas(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], State *state)
{
    printf("\033[0;0H\n");
    for (int i = 0; i < CANVAS_HEIGHT; i++)
    {
        printf("|");
        for (int j = 0; j < CANVAS_WIDTH; j++)
            printf("\033[%dm\u3000", canvas[i][j].color);
        printf("\033[0m|\n");
    }

    Shape shapeData = shapes[state->queue[1]];
    printf("\033[%d;%dHNext:", 3, CANVAS_WIDTH * 2 + 5);
    for (int i = 1; i <= 3; i++)
    {
        shapeData = shapes[state->queue[i]];
        for (int j = 0; j < 4; j++)
        {
            printf("\033[%d;%dH", i * 4 + j, CANVAS_WIDTH * 2 + 15);
            for (int k = 0; k < 4; k++)
            {
                if (j < shapeData.size && k < shapeData.size && shapeData.rotates[0][j][k])
                    printf("\x1b[%dm  ", shapeData.color);
                else
                    printf("\x1b[0m  ");
            }
        }
    }
    return;
}

int clearLine(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH])
{
    for (int i = 0; i < CANVAS_HEIGHT; i++)
    {
        for (int j = 0; j < CANVAS_WIDTH; j++)
        {
            if (canvas[i][j].current)
                canvas[i][j].current = false;
        }
    }

    int linesCleared = 0;

    for (int i = CANVAS_HEIGHT - 1; i >= 0; i--)
    {
        bool isFull = true;
        for (int j = 0; j < CANVAS_WIDTH; j++)
        {
            if (canvas[i][j].shape == EMPTY)
            {
                isFull = false;
                break;
            }
        }

        if (isFull)
        {
            linesCleared += 1;

            for (int j = i; j > 0; j--)
            {
                for (int k = 0; k < CANVAS_WIDTH; k++)
                {
                    setBlock(&canvas[j][k], canvas[j - 1][k].color, canvas[j - 1][k].shape, false);
                    resetBlock(&canvas[j - 1][k]);
                }
            }
            i++;
        }
    }

    return linesCleared;
}

void logic(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], State *state)
{
    if (ROTATE_FUNC())
    {
        int new_Rotate = (state->rotate + 1) % 4;
        if (move(canvas, state->x, state->y, state->rotate, state->x, state->y, new_Rotate, state->queue[0]))
            state->rotate = new_Rotate;
    }
    else if (LEFT_FUNC())
    {
        if (move(canvas, state->x, state->y, state->rotate, state->x - 1, state->y, state->rotate, state->queue[0]))
            state->x -= 1;
    }
    else if (RIGHT_FUNC())
    {
        if (move(canvas, state->x, state->y, state->rotate, state->x + 1, state->y, state->rotate, state->queue[0]))
            state->x += 1;
    }
    else if (DOWN_FUNC())
        state->fallTime = FALL_DELAY;
    else if (FALL_FUNC())
        state->fallTime += FALL_DELAY * CANVAS_HEIGHT;

    state->fallTime += RENDER_DELAY;

    while (state->fallTime >= FALL_DELAY)
    {
        state->fallTime -= FALL_DELAY;

        if (move(canvas, state->x, state->y, state->rotate, state->x, state->y + 1, state->rotate, state->queue[0]))
            state->y++;
        else
        {
            state->score += clearLine(canvas);

            state->x = CANVAS_WIDTH / 2;
            state->y = 0;
            state->rotate = 0;
            state->fallTime = 0;
            state->queue[0] = state->queue[1];
            state->queue[1] = state->queue[2];
            state->queue[2] = state->queue[3];
            state->queue[3] = rand() % 7;

            if (!move(canvas, state->x, state->y, state->rotate, state->x, state->y, state->rotate, state->queue[0]))
            {
                printf("\033[%d;%dH\x1b[41m GAME OVER \x1b[0m\033[%d;%dH", CANVAS_HEIGHT - 3, CANVAS_WIDTH * 2 + 5, CANVAS_HEIGHT + 5, 0);
                exit(0);
            }
        }
    }
    return;
}