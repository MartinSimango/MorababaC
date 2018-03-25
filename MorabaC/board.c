#include "stdafx.h" 
void init__startBoard(GAMEBOARD *gameBoard) {
	
	POINT_PTR(*T)(char, int) = Point__create;

	Coord__create(&gameBoard->A1, 'A', 1, ' ', T('A', 4), T('B', 2), T('D', 1), 0);
	Coord__create(&gameBoard->A4, 'A', 4, ' ', T('A', 1), T('A', 7), T('B', 4), 0);
	Coord__create(&gameBoard->A7, 'A', 7, ' ', T('A', 4), T('B', 6), T('D', 7), 0);

	Coord__create(&gameBoard->B2, 'B', 2, ' ', T('A', 1), T('B', 4), T('C', 3), T('D', 2));
	Coord__create(&gameBoard->B4, 'B', 4, ' ', T('A', 4), T('B', 2), T('B', 6), T('C', 4));
	Coord__create(&gameBoard->B6, 'B', 6, ' ', T('A', 7), T('B', 4), T('D', 6), T('C', 5));

	Coord__create(&gameBoard->C3, 'C', 3, ' ', T('B', 2), T('C', 4), T('D', 3), 0);
	Coord__create(&gameBoard->C4, 'C', 4, ' ', T('B', 4), T('C', 3), T('C', 5), 0);
	Coord__create(&gameBoard->C5, 'C', 5, ' ', T('B', 6), T('C', 4), T('D', 5), 0);

	Coord__create(&gameBoard->D1, 'D', 1, ' ', T('A', 1), T('D', 2), T('G', 1), 0);
	Coord__create(&gameBoard->D2, 'D', 2, ' ', T('B', 2), T('D', 1), T('D', 3), T('F', 2));
	Coord__create(&gameBoard->D3, 'D', 3, ' ', T('C', 3), T('D', 2), T('E', 3), 0);

	Coord__create(&gameBoard->D5, 'D', 5, ' ', T('C', 5), T('D', 6), T('E', 5), 0);
	Coord__create(&gameBoard->D6, 'D', 6, ' ', T('B', 6), T('D', 5), T('D', 7), T('F', 6));
	Coord__create(&gameBoard->D7, 'D', 7, ' ', T('A', 7), T('D', 6), T('G', 7), 0);


	Coord__create(&gameBoard->E3, 'E', 3, ' ', T('D', 3), T('F', 2), T('E', 4), 0);
	Coord__create(&gameBoard->E4, 'E', 4, ' ', T('E', 3), T('F', 4), T('E', 5), 0);
	Coord__create(&gameBoard->E5, 'E', 5, ' ', T('D', 5), T('E', 4), T('F', 6), 0);

	Coord__create(&gameBoard->F2, 'F', 2, ' ', T('D', 2), T('E', 3), T('F', 4), T('G', 1));
	Coord__create(&gameBoard->F4, 'F', 4, ' ', T('E', 4), T('F', 2), T('F', 6), T('G', 4));
	Coord__create(&gameBoard->F6, 'F', 6, ' ', T('D', 6), T('E', 5), T('F', 4), T('G', 7));


	Coord__create(&gameBoard->G1, 'G', 1, ' ', T('D', 1), T('F', 2), T('G', 4), 0);
	Coord__create(&gameBoard->G4, 'G', 4, ' ', T('F', 4), T('G', 1), T('G', 7), 0);
	Coord__create(&gameBoard->G7, 'G', 7, ' ', T('D', 7), T('F', 6), T('G', 4), 0);


}

