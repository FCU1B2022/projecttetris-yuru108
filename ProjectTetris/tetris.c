#include "tetris.h"

Shape shapes[7] = {
	{.shape = I,
	 .color = CYAN,
	 .size = 4,
	 .rotates =
		 {
			 {{0, 0, 0, 0},
			  {1, 1, 1, 1},
			  {0, 0, 0, 0},
			  {0, 0, 0, 0}},
			 {{0, 0, 1, 0},
			  {0, 0, 1, 0},
			  {0, 0, 1, 0},
			  {0, 0, 1, 0}},
			 {{0, 0, 0, 0},
			  {0, 0, 0, 0},
			  {1, 1, 1, 1},
			  {0, 0, 0, 0}},
			 {{0, 1, 0, 0},
			  {0, 1, 0, 0},
			  {0, 1, 0, 0},
			  {0, 1, 0, 0}}}},
	{.shape = J,
	 .color = BLUE,
	 .size = 3,
	 .rotates =
		 {
			 {{1, 0, 0},
			  {1, 1, 1},
			  {0, 0, 0}},
			 {{0, 1, 1},
			  {0, 1, 0},
			  {0, 1, 0}},
			 {{0, 0, 0},
			  {1, 1, 1},
			  {0, 0, 1}},
			 {{0, 1, 0},
			  {0, 1, 0},
			  {1, 1, 0}}}},
	{.shape = L,
	 .color = YELLOW,
	 .size = 3,
	 .rotates =
		 {
			 {{0, 0, 1},
			  {1, 1, 1},
			  {0, 0, 0}},
			 {{0, 1, 0},
			  {0, 1, 0},
			  {0, 1, 1}},
			 {{0, 0, 0},
			  {1, 1, 1},
			  {1, 0, 0}},
			 {{1, 1, 0},
			  {0, 1, 0},
			  {0, 1, 0}}}},
	{.shape = O,
	 .color = WHITE,
	 .size = 2,
	 .rotates =
		 {
			 {{1, 1},
			  {1, 1}},
			 {{1, 1},
			  {1, 1}},
			 {{1, 1},
			  {1, 1}},
			 {{1, 1},
			  {1, 1}}}},
	{.shape = S,
	 .color = GREEN,
	 .size = 3,
	 .rotates =
		 {
			 {{0, 1, 1},
			  {1, 1, 0},
			  {0, 0, 0}},
			 {{0, 1, 0},
			  {0, 1, 1},
			  {0, 0, 1}},
			 {{0, 0, 0},
			  {0, 1, 1},
			  {1, 1, 0}},
			 {{1, 0, 0},
			  {1, 1, 0},
			  {0, 1, 0}}}},
	{.shape = T,
	 .color = PURPLE,
	 .size = 3,
	 .rotates =
		 {
			 {{0, 1, 0},
			  {1, 1, 1},
			  {0, 0, 0}},

			 {{0, 1, 0},
			  {0, 1, 1},
			  {0, 1, 0}},
			 {{0, 0, 0},
			  {1, 1, 1},
			  {0, 1, 0}},
			 {{0, 1, 0},
			  {1, 1, 0},
			  {0, 1, 0}}}},
	{.shape = Z,
	 .color = RED,
	 .size = 3,
	 .rotates =
		 {
			 {{1, 1, 0},
			  {0, 1, 1},
			  {0, 0, 0}},
			 {{0, 0, 1},
			  {0, 1, 1},
			  {0, 1, 0}},
			 {{0, 0, 0},
			  {1, 1, 0},
			  {0, 1, 1}},
			 {{0, 1, 0},
			  {1, 1, 0},
			  {1, 0, 0}}}},
};

void hide_cursor()
{
    HANDLE hStdOut = NULL;
    CONSOLE_CURSOR_INFO curInfo;

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(hStdOut, &curInfo);
    curInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hStdOut, &curInfo);
}

