#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include "tetris.h"

State *init(void);
void setBlock(Block *block, Color color, ShapeID shape, bool current);
void resetBlock(Block *block);
void printCanvas(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], State *state);
bool move(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], int original_X, int original_Y, int original_Rotate, int new_X, int new_Y, int new_Rotate, ShapeID shapeID);
void logic(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], State* state);
int clearLine(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH]);


int main()
{
    srand(time(NULL));
    State *state = init();

    system("cls");
    printf("\e[?25l"); // hide cursor

    move(canvas, state.x, state.y, state.rotate, state.x, state.y, state.rotate, state.queue[0]);

    while(1)
    {
        logic(canvas, &state);
        printCanvas(canvas, &state);
        Sleep(100);
    }
}