#include "logic.h"
#include <raylib.h>
#include "game_over.h"
#include "draw_pieces.h"
piece* choosen = nullptr;
inline int abs(int x)
{
	return (x > 0 ? x : -x);
}
Point SetElPassant(Point new_piece)
{
	static Point piece = { -1, -1 };
	Point p = piece;
	piece = new_piece;
	return p;
}
Point getElPassant()
{
	Point p = SetElPassant({ -1, -1 });
	SetElPassant(p);
	return p;
}
bool IsCheck(Color color)
{
	Point king;
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			if (Board[i][j] != nullptr && Board[i][j]->get_type() == KING && Board[i][j]->get_color() == color) {
				king.x = j;
				king.y = i;
				break;
			}
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			if (Board[i][j] != nullptr && Board[i][j]->get_color() != color) {
				vector<Point> vec = Board[i][j]->squares_attacking();
				for (int k = 0; k < vec.size(); ++k)
					if (vec[k] == king)return 1;
			}
	return 0;
}
bool IsMoveLegal(Point starting, Point ending)
{
	piece* p1 = Board[starting.y][starting.x], * p2 = Board[ending.y][ending.x];
	Board[ending.y][ending.x] = Board[starting.y][starting.x];
	Board[starting.y][starting.x] = nullptr;
	bool moved = Board[ending.y][ending.x]->DidMove();
	Board[ending.y][ending.x]->set_position(ending);
	bool ans = IsCheck(Board[ending.y][ending.x]->get_color());

	Board[starting.y][starting.x] = p1;
	Board[ending.y][ending.x] = p2;
	Board[starting.y][starting.x]->set_position(starting);
	if (!moved)Board[starting.y][starting.x]->unmove();
	return !ans;
}
bool IsElPassantLegal(piece* ptr)
{
	Point p = getElPassant(), attacking = { ptr->get_y(), ptr->get_x() }, in = { p.y + (ptr->get_color() == BLACK ? 1 : -1), p.x };
	piece* def_pawn = Board[p.y][p.x];
	Board[p.y][p.x] = nullptr;
	Board[in.y][in.x] = ptr;
	Board[ptr->get_y()][ptr->get_x()] = nullptr;
	ptr->set_position({ in.y, in.x });


	bool ans = IsCheck(ptr->get_color());

	Board[ptr->get_y()][ptr->get_x()] = nullptr;
	ptr->set_position(attacking);
	Board[ptr->get_y()][ptr->get_x()] = ptr;
	Board[p.y][p.x] = def_pawn;
	SetElPassant(p);

	return !ans;
}
Point input()
{

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

		Vector2 pos = GetMousePosition();
		int x = int(pos.x), y = int(pos.y);

		x -= 100;
		y -= 100;
		x /= 100;
		if (y > 0) y /= 100;
		else y = -1;
		return { y, x };
	}
	return { -2, -2 };
}
Color turn = WHITE;

int IsCheckMate() {// 1 - yes, 0 - no, -1 - draw
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			if (Board[i][j] != nullptr && Board[i][j]->get_color() == turn)
			{
				vector<Point> attack = Board[i][j]->squares_attacking();
				for (int k = 0; k < attack.size(); k++)
					if (IsMoveLegal({ i, j }, attack[k]))return 0;
			}

	//el passant

	Point p = getElPassant();

	if (p.x != -1)
	{
		if (p.x == 0)
		{
			if (Board[p.y][p.x + 1] != nullptr && Board[p.y][p.x + 1]->get_type() == PAWN && Board[p.y][p.x + 1]->get_color() == turn
				&& IsElPassantLegal(Board[p.y][p.x + 1]))return 0;

		}
		else if (p.x == 7)
		{
			if (Board[p.y][p.x - 1] != nullptr && Board[p.y][p.x - 1]->get_type() == PAWN && Board[p.y][p.x - 1]->get_color() == turn
				&& IsElPassantLegal(Board[p.y][p.x - 1]))return 0;
		}
		else {
			if (Board[p.y][p.x + 1] != nullptr && Board[p.y][p.x + 1]->get_type() == PAWN && Board[p.y][p.x + 1]->get_color() == turn
				&& IsElPassantLegal(Board[p.y][p.x + 1]))return 0;
			if (Board[p.y][p.x - 1] != nullptr && Board[p.y][p.x - 1]->get_type() == PAWN && Board[p.y][p.x - 1]->get_color() == turn
				&& IsElPassantLegal(Board[p.y][p.x - 1]))return 0;
		}
	}

	if (IsCheck(turn))return 1;
	return -1;
}

int now_transformating = 0;// 0 - no, 1 - black, 2 - white

