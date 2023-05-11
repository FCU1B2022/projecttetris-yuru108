#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>

#define CANVAS_WIDTH 10
#define CANVAS_HEIGHT 20

typedef enum
{
	RED = 1,
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
}State;

typedef struct
{
    Color color;
    ShapeId shape;
    bool current;
}Block;

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

State *init();
void resetBlock(Block *block);