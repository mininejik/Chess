#include "draw_pieces.h"
#include "chess_pieces.h"

using namespace std;
void DrawDown(int x, int y, Color color) {
	DrawRectangle(x + 10, y + 85, 80, 10, color);
	DrawCircle(x + 10, y + 90, 5, color);
	DrawCircle(x + 90, y + 90, 5, color);
	DrawRectangle(x + 10, y + 80, 80, 5, color);
}
void DrawPawn(int x, int y, Color color) {
	x *= 100;
	y *= 100;
	x += 100;
	y += 100;
	DrawDown(x, y, color);
	DrawTriangle({ float(x + 50), float(y + 30) }, { float(x + 25), float(y + 80) }, { float(x + 75), float(y + 90) }, color);
	DrawCircle(x + 50, y + 30, 20, color);
	DrawTriangle({ float(x + 50), float(y + 45) }, { float(x + 25), float(y + 55) }, { float(x + 75), float(y + 55) }, color);
}
void DrawRook(int x, int y, Color color) {
	x *= 100;
	y *= 100;
	x += 100;
	y += 100;
	DrawDown(x, y, color);
	DrawRectangle(x + 30, y + 40, 40, 50, color);
	DrawRectangle(x + 20, y + 25, 60, 20, color);
	DrawRectangle(x + 20, y + 10, 15, 15, color);
	DrawRectangle(x + 41, y + 10, 18, 15, color);
	DrawRectangle(x + 65, y + 10, 15, 15, color);
}
void DrawKnight(int x, int y, Color color) {
	x *= 100;
	y *= 100;
	x += 100;
	y += 100;
	DrawDown(x, y, color);
	DrawRectangle(x + 30, y + 40, 40, 50, color);
	DrawRectangle(x + 15, y + 15, 55, 25, color);
	DrawTriangle({ float(x + 55), float(y + 15) }, { float(x + 65), float(y + 15) }, { float(x + 60), float(y + 5) }, color);

}
void DrawBishop(int x, int y, Color color) {
	x *= 100;
	y *= 100;
	x += 100;
	y += 100;
	DrawDown(x, y, color);
	DrawRectangle(x + 30, y + 45, 40, 10, color);
	DrawCircle(x + 30, y + 50, 5, color);
	DrawCircle(x + 70, y + 50, 5, color);
	DrawRectangle(x + 35, y + 45, 30, 50, color);
	DrawEllipse(x + 50, y + 40, 10, 20, color);
	DrawCircle(x + 50, y + 15, 5, color);

}
void DrawKing(int x, int y, Color color) {
	x *= 100;
	y *= 100;
	x += 100;
	y += 100;
	DrawDown(x, y, color);
	DrawRectangle(x + 35, y + 30, 30, 50, color);
	DrawCircle(x + 30, y + 35, 5, color);
	DrawCircle(x + 70, y + 35, 5, color);
	DrawRectangle(x + 30, y + 30, 40, 10, color);
	DrawRectangle(x + 45, y + 10, 10, 20, color);
	DrawRectangle(x + 40, y + 15, 20, 10, color);
}
void DrawQueen(int x, int y, Color color) {
	x *= 100;
	y *= 100;
	x += 100;
	y += 100;
	DrawDown(x, y, color);
	DrawRectangle(x + 35, y + 30, 30, 50, color);
	DrawCircle(x + 30, y + 35, 5, color);
	DrawCircle(x + 70, y + 35, 5, color);
	DrawRectangle(x + 30, y + 30, 40, 10, color);
	DrawTriangle({ float(x + 35), float(y + 15) }, { float(x + 35), float(y + 30) }, { float(x + 45), float(y + 30) }, color);
	DrawTriangle({ float(x + 45), float(y + 30) }, { float(x + 55), float(y + 30) }, { float(x + 50), float(y + 15) }, color);
	DrawTriangle({ float(x + 55), float(y + 30) }, { float(x + 65), float(y + 30) }, { float(x + 65), float(y + 15) }, color);
	DrawCircle(x + 35, y + 15, 5, color);
	DrawCircle(x + 50, y + 15, 5, color);
	DrawCircle(x + 65, y + 15, 5, color);
}
void DrawPiece(int y, int x) {
	if (Board[y][x] == nullptr)return;
	if (Board[y][x]->get_type() == PAWN) DrawPawn(x, y, Board[y][x]->get_color());
	else if (Board[y][x]->get_type() == ROOK) DrawRook(x, y, Board[y][x]->get_color());
	else if (Board[y][x]->get_type() == KNIGHT) DrawKnight(x, y, Board[y][x]->get_color());
	else if (Board[y][x]->get_type() == BISHOP) DrawBishop(x, y, Board[y][x]->get_color());
	else if (Board[y][x]->get_type() == QUEEN) DrawQueen(x, y, Board[y][x]->get_color());
	else if (Board[y][x]->get_type() == KING) DrawKing(x, y, Board[y][x]->get_color());
}