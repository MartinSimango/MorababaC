#include "stdafx.h"

Tuple makeTuple(char let, int num) {

	Tuple tuple = (Tuple)malloc(sizeof(struct Point));
	tuple->let = let;
	tuple->num = num;
	return tuple;

}

void init_Point(struct Point *point, char let, int num) {

	point->let = let;
	point->num = num;

}

void init_Coord(struct Coords * coord, char let, int num, char symbol, Tuple p1, Tuple p2, Tuple p3, Tuple p4) {

	coord->symbol = symbol;
	init_Point(&(coord->pos), let, num);

	coord->possibleMoves = (struct Point*) malloc(4 * sizeof(struct Point));
	coord->possibleMoves[0] = *p1;
	coord->possibleMoves[1] = *p2;
	coord->possibleMoves[2] = *p3;

	free(p1);
	free(p2);  //free the memory that was allocated
	free(p3);

	if (p4 != 0) {

		coord->possibleMoves[3] = *p4; //check if p4 is null
		free(p4);

	}
	else
	{
		Tuple invalidPoint = makeTuple('_', -1);
		coord->possibleMoves[3] = *invalidPoint;//make an invalid coord
		free(invalidPoint);

	}



}