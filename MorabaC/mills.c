#include "stdafx.h"

void init_Mill(struct Coords ** mill, struct Coords *c1, struct Coords *c2, struct Coords *c3) {

	mill[0] = c1;
	mill[1] = c2;
	mill[2] = c3;

}
void setUpMills() {
	//Allocate space for the mill then initialize its data
	AA17 = (struct Coords**) malloc(sizeof(struct Coords*) * 3);
	init_Mill(AA17, &A1, &A4, &A7);

	BB26 = (struct Coords**) malloc(sizeof(struct Coords*) * 3);
	init_Mill(BB26, &B2, &B4, &B6);

	CC35 = (struct Coords**) malloc(sizeof(struct Coords*) * 3);
	init_Mill(CC35, &C3, &C4, &C5);

	DD13 = (struct Coords**) malloc(sizeof(struct Coords*) * 3);
	init_Mill(DD13, &D1, &D2, &D3);

	DD57 = (struct Coords**) malloc(sizeof(struct Coords) * 3);
	init_Mill(DD57, &D5, &D6, &D7);

	EE35 = (struct Coords**) malloc(sizeof(struct Coords) * 3);
	init_Mill(EE35, &E3, &E4, &E5);

	FF26 = (struct Coords**) malloc(sizeof(struct Coords) * 3);
	init_Mill(FF26, &F2, &F4, &F6);

	GG17 = (struct Coords**)malloc(sizeof(struct Coords) * 3);
	init_Mill(GG17, &G1, &G4, &G7);

	AG11 = (struct Coords**) malloc(sizeof(struct Coords) * 3);
	init_Mill(AG11, &A1, &D1, &G1);

	BF22 = (struct Coords**) malloc(sizeof(struct Coords) * 3);
	init_Mill(BF22, &B2, &D2, &F2);

	CE33 = (struct Coords**) malloc(sizeof(struct Coords) * 3);
	init_Mill(CE33, &C3, &D3, &E3);

	AC44 = (struct Coords**) malloc(sizeof(struct Coords) * 3);
	init_Mill(AC44, &A4, &B4, &C4);

	EG44 = (struct Coords**) malloc(sizeof(struct Coords) * 3);
	init_Mill(EG44, &E4, &F4, &G4);

	CE55 = (struct Coords**) malloc(sizeof(struct Coords) * 3);
	init_Mill(CE55, &C5, &D5, &E5);

	BF66 = (struct Coords**) malloc(sizeof(struct Coords) * 3);
	init_Mill(BF66, &B6, &D6, &F6);

	AG77 = (struct Coords**) malloc(sizeof(struct Coords) * 3);
	init_Mill(AG77, &A7, &D7, &G7);

	AC13 = (struct Coords**) malloc(sizeof(struct Coords) * 3);
	init_Mill(AC13, &A1, &B2, &C3);

	CA57 = (struct Coords**) malloc(sizeof(struct Coords) * 3);
	init_Mill(CA57, &C5, &B6, &A7);

	GE13 = (struct Coords**) malloc(sizeof(struct Coords) * 3);
	init_Mill(GE13, &G1, &F2, &E3);

	EG57 = (struct Coords**) malloc(sizeof(struct Coords) * 3);
	init_Mill(EG57, &E5, &F6, &G7);



}
void createMills() {
	//all coordinate combinations that can form a mill addItem(allBoardMills,if all are occupied by the same player)

	allBoardMills = (List*)malloc(sizeof(List) * 20);
	initList(allBoardMills);


	addItem(allBoardMills, *AA17);
	addItem(allBoardMills, *BB26);
	addItem(allBoardMills, *CC35);

	addItem(allBoardMills, *DD13);
	addItem(allBoardMills, *DD57);
	addItem(allBoardMills, *EE35);

	addItem(allBoardMills, *FF26);
	addItem(allBoardMills, *GG17);
	addItem(allBoardMills, *AG11);

	addItem(allBoardMills, *BF22);
	addItem(allBoardMills, *CE33);
	addItem(allBoardMills, *AC44);

	addItem(allBoardMills, *EG44);
	addItem(allBoardMills, *CE55);
	addItem(allBoardMills, *BF66);

	addItem(allBoardMills, *AG77);
	addItem(allBoardMills, *AC13);
	addItem(allBoardMills, *CA57);

	addItem(allBoardMills, *GE13);
	addItem(allBoardMills, *EG57);

	/*struct Coords *cor =getElementAt(allBoardMills,0);
	//cor;
	printf("Char: (%c,%d)\n",cor[2].pos.let,cor[2].pos.num);
	A1.symbol='B';
	printf("Char: %c \n",getElementAt(allBoardMills,0)->symbol);*/

}

