#ifndef LOGIC_H
#define LOGIC_H
#include "chess_pieces.h"
extern int now_transformating;// 0 - no, 1 - black, 2 - white
extern piece* choosen;
Point getElPassant();
inline int abs(int x);
bool IsElPassantLegal(piece* ptr);
bool IsMoveLegal(Point p1, Point p2);
void logic();
#endif LOGIC_H
