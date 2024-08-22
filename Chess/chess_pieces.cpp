#include "chess_pieces.h"
#include <algorithm>
using namespace std;

bool operator==(Color& a, Color b)
{
	return(a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a);
}
bool operator!=(Color& a, Color& b)
{
	return!(a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a);
}
bool operator!= (Point& p1, Point& p2)
{
	return !(p1.x == p2.x && p1.y == p2.y);
}
bool operator== (Point& p1, Point& p2)
{
	return (p1.x == p2.x && p1.y == p2.y);
}
piece& piece::operator= (const piece& P) {
	if (&P == this)return *this;
	moved = P.moved;
	x = P.x;
	y = P.y;
	color = P.color;
	type = P.type;
	return *this;
}
piece::piece(int mX, int mY, Color mColor, piece_type mType) : x(mX), y(mY), color(mColor), type(mType), moved(0) {}
pawn::pawn(int mX, int mY, Color mColor) : piece(mX, mY, mColor, PAWN) {}
queen::queen(int mX, int mY, Color mColor) : piece(mX, mY, mColor, QUEEN) {}
king::king(int mX, int mY, Color mColor) : piece(mX, mY, mColor, KING) {}
rook::rook(int mX, int mY, Color mColor) : piece(mX, mY, mColor, ROOK) {}
knight::knight(int mX, int mY, Color mColor) : piece(mX, mY, mColor, KNIGHT) {}
bishop::bishop(int mX, int mY, Color mColor) : piece(mX, mY, mColor, BISHOP) {}
piece::piece(piece& Piece) :x(Piece.x), y(Piece.y), type(Piece.type), color(Piece.color) {}
piece::piece() {}
pawn::pawn() {}
queen::queen() {}
king::king() {}
rook::rook() {}
knight::knight() {}
bishop::bishop() {}
bool comp(Point p1, Point p2)
{
	if (p1.x > p2.x)return true;
	else if (p1.x < p2.x)return false;
	return p1.y > p2.y;
}


void piece::unmove()
{
	moved = 0;
}
bool piece::DidMove()
{
	return moved;
}
void piece::move()
{
	moved = 1;
}
bool piece::canCastle()
{
	return 0;
}

vector<Point> attack(Color color)
{
	vector<Point> vec;
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			if (Board[i][j] != nullptr && Board[i][j]->get_color() == color) {
				vector<Point> v1 = Board[i][j]->squares_attacking();
				for (int k = 0; k < v1.size(); ++k)
					vec.push_back(v1[k]);
			}
	vector<Point> ans;
	sort(ans.begin(), ans.end(), comp);
	if (vec.size() == 0)return vec;
	ans.push_back(vec[0]);
	for (int i = 1; i < vec.size(); ++i)
		if (vec[i] != vec[i - 1])ans.push_back(vec[i]);
	return ans;
}
bool rook::canCastle()
{
	if (moved || ((color == BLACK && kings[0].DidMove()) || (color == WHITE && kings[1].DidMove())))return 0;
	vector<Point> squares_attaked = attack((color == BLACK ? WHITE : BLACK));
	if (x == 0) {
		if (Board[y][1] != nullptr || Board[y][2] != nullptr || Board[y][3] != nullptr) return 0;
		bool check = 1;
		for (int i = 0; i < squares_attaked.size(); ++i)
		{
			if (squares_attaked[i].y == y && (squares_attaked[i].x >= 0 && squares_attaked[i].x <= 4)) { check = 0; break; }
		}

		return check;
	}
	else {
		if (Board[y][5] != nullptr || Board[y][6] != nullptr) return 0;
		bool check = 1;
		for (int i = y; i < squares_attaked.size(); ++i)
		{
			if (squares_attaked[i].y == y && (squares_attaked[i].x >= 4 && squares_attaked[i].x <= 7)) { check = 0; break; }
		}
		return check;
	}
	return 0;
}
void piece::set_position(Point point) {
	moved = 1;
	x = point.x;
	y = point.y;
}
int piece::get_x()
{
	return x;
}
int piece::get_y()
{
	return y;
}
piece_type& piece::get_type()
{
	return type;
}

Color& piece::get_color() {
	return color;
}

