#include <raylib.h>
#include "draw.h"
#include "setup.h"
#include "logic.h"
using namespace std;
bool WindowShouldClose()
{
	return IsKeyPressed(KEY_ESCAPE);
}
int main()
{
	InitWindow(1000, 1000, "chess");
	setup();
	SetTargetFPS(144);
	while (!WindowShouldClose())
	{
		logic();
		draw();
	}
	return 0;
}