void start()
{
    int flag = 0;
    while(1)
    {
        Sleep(100);

        printf("\033[%d;%dH\x1b[47m     \x1b[0m  \x1b[47m     \x1b[0m  \x1b[47m     \x1b[0m  \x1b[47m     \x1b[0m  \x1b[47m     \x1b[0m  \x1b[47m     \x1b[0m\n", 3, 5);
        printf("\033[%d;%dH  \x1b[47m \x1b[0m    \x1b[47m \x1b[0m        \x1b[47m \x1b[0m    \x1b[47m \x1b[0m   \x1b[47m \x1b[0m    \x1b[47m \x1b[0m    \x1b[47m \x1b[0m\n", 4, 5);
        printf("\033[%d;%dH  \x1b[47m \x1b[0m    \x1b[47m     \x1b[0m    \x1b[47m \x1b[0m    \x1b[47m   \x1b[0m      \x1b[47m \x1b[0m     \x1b[47m   \x1b[0m\n", 5, 5);
        printf("\033[%d;%dH  \x1b[47m \x1b[0m    \x1b[47m \x1b[0m        \x1b[47m \x1b[0m    \x1b[47m \x1b[0m  \x1b[47m \x1b[0m     \x1b[47m \x1b[0m        \x1b[47m \x1b[0m\n", 6, 5);
        printf("\033[%d;%dH  \x1b[47m \x1b[0m    \x1b[47m     \x1b[0m    \x1b[47m \x1b[0m    \x1b[47m \x1b[0m   \x1b[47m \x1b[0m  \x1b[47m     \x1b[0m  \x1b[47m     \x1b[0m\n", 7, 5);

        if(LEFT_FUNC())
            flag = 0;  
        if(RIGHT_FUNC())
            flag = 1;

        if(!flag)
        {
            printf("\033[%d;%dH\x1b[42m start \x1b[0m  rule ", 12, 17);
            if(START_FUNC())
                break;
        }
        if(flag)
        {
            printf("\033[%d;%dH start  \x1b[43m rule \x1b[0m", 12, 17);
            if(START_FUNC())
            {
                system("cls");
                Sleep(100);

                printf("\033[%d;%dH R U L E\n", 3, 5);
                printf("\033[%d;%dH - press \x1b[42m Left \x1b[0m \x1b[42m Down \x1b[0m \x1b[42m Right \x1b[0m to move block\n", 5, 5);
                printf("\033[%d;%dH - press \x1b[42m Up \x1b[0m to rotate 90 clockwise\n", 7, 5);
                printf("\033[%d;%dH - press \x1b[42m Space \x1b[0m to hard drop\n", 9, 5);
                printf("\033[%d;%dH - press \x1b[42m Shift \x1b[0m to hold\n", 11, 5);
                printf("\033[%d;%dH - press \x1b[42m Enter \x1b[0m to \x1b[43m pause \x1b[0m\n", 13, 5);
                printf("\033[%d;%dH - press \x1b[42m Ctrl \x1b[0m to \x1b[41m AUTO Mode \x1b[0m\n", 15, 5);

                printf("\033[%d;%dH S C O R E\n", 18, 5);
                printf("\033[%d;%dH - 1 line:  100\n",20, 5);
                printf("\033[%d;%dH - 2 lines: 300\n",22, 5);
                printf("\033[%d;%dH - 3 lines: 500\n",24, 5);
                printf("\033[%d;%dH - 4 lines: 800\n",26, 5);
                
                printf("\033[%d;%dH Press SPACE to return", 29, 13);
                
                while(1)
                {
                    if(START_FUNC())
                    {
                        system("cls");
                        break;
                    }
                }
            }
        }

        printf("\033[%d;%dH Press SPACE to select", 15, 13);
    }
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
    printf("\033[1;0H LEVEL: %d\n", state->level);
    printf("\033[2;0H Line: %2d /%d\n", state->line, 10 + state->level*LEVEL_RANGE);
    printf("\033[3;0H Score: %d\n", state->score);

    printf("\033[%d;%dH\n", 0, 15);
    for (int i = 0; i < CANVAS_HEIGHT; i++)
    {
        printf("\033[%d;%dH|", i, 15);
        for (int j = 0; j < CANVAS_WIDTH; j++)
            printf("\033[%dm\u3000", canvas[i][j].color);
        printf("\033[0m|\n");
    }

    Shape shapeData = shapes[state->queue[1]];
    printf("\033[%d;%dHNext:", 3, CANVAS_WIDTH * 2 + 20);
    for (int i = 1; i <= 3; i++)
    {
        shapeData = shapes[state->queue[i]];
        for (int j = 0; j < 4; j++)
        {
            printf("\033[%d;%dH", i * 4 + j + 1, CANVAS_WIDTH * 2 + 30);
            for (int k = 0; k < 4; k++)
            {
                if (j < shapeData.size && k < shapeData.size && shapeData.rotates[0][j][k])
                    printf("\x1b[%dm  ", shapeData.color);
                else
                    printf("\x1b[0m  ");
            }
        }
    }
    
    if(!state->hold_use)
        printf("\033[%d;%dHHold (used):", 16, CANVAS_WIDTH * 2 + 20);
    else
        printf("\033[%d;%dHHold:       ", 16, CANVAS_WIDTH * 2 + 20);

    shapeData = shapes[state->hold];
    for (int j = 0; j < 4; j++)
    {
        printf("\033[%d;%dH", 18 + j, CANVAS_WIDTH * 2 + 30);
        for (int k = 0; k < 4; k++)
        {
            if (j < shapeData.size && k < shapeData.size && shapeData.rotates[0][j][k])
                printf("\x1b[%dm  ", shapeData.color);
            else
                printf("\x1b[0m  ");
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

void score_count(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], State *state)
{
    int linesCleared = clearLine(canvas);

    state->line += linesCleared;

    if(linesCleared == 1)
        state->score += 100*state->level;
    else if(linesCleared == 2)
        state->score += 300*state->level;
    else if(linesCleared == 3)
        state->score += 500*state->level;
    else if(linesCleared == 4)
        state->score += 800*state->level;
}

void game_pause()
{
    if(PAUSE_FUNC())
    {
        int flag = 0;
        printf("\033[%d;%dH\x1b[43m PAUSE \x1b[0m\033[%d;%dH", CANVAS_HEIGHT /2, CANVAS_WIDTH + 12, CANVAS_HEIGHT + 5, 0);
        while(1)
        {
            Sleep(100);

            if(LEFT_FUNC())
                flag = 0;  
            if(RIGHT_FUNC())
                flag = 1;

            if(!flag)
            {
                printf("\033[%d;%dH\x1b[42m continue \x1b[0m  exit \033[%d;%dH", CANVAS_HEIGHT /2 + 2, CANVAS_WIDTH + 8, CANVAS_HEIGHT + 5, 0);
                if(PAUSE_FUNC())
                    break;
            }
            if(flag)
            {
                printf("\033[%d;%dH continue  \x1b[41m exit \x1b[0m\033[%d;%dH", CANVAS_HEIGHT /2 + 2, CANVAS_WIDTH + 8, CANVAS_HEIGHT + 5, 0);
                if(PAUSE_FUNC())
                {
                    printf("\033[%d;%dH\x1b[41m GAME OVER \x1b[0m\033[%d;%dH", CANVAS_HEIGHT /2, CANVAS_WIDTH + 10, CANVAS_HEIGHT + 5, 0);
                    exit(0);
                }
            }
        }
    }
}

void hold(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], State *state)
{
    if(state->hold_use && HOLD_FUNC())
    {
        for (int i = 0; i < shapes[state->queue[0]].size; i++)
        {
            for (int j = 0; j < shapes[state->queue[0]].size; j++)
                resetBlock(&canvas[state->y + i][state->x + j]);
        }

        if(state->hold == -1)
        {
            state->hold = state->queue[0];
            state->queue[0] = state->queue[1];
            state->queue[1] = state->queue[2];
            state->queue[2] = state->queue[3];
            state->queue[3] = rand() % 7;
        }
        else
        {
            ShapeID tmp = state->queue[0];
            state->queue[0] = state->hold;
            state->hold = tmp;
        }

        state->x = CANVAS_WIDTH / 2;
        state->y = 0;
        state->rotate = 0;
        state->fallTime = 0;
        state->hold_use = false;
    }
}

void control(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], State *state)
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

    hold(canvas, state);
    
    Sleep(50);
    logic(canvas, state);
}

