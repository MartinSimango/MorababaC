#include "stdafx.h"

void init__Mill(MILLS mill, COORD_PTR c1, COORD_PTR c2, COORD_PTR c3) {

	mill[0] = c1;
	mill[1] = c2;
	mill[2] = c3;

}
void init__Mills(GAMEBOARD *gameBoard){
	//Allocate space for the mill then initialize its data
	gameBoard->AA17 = (MILLS) malloc(sizeof(COORD_PTR) * 3);
	init__Mill(gameBoard->AA17, &(gameBoard->A1), &(gameBoard->A4), &(gameBoard->A7));

	gameBoard->BB26 = (MILLS) malloc(sizeof(COORD_PTR) * 3);
	init__Mill(gameBoard->BB26, &(gameBoard->B2), &(gameBoard->B4), &(gameBoard->B6));

	gameBoard->CC35 = (MILLS) malloc(sizeof(COORD_PTR) * 3);
	init__Mill(gameBoard->CC35, &(gameBoard->C3), &(gameBoard->C4), &(gameBoard->C5));

	gameBoard->DD13 = (MILLS) malloc(sizeof(COORD_PTR) * 3);
	init__Mill(gameBoard->DD13, &(gameBoard->D1), &(gameBoard->D2), &(gameBoard->D3));

	gameBoard->DD57 = (MILLS) malloc(sizeof(COORD_PTR) * 3);
	init__Mill(gameBoard->DD57, &(gameBoard->D5), &(gameBoard->D6), &(gameBoard->D7));

	gameBoard->EE35 = (MILLS) malloc(sizeof(COORD_PTR) * 3);
	init__Mill(gameBoard->EE35, &(gameBoard->E3), &(gameBoard->E4), &(gameBoard->E5));

	gameBoard->FF26 = (MILLS) malloc(sizeof(COORD_PTR) * 3);
	init__Mill(gameBoard->FF26, &(gameBoard->F2), &(gameBoard->F4), &(gameBoard->F6));

	gameBoard->GG17 = (MILLS)malloc(sizeof(COORD_PTR) * 3);
	init__Mill(gameBoard->GG17, &(gameBoard->G1), &(gameBoard->G4), &(gameBoard->G7));

	gameBoard->AG11 = (MILLS) malloc(sizeof(COORD_PTR) * 3);
	init__Mill(gameBoard->AG11, &(gameBoard->A1), &(gameBoard->D1), &(gameBoard->G1));

	gameBoard->BF22 = (MILLS) malloc(sizeof(COORD_PTR) * 3);
	init__Mill(gameBoard->BF22, &(gameBoard->B2), &(gameBoard->D2), &(gameBoard->F2));

	gameBoard->CE33 = (MILLS) malloc(sizeof(COORD_PTR) * 3);
	init__Mill(gameBoard->CE33, &(gameBoard->C3), &(gameBoard->D3), &(gameBoard->E3));

	gameBoard->AC44 = (MILLS) malloc(sizeof(COORD_PTR) * 3);
	init__Mill(gameBoard->AC44, &(gameBoard->A4), &(gameBoard->B4), &(gameBoard->C4));

	gameBoard->EG44 = (MILLS) malloc(sizeof(COORD_PTR) * 3);
	init__Mill(gameBoard->EG44, &(gameBoard->E4), &(gameBoard->F4), &(gameBoard->G4));

	gameBoard->CE55 = (MILLS) malloc(sizeof(COORD_PTR) * 3);
	init__Mill(gameBoard->CE55, &(gameBoard->C5), &(gameBoard->D5), &(gameBoard->E5));

	gameBoard->BF66 = (MILLS) malloc(sizeof(COORD_PTR) * 3);
	init__Mill(gameBoard->BF66, &(gameBoard->B6), &(gameBoard->D6), &(gameBoard->F6));

	gameBoard->AG77 = (MILLS) malloc(sizeof(COORD_PTR) * 3);
	init__Mill(gameBoard->AG77, &(gameBoard->A7), &(gameBoard->D7), &(gameBoard->G7));

	gameBoard->AC13 = (MILLS) malloc(sizeof(COORD_PTR) * 3);
	init__Mill(gameBoard->AC13, &(gameBoard->A1), &(gameBoard->B2), &(gameBoard->C3));

	gameBoard->CA57 = (MILLS) malloc(sizeof(COORD_PTR) * 3);
	init__Mill(gameBoard->CA57, &(gameBoard->C5), &(gameBoard->B6), &(gameBoard->A7));

	gameBoard->GE13 = (MILLS) malloc(sizeof(COORD_PTR) * 3);
	init__Mill(gameBoard->GE13, &(gameBoard->G1), &(gameBoard->F2), &(gameBoard->E3));

	gameBoard->EG57 = (MILLS) malloc(sizeof(COORD_PTR) * 3);
	init__Mill(gameBoard->EG57, &(gameBoard->E5), &(gameBoard->F6), &(gameBoard->G7));



}

