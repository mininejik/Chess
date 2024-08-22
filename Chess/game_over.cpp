#include "game_over.h"
#include <raylib.h>
#include <iostream>
void game_over(int who_won)
{
	while (!IsKeyPressed(KEY_ESCAPE))
	{
		BeginDrawing();
		ClearBackground(LIME);
		if (who_won == 1) DrawText("WHITE WON", 250, 450, 100, GREEN);
		else if (who_won == 2) DrawText("BLACK WON", 250, 450, 100, GREEN);
		else  DrawText("DRAW", 375, 450, 100, GREEN);
		EndDrawing();
	}
	exit(0);
}