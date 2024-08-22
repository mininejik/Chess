#include "draw.h"
#include "raylib.h"
#include <string>
#include "draw_pieces.h"
#include "logic.h"
#include "chess_pieces.h"
using namespace std;

void draw()
{
	BeginDrawing();
	ClearBackground(Color{ 0, 190, 48, 255 });
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			DrawRectangle(i * 100 + 100, j * 100 + 100, 100, 100, ((i + j) % 2 == 1 ? GREEN : Color{ 0, 255, 48, 255 }));
	if (choosen != nullptr && choosen->get_type() == PAWN) {
		Point p = getElPassant();
		if (p.x != -1 && choosen->get_color() != Board[p.y][p.x]->get_color() && choosen->get_y() == p.y && abs(p.x - choosen->get_x()) == 1 && IsElPassantLegal(choosen))
			DrawRectangle(p.x * 100 + 100, p.y * 100 + 100 + (choosen->get_color() == BLACK ? 100 : -100), 100, 100, RED);
	}

	for (int i = 0; i < 8; i++)
	{
		string str;
		str = i + '1';
		DrawText(str.c_str(), 24, 821 - i * 100, 75, BLACK);
		DrawText(str.c_str(), 25, 820 - i * 100, 75, LIME);
		str = i + 'a';
		DrawText(str.c_str(), i * 100 + 129, 15, 75, BLACK);
		DrawText(str.c_str(), i * 100 + 130, 15, 75, LIME);
	}
	if (choosen != nullptr) {
		if (choosen->get_type() == ROOK && choosen->canCastle()) {
			if (choosen->get_color() == BLACK) {
				DrawRectangle(500, 100, 100, 100, RED);
				DrawRectangle(510, 110, 80, 80, Color{ 0, 255, 48, 255 });
			}
			else {
				DrawRectangle(500, 800, 100, 100, RED);
				DrawRectangle(510, 810, 80, 80, GREEN);
			}
		}

		if (choosen->get_type() == KING) {
			if (Board[choosen->get_y()][0] != nullptr && Board[choosen->get_y()][0]->canCastle()) {
				if (choosen->get_color() == BLACK) {
					DrawRectangle(100, 100, 100, 100, RED);
					DrawRectangle(110, 110, 80, 80, Color{ 0, 255, 48, 255 });
				}
				else {
					DrawRectangle(100, 800, 100, 100, RED);
					DrawRectangle(110, 810, 80, 80, GREEN);
				}
			}
			if (Board[choosen->get_y()][7] != nullptr && Board[choosen->get_y()][7]->canCastle()) {
				if (choosen->get_color() == BLACK) {
					DrawRectangle(800, 100, 100, 100, RED);
					DrawRectangle(810, 110, 80, 80, GREEN);
				}
				else {
					DrawRectangle(800, 800, 100, 100, RED);
					DrawRectangle(810, 810, 80, 80, Color{ 0, 255, 48, 255 });
				}
			}
		}
		vector<Point> attack, vec = choosen->squares_attacking();
		for (int i = 0; i < vec.size(); ++i)
			if (IsMoveLegal({ choosen->get_y(), choosen->get_x() }, vec[i]))attack.push_back(vec[i]);

		DrawRectangle(choosen->get_x() * 100 + 100, choosen->get_y() * 100 + 100, 100, 100, BLUE);
		for (int i = 0; i < attack.size(); ++i)
		{
			DrawRectangle(attack[i].x * 100 + 100, attack[i].y * 100 + 100, 100, 100, RED);
			if (Board[attack[i].y][attack[i].x] == nullptr)DrawRectangle(attack[i].x * 100 + 110, attack[i].y * 100 + 110, 80, 80,
				((attack[i].y + attack[i].x) % 2 == 1 ? GREEN : Color{ 0, 255, 48, 255 }));
		}

	}




	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			DrawPiece(i, j);


	if (now_transformating != 0) {
		Color color = (now_transformating == 1 ? BLACK : WHITE);
		int y = (color == BLACK ? 9 : 0);
		DrawRectangle(300, y * 100, 400, 100, GRAY);
		y--;
		DrawQueen(2, y, color);
		DrawKnight(3, y, color);
		DrawBishop(4, y, color);
		DrawRook(5, y, color);
	}




	EndDrawing();
}