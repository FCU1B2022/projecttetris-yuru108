#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include "tetris.h"

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