void transformation(Point point)
{
	if (now_transformating == 0)return;
	Point in = input();

	Color color = (now_transformating == 2 ? WHITE : BLACK);

	if (in.y == (now_transformating == 2 ? -1 : 8)) {

		if (in.x == 2) { create((now_transformating == 2 ? 0 : 7), point.x, QUEEN, color); now_transformating = 0; choosen = nullptr; }
		else if (in.x == 3) { create((now_transformating == 2 ? 0 : 7), point.x, KNIGHT, color); now_transformating = 0; choosen = nullptr; }
		else if (in.x == 4) { create((now_transformating == 2 ? 0 : 7), point.x, BISHOP, color); now_transformating = 0; choosen = nullptr; }
		else if (in.x == 5) { create((now_transformating == 2 ? 0 : 7), point.x, ROOK, color); now_transformating = 0; choosen = nullptr; }
	}
	return;
}
bool CantMate()
{
	int white = 0, black = 0;
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			if (Board[i][j] != nullptr) {
				if (Board[i][j]->get_color() == BLACK) {
					if (Board[i][j]->get_type() == BISHOP || Board[i][j]->get_type() == KNIGHT)black++;
					else black += (Board[i][j]->get_type() == KING ? 0 : 100);
				}
				else {
					if (Board[i][j]->get_type() == BISHOP || Board[i][j]->get_type() == KNIGHT)white++;
					else white += (Board[i][j]->get_type() == KING ? 0 : 100);
				}
			}
	return !(black > 1 || white > 1);
}
void logic()
{

	if (now_transformating != 0)transformation({ choosen->get_y(), choosen->get_x() });
	else {

		Point in = input();
		if (IsCheckMate() == 1) {
			game_over((turn == BLACK ? 1 : 2));
		}
		else if (IsCheckMate() == -1) {
			game_over(3);
		}
		if (in.x != -2)
		{
			if (!(in.x >= 0 && in.x < 8 && in.y >= 0 && in.y < 8))choosen = nullptr;
			else {
				if (choosen != nullptr) {
					//el passant
					Point p = getElPassant();
					if (choosen->get_type() == PAWN && in.x == p.x && in.y == p.y + (Board[p.y][p.x]->get_color() == BLACK ? -1 : 1) &&
						choosen->get_color() != Board[p.y][p.x]->get_color() && choosen->get_y() == p.y && abs(p.x - choosen->get_x()) == 1 && IsElPassantLegal(choosen)) {
						Board[p.y][p.x] = nullptr;
						Board[in.y][in.x] = choosen;
						Board[choosen->get_y()][choosen->get_x()] = nullptr;
						choosen->set_position({ in.y, in.x });
						if (turn == WHITE)turn = BLACK;
						else turn = WHITE;
						SetElPassant({ -1, -1 });
					}
					//castling from rook
					else if (choosen->get_type() == ROOK && ((choosen->get_color() == BLACK && in.x == 4 && in.y == 0) ||
						(choosen->get_color() == WHITE && in.x == 4 && in.y == 7)) && choosen->canCastle()) {

						Castling({ in.y, 4 }, { choosen->get_y(), choosen->get_x() });
						if (turn == WHITE)turn = BLACK;
						else turn = WHITE;
						SetElPassant({ -1, -1 });
					}
					// castling from king with left rook
					else if (choosen->get_type() == KING && in.y == choosen->get_y() &&
						in.x == 0 && Board[choosen->get_y()][0] != nullptr && Board[choosen->get_y()][0]->canCastle()) {

						Castling({ choosen->get_y(), choosen->get_x() }, { in.y, 0 });
						if (turn == WHITE)turn = BLACK;
						else turn = WHITE;
						SetElPassant({ -1, -1 });
					}
					// castling from king with right rook
					else if (choosen->get_type() == KING && in.y == choosen->get_y() &&
						in.x == 7 && Board[choosen->get_y()][7] != nullptr && Board[choosen->get_y()][7]->canCastle()) {

						Castling({ choosen->get_y(), choosen->get_x() }, { in.y, 7 });
						if (turn == WHITE)turn = BLACK;
						else turn = WHITE;
						SetElPassant({ -1, -1 });
					}
					// other moves
					else {
						vector<Point> attack, vec = choosen->squares_attacking();

						for (int i = 0; i < vec.size(); ++i)
							if (IsMoveLegal({ choosen->get_y(), choosen->get_x() }, vec[i]))attack.push_back(vec[i]);
						for (int i = 0; i < attack.size(); ++i)
							if (attack[i].x == in.x && attack[i].y == in.y && (Board[attack[i].y][attack[i].x] == nullptr || Board[attack[i].y][attack[i].x]->get_color() != turn)) {
								if (choosen->get_type() == PAWN && abs(in.y - choosen->get_y()) == 2) SetElPassant({ in.y, choosen->get_x() });
								else SetElPassant({ -1, -1 });
								Board[choosen->get_y()][choosen->get_x()] = nullptr;
								choosen->set_position(in);
								Board[in.y][in.x] = choosen;
								if (turn == WHITE)turn = BLACK;
								else turn = WHITE;
								break;
							}
						if (choosen->get_type() == PAWN && choosen->get_y() == 0) { now_transformating = 2; return; }
						else if (choosen->get_type() == PAWN && choosen->get_y() == 7) { now_transformating = 1; return; }
					}
					if (CantMate())game_over(3);
					choosen = nullptr;
				}
				else {
					if (Board[in.y][in.x] != nullptr && Board[in.y][in.x]->get_color() == turn)choosen = Board[in.y][in.x];
				}
			}
		}

	}
}