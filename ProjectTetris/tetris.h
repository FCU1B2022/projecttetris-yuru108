#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>

#define CANVAS_WIDTH 10
#define CANVAS_HEIGHT 20

#define LEFT_KEY 0x25	// The key to move left, default = 0x25 (left arrow)
#define RIGHT_KEY 0x27	// The key to move right, default = 0x27 (right arrow)
#define ROTATE_KEY 0x26 // The key to rotate, default = 0x26 (up arrow)
#define DOWN_KEY 0x28	// The key to move down, default = 0x28 (down arrow)
#define FALL_KEY 0x20	// The key to fall, default = 0x20 (spacebar)
#define HOLD_KEY 0x10   // The key to hold, default = 0x10 (shift)
#define START_KEY 0x20  // The key to start, default = 0x20 (spacebar)
#define PAUSE_KEY 0x0D  // The key to pause, default = 0x0D (enter)
#define AUTO_KEY 0x11   // The key to auto mode, default = 0x11 (control)

#define FALL_DELAY 500	 // The delay between each fall, default = 500
#define RENDER_DELAY 100 // The delay between each frame, default = 100
#define LEVEL_RANGE 5

#define LEFT_FUNC() GetAsyncKeyState(LEFT_KEY) & 0x8000
#define RIGHT_FUNC() GetAsyncKeyState(RIGHT_KEY) & 0x8000
#define ROTATE_FUNC() GetAsyncKeyState(ROTATE_KEY) & 0x8000
#define DOWN_FUNC() GetAsyncKeyState(DOWN_KEY) & 0x8000
#define FALL_FUNC() GetAsyncKeyState(FALL_KEY) & 0x8000
#define HOLD_FUNC() GetAsyncKeyState(HOLD_KEY) & 0x8000
#define PAUSE_FUNC() GetAsyncKeyState(PAUSE_KEY) & 0x8000
#define AUTO_FUNC() GetAsyncKeyState(AUTO_KEY) & 0x8000
#define START_FUNC() GetAsyncKeyState(START_KEY) & 0x8000

typedef enum
{
	RED = 41,
	GREEN,
	YELLOW,
	BLUE,
	PURPLE,
	CYAN,
	WHITE,
	BLACK = 0,
} Color;

typedef enum
{
	EMPTY = -1,
	I,
	J,
	L,
	O,
	S,
	T,
	Z
} ShapeID;

typedef struct
{
	ShapeID shape;
	Color color;
	int size;
	char rotates[4][4][4];
} Shape;

typedef struct
{
	int x;
	int y;
	int rotate;
	int score;
	int line;
	int level;
	int fallTime;
	bool hold_use;
	ShapeID hold;
	ShapeID queue[4];
} State;

typedef struct
{
	Color color;
	ShapeID shape;
	bool current;
} Block;


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
void logic(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], State *state);
int clearLine(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH]);

int evaluate(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH],State test);
State* best_move(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], State state);
void auto_play(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], State *state);