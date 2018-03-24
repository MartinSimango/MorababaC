#pragma once


#define CoordNum 24
struct Point {
	char let;
	int num;
};
typedef struct Point * Tuple;



struct Coords {
	struct Point pos;
	char symbol;
	struct Point * possibleMoves;
	int possibleMovesNum;
}A1, A4, A7, B2, B4, B6, C3, C4, C5, D1, D2, D3, D5, D6, D7, E3, E4, E5, F2, F4, F6, G1, G4, G7,
**AA17, **BB26, **CC35, **DD13, **DD57, **EE35, **FF26, **GG17, **AG11, **BF22, **CE33, **AC44, **EG44,
**CE55, **BF66, **AG77, **AC13, **CA57, **GE13, **EG57; //list of all possible mill combinations


														//BOARD
Tuple makeTuple(char let, int num);

void init_Point(struct Point *point, char let, int num);
void init_Coord(struct Coords * coord, char let, int num, char symbol, Tuple p1, Tuple p2, Tuple p3, Tuple p4);



