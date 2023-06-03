#include "tetris.h"

int evaluate(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH],State test)
{
    Shape shapeData = shapes[test.queue[0]]
    int size = shapeDate.size;
    int state_score = test.y;

    for(int i=0; i<size; i++) // the state round the test_block
    {
        for(int j=0; j<size; j++)
        {
            if(!shapeData.rotates[test.rotate][i][j] && canvas[test.y+i][test.x+j].color == -1)
                state_score -= 1;
        }
    }
    return state_score;
}

State auto_play(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], State state)
{
    State test = state;
    Shape shapeData = shapes[test.queue[0]]
    int size = shapeDate.size;
    int best_score = 0;
    State best_solve = test;

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
                int now_score = evaluate(canvas, test);
                if(now_score > best_score)
                {
                    best_score = now_score;
                    best_solve = test;
                }

                for(int i; i<size; i++)
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

            test.x += 1;
            test.y = 0;
        }
    }
    return best_solve;
}