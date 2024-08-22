#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H
#include <vector>
#include <iostream>
#include <raylib.h>
using namespace std;
struct Point {
	int y, x;
};
enum piece_type {
	PAWN,
	BISHOP,
	KNIGHT,
	ROOK,
	QUEEN,
	KING
};

bool operator==(Color& a, Color b);
bool operator!=(Color& a, Color& b);
bool operator!= (Point& p1, Point& p2);
bool operator== (Point& p1, Point& p2);
class piece {
protected:
	bool moved = 0;
	int x = 0, y = 0;
	piece_type type = PAWN;
	Color color = BLACK;
public:
	bool DidMove();
	void unmove();
	void move();
	virtual bool canCastle();
	void set_position(Point point);
	piece_type& get_type();
	Color& get_color();
	int get_x();
	int get_y();
	virtual std::vector<Point> squares_attacking();
	piece(int mX, int mY, Color mColor, piece_type type);
	piece(piece& Piece);
	piece();
	piece& operator= (const piece& P);
};
template <class T>
class database {
private:
	T arr[50];
	int sz = 0;
public:
	void push_back(T& piece);
	T& operator[] (int it);
	int size();
	database();
};
template <class T>
void database<T>::push_back(T& piece) {
	arr[sz++] = piece;
}
template <class T>
T& database<T>::operator[] (int it)
{
	return arr[it];
}
template <class T>
int database<T>::size()
{
	return sz;
}
template <class T>
database<T>::database() :sz(0) {}

class pawn : public piece {
public:
	pawn(int mX, int mY, Color mColor);
	pawn();
	std::vector<Point> squares_attacking() override;
};
class queen : public piece {
public:
	queen(int mX, int mY, Color mColor);
	queen();
	std::vector<Point> squares_attacking() override;
};
class king : public piece {
public:
	bool isMoved();
	king(int mX, int mY, Color mColor);
	king();
	std::vector<Point> squares_attacking() override;
};
class bishop : public piece {
public:
	bishop(int mX, int mY, Color mColor);
	bishop();
	std::vector<Point> squares_attacking() override;
};
class rook : public piece {
public:
	bool canCastle() override;
	rook(int mX, int mY, Color mColor);
	rook();
	std::vector<Point> squares_attacking() override;
};
class knight : public piece {
public:
	knight(int mX, int mY, Color mColor);
	knight();
	std::vector<Point> squares_attacking() override;
};
extern piece* Board[8][8];
extern database<pawn> pawns;
extern database<rook> rooks;
extern database<knight> knights;
extern database<bishop> bishops;
extern database<queen> queens;
extern database<king> kings;
void create(int y, int x, piece_type type, Color color);
void erase(int y, int x);
void Castling(Point king, Point rook);
#endif