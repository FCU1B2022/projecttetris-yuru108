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

#define FALL_DELAY 500	 // The delay between each fall, default = 500
#define RENDER_DELAY 100 // The delay between each frame, default = 100

#define LEFT_FUNC() GetAsyncKeyState(LEFT_KEY) & 0x8000
#define RIGHT_FUNC() GetAsyncKeyState(RIGHT_KEY) & 0x8000
#define ROTATE_FUNC() GetAsyncKeyState(ROTATE_KEY) & 0x8000
#define DOWN_FUNC() GetAsyncKeyState(DOWN_KEY) & 0x8000
#define FALL_FUNC() GetAsyncKeyState(FALL_KEY) & 0x8000

// =============================

void setBlock(Block *block, Color color, ShapeID shape, bool current);
void resetBlock(Block *block);
void printCanvas(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], State *state);
bool move(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], int original_X, int original_Y, int original_Rotate, int new_X, int new_Y, int new_Rotate, ShapeID shapeID);
void logic(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], State *state);
int clearLine(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH]);

// =============================

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
	int score;
	int rotate;
	int fallTime;
	ShapeID queue[4];
} State;

typedef struct
{
	Color color;
	ShapeID shape;
	bool current;
} Block;

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