vector<Point> pawn::squares_attacking() {
	vector<Point> vec;
	if (color == BLACK && y != 7 && Board[y + 1][x] == nullptr) vec.push_back({ y + 1, x });
	else if (color == WHITE && y != 0 && Board[y - 1][x] == nullptr)vec.push_back({ y - 1, x });
	if (color == BLACK && y == 1 && Board[y + 1][x] == nullptr && Board[y + 2][x] == nullptr)vec.push_back({ y + 2, x });
	else if (color == WHITE && y == 6 && Board[y - 1][x] == nullptr && Board[y - 2][x] == nullptr)vec.push_back({ y - 2, x });
	if (x != 0) {
		if (color == BLACK && y != 7 && Board[y + 1][x - 1] != nullptr && Board[y + 1][x - 1]->get_color() == WHITE)vec.push_back({ y + 1,x - 1 });
		if (color == WHITE && y != 0 && Board[y - 1][x - 1] != nullptr && Board[y - 1][x - 1]->get_color() == BLACK)vec.push_back({ y - 1,x - 1 });
	}
	if (x != 7) {
		if (color == BLACK && y != 7 && Board[y + 1][x + 1] != nullptr && Board[y + 1][x + 1]->get_color() == WHITE)vec.push_back({ y + 1,x + 1 });
		if (color == WHITE && y != 0 && Board[y - 1][x + 1] != nullptr && Board[y - 1][x + 1]->get_color() == BLACK)vec.push_back({ y - 1,x + 1 });
	}
	if (vec.size() != 0 && (vec[0].y == 8 || vec[0].y == -1))vec.clear();
	return vec;
}
vector<Point> piece::squares_attacking() {
	return {};
}
vector<Point> king::squares_attacking() {
	vector<Point> vec;
	if (x > 0) {
		if (y > 0) vec.push_back({ y - 1, x - 1 });
		if (y < 7) vec.push_back({ y + 1, x - 1 });
		vec.push_back({ y, x - 1 });
	}
	if (x < 7)
	{
		if (y > 0) vec.push_back({ y - 1, x + 1 });
		if (y < 7) vec.push_back({ y + 1, x + 1 });
		vec.push_back({ y, x + 1 });
	}
	if (y > 0) vec.push_back({ y - 1, x });
	if (y < 7) vec.push_back({ y + 1, x });
	vector<Point> ans;
	for (int i = 0; i < vec.size(); ++i)
		if (Board[vec[i].y][vec[i].x] == nullptr || Board[vec[i].y][vec[i].x]->get_color() != color) ans.push_back(vec[i]);
	return ans;
}
vector<Point> queen::squares_attacking() {
	vector<Point> vec;
	for (int i = y + 1; i < 8; ++i)
	{
		if (Board[i][x] != nullptr) {
			if (Board[i][x]->get_color() != color)vec.push_back({ i, x });
			break;
		}
		vec.push_back({ i, x });
	}
	for (int i = y - 1; i >= 0; --i)
	{
		if (Board[i][x] != nullptr) {
			if (Board[i][x]->get_color() != color)vec.push_back({ i, x });
			break;
		}
		vec.push_back({ i, x });
	}
	for (int i = x + 1; i < 8; ++i)
	{
		if (Board[y][i] != nullptr) {
			if (Board[y][i]->get_color() != color)vec.push_back({ y, i });
			break;
		}
		vec.push_back({ y, i });
	}
	for (int i = x - 1; i >= 0; --i)
	{
		if (Board[y][i] != nullptr) {
			if (Board[y][i]->get_color() != color)vec.push_back({ y, i });
			break;
		}
		vec.push_back({ y, i });
	}



	for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; --i, --j)
	{
		if (Board[j][i] != nullptr) {
			if (Board[j][i]->get_color() != color)vec.push_back({ j, i });
			break;
		}
		vec.push_back({ j, i });
	}
	for (int i = x + 1, j = y + 1; i < 8 && j < 8; ++i, ++j)
	{
		if (Board[j][i] != nullptr) {
			if (Board[j][i]->get_color() != color)vec.push_back({ j, i });
			break;
		}
		vec.push_back({ j, i });
	}

	for (int i = x + 1, j = y - 1; i < 8 && j >= 0; ++i, --j)
	{
		if (Board[j][i] != nullptr) {
			if (Board[j][i]->get_color() != color)vec.push_back({ j, i });
			break;
		}
		vec.push_back({ j, i });
	}
	for (int i = x - 1, j = y + 1; i >= 0 && j < 8; --i, ++j)
	{
		if (Board[j][i] != nullptr) {
			if (Board[j][i]->get_color() != color)vec.push_back({ j, i });
			break;
		}
		vec.push_back({ j, i });
	}
	return vec;
}
vector<Point> rook::squares_attacking() {
	vector<Point> vec;
	for (int i = y + 1; i < 8; ++i)
	{
		if (Board[i][x] != nullptr) {
			if (Board[i][x]->get_color() != color)vec.push_back({ i, x });
			break;
		}
		vec.push_back({ i, x });
	}
	for (int i = y - 1; i >= 0; --i)
	{
		if (Board[i][x] != nullptr) {
			if (Board[i][x]->get_color() != color)vec.push_back({ i, x });
			break;
		}
		vec.push_back({ i, x });
	}
	for (int i = x + 1; i < 8; ++i)
	{
		if (Board[y][i] != nullptr) {
			if (Board[y][i]->get_color() != color)vec.push_back({ y, i });
			break;
		}
		vec.push_back({ y, i });
	}
	for (int i = x - 1; i >= 0; --i)
	{
		if (Board[y][i] != nullptr) {
			if (Board[y][i]->get_color() != color)vec.push_back({ y, i });
			break;
		}
		vec.push_back({ y, i });
	}


	return vec;
}
vector<Point> knight::squares_attacking() {
	vector<Point> vec, ans;
	vec.push_back({ y - 1, x - 2 });
	vec.push_back({ y - 1, x + 2 });
	vec.push_back({ y + 1, x - 2 });
	vec.push_back({ y + 1, x + 2 });
	vec.push_back({ y - 2, x - 1 });
	vec.push_back({ y - 2, x + 1 });
	vec.push_back({ y + 2, x - 1 });
	vec.push_back({ y + 2, x + 1 });
	for (int i = 0; i < vec.size(); ++i)
		if ((vec[i].y >= 0 && vec[i].y < 8 && vec[i].x >= 0 && vec[i].x < 8) && (Board[vec[i].y][vec[i].x] == nullptr || Board[vec[i].y][vec[i].x]->get_color() != color))ans.push_back(vec[i]);
	return ans;

}
vector<Point> bishop::squares_attacking() {
	vector<Point> vec;
	for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; --i, --j)
	{
		if (Board[j][i] != nullptr) {
			if (Board[j][i]->get_color() != color)vec.push_back({ j, i });
			break;
		}
		vec.push_back({ j, i });
	}

	for (int i = x + 1, j = y + 1; i < 8 && j < 8; ++i, ++j)
	{
		if (Board[j][i] != nullptr) {
			if (Board[j][i]->get_color() != color)vec.push_back({ j, i });
			break;
		}
		vec.push_back({ j, i });
	}

	for (int i = x + 1, j = y - 1; i < 8 && j >= 0; ++i, --j)
	{
		if (Board[j][i] != nullptr) {
			if (Board[j][i]->get_color() != color)vec.push_back({ j, i });
			break;
		}
		vec.push_back({ j, i });
	}
	for (int i = x - 1, j = y + 1; i >= 0 && j < 8; --i, ++j)
	{
		if (Board[j][i] != nullptr) {
			if (Board[j][i]->get_color() != color)vec.push_back({ j, i });
			break;
		}
		vec.push_back({ j, i });
	}
	return vec;
}

