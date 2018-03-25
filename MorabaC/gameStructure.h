

#pragma once


#define COORDNUM 24
#define COORD_MAXPOSSIBLEMOVES 4
struct Point {

	char let;
	int num;

};
typedef struct Point POINT_;
typedef struct Point * POINT_PTR;

struct Coords {

	POINT_ pos;
	char symbol;
	POINT_PTR possibleMoves;
	int possibleMovesNum;

};

typedef struct Coords COORD_;	
typedef struct Coords * COORD_PTR;
typedef struct Coords ** MILLS;

struct GameBoard {
	
	COORD_								//all the coords on the board;
		A1, A4, A7, B2, B4, B6, C3, C4, C5, D1, 
		D2, D3, D5, D6, D7, E3, E4, E5, F2, F4, F6, 
		G1, G4, G7;                             
	   
	MILLS
	   AA17, BB26, CC35, DD13, DD57, EE35, FF26, 
	   GG17, AG11, BF22, CE33, AC44, EG44, CE55,
	   BF66, AG77, AC13, CA57, GE13, EG57; //list of all possible mill combinations

};

typedef struct GameBoard GAMEBOARD;

//return a point pointer given a let and a number for that point
POINT_PTR Point__create(char let, int num);

//create a point
//void POINT__create(POINT_PTR point, char let, int num);

//create a coord with p1 p2,p3,p4 being the possibles moves where you can move to
//and point being the actual point you are creating the coord for
void Coord__create(COORD_PTR coord,char let,int num,char symbol,POINT_PTR possible_1, POINT_PTR possible_2, 
			 		    POINT_PTR possible_3, POINT_PTR possible_4);

int Coords__isEqual(COORD_ data, COORD_ dataToBeCompared);