int evaluate(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], State test)
{
    Shape shapeData = shapes[test.queue[0]];
    int size = shapeData.size;
    int state_score = test.y*4;

    for (int i = CANVAS_HEIGHT - 1; i >= 0; i--)
    {
        bool isFull = true;
        for (int j = 0; j < CANVAS_WIDTH; j++)
        {
            if (canvas[i][j].shape == EMPTY && !shapeData.rotates[test.rotate][i][j])
            {
                isFull = false;
                break;
            }
        }

        if (isFull)
            state_score += 100;
    }

    for(int i=0; i<size; i++) // the state round the test_block
    {
        for(int j=0; j<size; j++)
        {
            if(!shapeData.rotates[test.rotate][i][j] && canvas[test.y+i+1][test.x+j].shape == EMPTY)
                state_score -= 2;

            if(shapeData.rotates[test.rotate][i][j])
                state_score += i*2;

            if(shapeData.rotates[test.rotate][i][j])
            {
                if(test.y+1 < CANVAS_HEIGHT && canvas[test.y+i+1][test.x+j].shape != EMPTY)
                    state_score += 1;
                if(test.x+1 < CANVAS_WIDTH && canvas[test.y+i][test.x+j+1].shape != EMPTY)
                    state_score += 1;
                if(test.y-1 >= 0 && canvas[test.y+i][test.x+j-1].shape != EMPTY)
                    state_score += 1;
            }
        }
    }
    return state_score;
}

