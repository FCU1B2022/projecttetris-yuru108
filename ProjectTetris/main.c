#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include "tetris.h"

void hide_cursor(void);
void start(void);
void rule(void);
void setBlock(Block *block, Color color, ShapeID shape, bool current);
void resetBlock(Block *block);
void printState(State *state);
void printCanvas(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], State *state);
bool move(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], int original_X, int original_Y, int original_Rotate, int new_X, int new_Y, int new_Rotate, ShapeID shapeID);
void score_count(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], State *state);
void game_pause(void);
void hold(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], State *state);
void control(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], State *state);
void logic(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], State* state);
int clearLine(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH]);

int evaluate(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH],State test);
State* best_move(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], State state);
void auto_play(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], State *state);

int main()
{
    srand(time(NULL));
    State state = {
        .x = CANVAS_WIDTH / 2,
        .y = 0,
        .rotate = 0,
        .score = 0,
        .line = 0,
        .level = 1,
        .fallTime = 0,
        .hold_use = true,
        .hold = -1
    };

    for (int i = 0; i < 4; i++)
        state.queue[i] = rand() % 7;

    Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH];
    for (int i = 0; i < CANVAS_HEIGHT; i++)
    {
        for (int j = 0; j < CANVAS_WIDTH; j++)
            resetBlock(&canvas[i][j]);
    }
    
    hide_cursor();
    start();
    Sleep(100);
    
    system("cls");
    move(canvas, state.x, state.y, state.rotate, state.x, state.y, state.rotate, state.queue[0]);

    while(1)
    {
        if(AUTO_FUNC())
            auto_play(canvas, &state);
        else
            control(canvas, &state);
        
        printState(&state);
        printCanvas(canvas, &state);
        Sleep(100);
    }
}