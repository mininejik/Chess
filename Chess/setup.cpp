#include "setup.h"
#include "chess_pieces.h"
#include "logic.h"

void setup() {
	choosen = nullptr;
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			Board[i][j] = nullptr;


	for (int i = 0; i < 8; i++)
	{
		create(1, i, PAWN, BLACK);
		create(6, i, PAWN, WHITE);
	}
	create(0, 0, ROOK, BLACK);
	create(0, 7, ROOK, BLACK);
	create(7, 0, ROOK, WHITE);
	create(7, 7, ROOK, WHITE);
	create(0, 1, KNIGHT, BLACK);
	create(0, 6, KNIGHT, BLACK);
	create(7, 1, KNIGHT, WHITE);
	create(7, 6, KNIGHT, WHITE);
	create(0, 2, BISHOP, BLACK);
	create(0, 5, BISHOP, BLACK);
	create(7, 2, BISHOP, WHITE);
	create(7, 5, BISHOP, WHITE);
	create(0, 3, QUEEN, BLACK);
	create(7, 3, QUEEN, WHITE);
	create(0, 4, KING, BLACK);
	create(7, 4, KING, WHITE);
}