piece* Board[8][8];
database<pawn> pawns;
database<rook> rooks;
database<knight> knights;
database<bishop> bishops;
database<queen> queens;
database<king> kings;
void create(int y, int x, piece_type type, Color color)
{
	if (type == PAWN) {
		pawn piece(x, y, color);
		pawns.push_back(piece);
		Board[y][x] = &pawns[pawns.size() - 1];
	}
	else if (type == ROOK) {
		rook piece(x, y, color);
		rooks.push_back(piece);
		Board[y][x] = &rooks[rooks.size() - 1];
	}
	else if (type == KNIGHT) {
		knight piece(x, y, color);
		knights.push_back(piece);
		Board[y][x] = &knights[knights.size() - 1];
	}
	else if (type == BISHOP) {
		bishop piece(x, y, color);
		bishops.push_back(piece);
		Board[y][x] = &bishops[bishops.size() - 1];
	}
	else if (type == QUEEN) {
		queen piece(x, y, color);
		queens.push_back(piece);
		Board[y][x] = &queens[queens.size() - 1];
	}
	else if (type == KING) {
		king piece(x, y, color);
		kings.push_back(piece);
		Board[y][x] = &kings[kings.size() - 1];
	}
}
void erase(int y, int x) {
	Board[y][x] = nullptr;
}
void Castling(Point king, Point rook)
{
	int x1 = rook.x, y1 = rook.y, x2 = king.x;
	if (x1 == 0)
	{
		Board[y1][x1]->set_position({ y1, 3 });
		Board[y1][x2]->set_position({ y1, 2 });
		Board[y1][2] = Board[y1][x2];
		Board[y1][3] = Board[y1][x1];

	}
	else {
		Board[y1][x1]->set_position({ y1, 5 });
		Board[y1][x2]->set_position({ y1, 6 });
		Board[y1][6] = Board[y1][x2];
		Board[y1][5] = Board[y1][x1];
	}
	Board[y1][x1] = nullptr;
	Board[y1][x2] = nullptr;
}
