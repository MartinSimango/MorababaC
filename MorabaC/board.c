#include "stdafx.h"
void setUpStartBoard() {

	Tuple(*T)(char, int) = makeTuple;

	init_Coord(&A1, 'A', 1, ' ', T('A', 4), T('B', 2), T('D', 1), 0);
	init_Coord(&A4, 'A', 4, ' ', T('A', 1), T('A', 7), T('B', 4), 0);
	init_Coord(&A7, 'A', 7, ' ', T('A', 4), T('B', 6), T('D', 7), 0);

	init_Coord(&B2, 'B', 2, ' ', T('A', 1), T('B', 4), T('C', 3), T('D', 2));
	init_Coord(&B4, 'B', 4, ' ', T('A', 4), T('B', 2), T('B', 6), T('C', 4));
	init_Coord(&B6, 'B', 6, ' ', T('A', 7), T('B', 4), T('D', 6), T('C', 5));

	init_Coord(&C3, 'C', 3, ' ', T('B', 2), T('C', 4), T('D', 3), 0);
	init_Coord(&C4, 'C', 4, ' ', T('B', 4), T('C', 3), T('C', 5), 0);
	init_Coord(&C5, 'C', 5, ' ', T('B', 6), T('C', 4), T('D', 5), 0);

	init_Coord(&D1, 'D', 1, ' ', T('A', 1), T('D', 2), T('G', 1), 0);
	init_Coord(&D2, 'D', 2, ' ', T('B', 2), T('D', 1), T('D', 3), T('F', 2));
	init_Coord(&D3, 'D', 3, ' ', T('C', 3), T('D', 2), T('E', 3), 0);

	init_Coord(&D5, 'D', 5, ' ', T('C', 5), T('D', 6), T('E', 5), 0);
	init_Coord(&D6, 'D', 6, ' ', T('B', 6), T('D', 5), T('D', 7), T('F', 6));
	init_Coord(&D7, 'D', 7, ' ', T('A', 7), T('D', 6), T('G', 7), 0);


	init_Coord(&E3, 'E', 3, ' ', T('D', 3), T('F', 2), T('E', 4), 0);
	init_Coord(&E4, 'E', 4, ' ', T('E', 3), T('F', 4), T('E', 5), 0);
	init_Coord(&E5, 'E', 5, ' ', T('D', 5), T('E', 4), T('F', 6), 0);

	init_Coord(&F2, 'F', 2, ' ', T('D', 2), T('E', 3), T('F', 4), T('G', 1));
	init_Coord(&F4, 'F', 4, ' ', T('E', 4), T('F', 2), T('F', 6), T('G', 4));
	init_Coord(&F6, 'F', 6, ' ', T('D', 6), T('E', 5), T('F', 4), T('G', 7));


	init_Coord(&G1, 'G', 1, ' ', T('D', 1), T('F', 2), T('G', 4), 0);
	init_Coord(&G4, 'G', 4, ' ', T('F', 4), T('G', 1), T('G', 7), 0);
	init_Coord(&G7, 'G', 7, ' ', T('D', 7), T('F', 6), T('G', 4), 0);


}

void createStartBoard() {

	initList(&startBoard);

	addItem(&startBoard, &A1);
	addItem(&startBoard, &A4);
	addItem(&startBoard, &A7);

	addItem(&startBoard, &B2);
	addItem(&startBoard, &B4);
	addItem(&startBoard, &B6);

	addItem(&startBoard, &C3);
	addItem(&startBoard, &C4);
	addItem(&startBoard, &C5);

	addItem(&startBoard, &D1);
	addItem(&startBoard, &D2);
	addItem(&startBoard, &D3);
	addItem(&startBoard, &D5);
	addItem(&startBoard, &D6);
	addItem(&startBoard, &D7);

	addItem(&startBoard, &E3);
	addItem(&startBoard, &E4);
	addItem(&startBoard, &E5);

	addItem(&startBoard, &F2);
	addItem(&startBoard, &F4);
	addItem(&startBoard, &F6);

	addItem(&startBoard, &G1);
	addItem(&startBoard, &G4);
	addItem(&startBoard, &G7);
}