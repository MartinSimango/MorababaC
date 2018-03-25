#include "stdafx.h"

POINT_PTR 
Point__create(char let, int num) {
	
    POINT_PTR point = (POINT_PTR)malloc(sizeof(POINT));
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

	
    coord->possibleMoves = (POINT_PTR) malloc(4 * sizeof(POINT));
	coord->possibleMoves[0] = *possible_1;
	coord->possibleMoves[1] = *possible_2;
	coord->possibleMoves[2] = *possible_3;
	
    free(possible_1);
	free(possible_2);  //free the memory that was allocated
	free(possible_3);
	
    if (possible_4 != 0) {
		
        coord->possibleMoves[3] = *possible_4; //check if p4 is null
		free(possible_4);

	}
	else 
    {
		POINT_PTR invalidPoint = Point__create('_', -1);
		coord->possibleMoves[3] = *invalidPoint;//make an invalid coord
		free(invalidPoint);

	}
   
}
int Coords__isEqual(COORD data, COORD dataToBeCompared) {
	
	return data.pos.let == dataToBeCompared.pos.let &&
		   data.pos.num == dataToBeCompared.pos.num &&
		   data.symbol == dataToBeCompared.symbol;

}