State* best_move(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], State state)
{
    State test = state;
    State best_solve = test;
    Shape shapeData = shapes[test.queue[0]];
    int size = shapeData.size;
    int best_score = 0;

    for(int rotate=0; rotate<4; rotate++)  // each block has 4 directions
    {
        test.x = 0;
        test.y = 0;
        test.rotate = rotate;

        while(test.x < CANVAS_WIDTH)
        {
            bool move = true;
            while(move)
            {
                for(int i=0; i<size; i++)
                {
                    for(int j=0; j<size; j++)
                    {
                        if (shapeData.rotates[test.rotate][i][j])
                        {
                            if (!canvas[test.y + 1 + i][test.x + j].current && canvas[test.y + 1 + i][test.x + j].shape != EMPTY)
                                move = false;
                        }
                    }
                }
                if(move)
                    test.y += 1;
            }
            
            int now_score = evaluate(canvas, test);
            if(now_score > best_score)
            {
                best_score = now_score;
                best_solve = test;
            }

            test.x += 1;
            test.y = 0;
        }
    }
    return &best_solve;
}

void auto_play(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], State *state)
{
    State* best = best_move(canvas, *state);
    int targ_x = best->x;
    int targ_y = best->y;
    int targ_rotate = best->rotate;

    if(state->rotate != targ_rotate)
    {
        int new_Rotate = (state->rotate + 1) % 4;
        if (move(canvas, state->x, state->y, state->rotate, state->x, state->y, new_Rotate, state->queue[0]))
            state->rotate = new_Rotate;
    }
    else if(state->x > targ_x && move(canvas, state->x, state->y, state->rotate, state->x - 1, state->y, state->rotate, state->queue[0]))
            state->x -= 1;
    else if(state->x < targ_x && move(canvas, state->x, state->y, state->rotate, state->x + 1, state->y, state->rotate, state->queue[0]))
            state->x += 1;
    else
        state->fallTime += FALL_DELAY * CANVAS_HEIGHT;

    logic(canvas, state);
}

void logic(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], State *state)
{
    game_pause();

    state->fallTime += RENDER_DELAY + state->level * 20;

    while (state->fallTime >= FALL_DELAY)
    {
        state->fallTime -= FALL_DELAY;

        if (move(canvas, state->x, state->y, state->rotate, state->x, state->y + 1, state->rotate, state->queue[0]))
            state->y++;
        else
        {
            score_count(canvas, state);

            if(state->line == 5 + state->level*LEVEL_RANGE)
            {
                printf("\033[5;0H\x1b[42m LEVEL UP!\x1b[0m\n");
                state->level += 1;
                state->line = 0;
            }

            if(state->line == 1)
                printf("\033[5;0H          \n");

            state->x = CANVAS_WIDTH / 2;
            state->y = 0;
            state->rotate = 0;
            state->fallTime = 0;
            state->hold_use = true;
            state->queue[0] = state->queue[1];
            state->queue[1] = state->queue[2];
            state->queue[2] = state->queue[3];
            state->queue[3] = rand() % 7;

            if (!move(canvas, state->x, state->y, state->rotate, state->x, state->y, state->rotate, state->queue[0]))
            {
                printf("\033[%d;%dH\x1b[41m GAME OVER \x1b[0m\033[%d;%dH", CANVAS_HEIGHT /2, CANVAS_WIDTH + 10, CANVAS_HEIGHT + 5, 0);
                exit(0);
            }
        }
    }
    return;
}