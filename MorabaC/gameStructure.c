#include "stdafx.h"

POINT_PTR 
Point__create(char let, int num) {
	
    POINT_PTR point = (POINT_PTR)malloc(sizeof(POINT_));
	point->let = let;
	point->num = num;
	return point;
    
}


void
Coord__create(COORD_PTR coord,char let,int num,char symbol,POINT_PTR possible_1, POINT_PTR possible_2, 
			 		    POINT_PTR possible_3, POINT_PTR possible_4){
	
	//COORD_PTR coord= (COORD_PTR) malloc (sizeof(COORD));
	coord->symbol = symbol;
	coord->pos.let = let;
	coord->pos.num=num;

	
    coord->possibleMoves = (POINT_PTR) malloc(4 * sizeof(POINT_));
	coord->possibleMoves[0] = *possible_1;
	coord->possibleMoves[1] = *possible_2;
	coord->possibleMoves[2] = *possible_3;
	
 
	
    if (possible_4 != 0) {
		
        coord->possibleMoves[3] = *possible_4; //check if p4 is null
	

	}
	else 
    {
		POINT_PTR invalidPoint = Point__create('_', -1);
		coord->possibleMoves[3] = *invalidPoint;//make an invalid coord
		free(invalidPoint);

	}
   
}
int Coords__isEqual(COORD_ data, COORD_ dataToBeCompared) {
	
	return data.pos.let == dataToBeCompared.pos.let &&
		   data.pos.num == dataToBeCompared.pos.num &&
		   data.symbol == dataToBeCompared.symbol;

}

COORD_PTR Coord__FromCoord(COORD_PTR coord) {
	COORD_PTR returnCoord= malloc(sizeof(COORD_));
	Coord__create(returnCoord, coord->pos.let, coord->pos.num, coord->symbol, &(coord->possibleMoves[0]),
	&(coord->possibleMoves[1]), &(coord->possibleMoves[2]),( &coord->possibleMoves[3]));

	/*returnCoord->possibleMoves = (POINT_PTR) malloc(4 * sizeof(POINT_));
	for (int i = 0; i < 4; i++) {
		returnCoord->possibleMoves[i].let = coord->possibleMoves[i].let;
		returnCoord->possibleMoves[i].num = coord->possibleMoves[i].num;
	}*/

	return returnCoord;
}

GAMEBOARD * Gameboard__FromGameboard(GAMEBOARD * gameBoard) {
	GAMEBOARD * newGameBoard = malloc(sizeof(GAMEBOARD));

	newGameBoard->A1=  *Coord__FromCoord(&(gameBoard->A1));
	newGameBoard->A4 = *Coord__FromCoord(&(gameBoard->A4));
	newGameBoard->A7 = *Coord__FromCoord(&(gameBoard->A7));
	
	newGameBoard->B2 = *Coord__FromCoord(&(gameBoard->B2));
	newGameBoard->B4 = *Coord__FromCoord(&(gameBoard->B4));
	newGameBoard->B6 = *Coord__FromCoord(&(gameBoard->B6));
	
	newGameBoard->C3 = *Coord__FromCoord(&(gameBoard->C3));
	newGameBoard->C4 = *Coord__FromCoord(&(gameBoard->C4));
	newGameBoard->C5 = *Coord__FromCoord(&(gameBoard->C5));
	
	newGameBoard->D1 = *Coord__FromCoord(&(gameBoard->D1));
	newGameBoard->D2 = *Coord__FromCoord(&(gameBoard->D2));
	newGameBoard->D3 = *Coord__FromCoord(&(gameBoard->D3));
	newGameBoard->D5 = *Coord__FromCoord(&(gameBoard->D5));
	newGameBoard->D6 = *Coord__FromCoord(&(gameBoard->D6));
	newGameBoard->D7 = *Coord__FromCoord(&(gameBoard->D7));
	
	newGameBoard->E3 = *Coord__FromCoord(&(gameBoard->E3));
	newGameBoard->E4 = *Coord__FromCoord(&(gameBoard->E4));
	newGameBoard->E5 = *Coord__FromCoord(&(gameBoard->E5));
	
	newGameBoard->F2 = *Coord__FromCoord(&(gameBoard->F2));
	newGameBoard->F4 = *Coord__FromCoord(&(gameBoard->F4));
	newGameBoard->F6 = *Coord__FromCoord(&(gameBoard->F6));
	
	newGameBoard->G1 = *Coord__FromCoord(&(gameBoard->G1));
	newGameBoard->G4 = *Coord__FromCoord(&(gameBoard->G4));
	newGameBoard->G7 = *Coord__FromCoord(&(gameBoard->G7));

	
	return newGameBoard;
}
