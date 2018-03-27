// Moraba.cpp : Defines the entry point for the console application.
//ab

#include "stdafx.h"


#if defined(__APPLE__) || defined(__unix__)                   /* __unix__ is usually defined by compilers targeting Unix systems */	
struct termios initialSettings;
struct termios newSettings;

void setTerminalSettings() {
	tcgetattr(fileno(stdin), &initialSettings);

	newSettings = initialSettings;
	newSettings.c_lflag &= ~ICANON;
	newSettings.c_cc[VTIME] = 0;
	newSettings.c_cc[VMIN] = 1;

	tcsetattr(fileno(stdin), TCSAFLUSH, &newSettings);
}
void resetTerminalSettings() {
	tcsetattr(fileno(stdin), TCSAFLUSH, &initialSettings);
}
#endif


#define MAX_STAGES 5


int CURRENT_DEPTH = 0;
enum BACKINGSTAGE { NOT_BACKING=0, BACKING = 1,LEFTBACKING} BACKINGSTATE;
int DEPTH_REACHED=0;

int changeGameStage(const POINT_ point) {

	if (point.num-1 < 0 || point.num-1 >=DEPTH_REACHED) {
		
		printf("Can't go back to stage %d! Only %d stage(s) available\n", point.num,DEPTH_REACHED);
		return 0;
	}
	else {
		CURRENT_DEPTH = point.num-1; //changed the depth

		return 1;
	}

	return 0;
}
POINT_ getPos(char * what) {

	POINT_ retPoint;

	int valid = 0;
	char c=' ';

	while (!valid) {

		printf("%s\n", what);
		printf("Row: ");

	#if defined(__APPLE__) || defined(__unix__)

			scanf("%c", &c);

	#elif defined(_WIN32) || defined(WIN32)

			c = _getch();
			printf("%c", c);

	#endif

			retPoint.let = toupper(c);
			printf("\nColumn: ");

	#if defined(__APPLE__) || defined(__unix__)

			scanf("%c", &c);

	#elif defined(_WIN32) || defined(WIN32)

			c = _getch();
			printf("%c", c);

#endif

		int num = atoi(&c); //check if input is invalid

		if (num == 0)
			printf("\nRow must be character and column must be number from 1-9!\n");
		else
		{
			retPoint.num = num;
			valid = 1;
		}
	}
	printf("\n");

	return retPoint;
}

void shift(GAME **Morabaraba) {
	for (int i = 0; i < DEPTH_REACHED; i++) {
		Morabaraba[i] = Game__FromGame(Morabaraba[i + 1]);
	}
	//Morabaraba[0] stays Morabaraba[0]

}

void getPlayerMove(GAME *Morabaraba,POINT_PTR fromPoint, POINT_PTR toPoint, PLAYER * player) { //struct Coords* availableBoard

	POINT_ tempPoint;
	char askString[255];
	switch (player->playerState) {
	case PLACING:

		#if defined(__APPLE__) || defined(__unix__)
			sprintf(askString, "%s's turn\nWhere do you want to place the cow?", player->name);
        #elif defined(_WIN32) || defined(WIN32)
			sprintf_s(askString,sizeof(askString), "%s's turn\nWhere do you want to place the cow?", player->name);
		#endif

		tempPoint = getPos(askString); //get the input
		if (tempPoint.let == '#') {
			
			if (changeGameStage(tempPoint)) {

				BACKINGSTATE = BACKING;
				return;
			}
			return getPlayerMove(Morabaraba, fromPoint, toPoint, player);
			
		}
	
	
	//	BACKINGSTATE = NOT_BACKING; //move has been made no longer backing
		if (Game__IsValidPlace(Morabaraba,tempPoint))
		{
			toPoint->let = tempPoint.let;
			toPoint->num = tempPoint.num;

			BACKINGSTATE = NOT_BACKING; //move has been made no longer backing

		}
		else
		{
			printf("(%c,%d) is not a valid move\n", tempPoint.let, tempPoint.num);
			getPlayerMove(Morabaraba,fromPoint, toPoint, player);
		}
		break;

	case MOVING:

		#if defined(__APPLE__) || defined(__unix__)
			sprintf(askString, "%s's turn\nWhere do you want to move the cow from?", player->name);
		#elif defined(_WIN32) || defined(WIN32)
			sprintf_s(askString, sizeof(askString), "%s's turn\nWhere do you want to move the cow from?", player->name);
		#endif

		tempPoint = getPos(askString);

		if (Game__IsValidFrom(Morabaraba,tempPoint, player))
		{
			fromPoint->let = tempPoint.let;
			fromPoint->num = tempPoint.num;
			
			#if defined(__APPLE__) || defined(__unix__)
				sprintf(askString, "Where do you want to move the cow to?");
			#elif defined(_WIN32) || defined(WIN32)
				sprintf_s(askString, sizeof(askString), "%s's turn\nWhere do you want to move the cow to?", player->name);
			#endif
			
				tempPoint = getPos(askString);

			if (Game__IsValidTo(Morabaraba,tempPoint, player))
			{
				toPoint->let = tempPoint.let;
				toPoint->num = tempPoint.num;
			}
			else
			{
				printf("You cannot move from (%c,%d) to (%c,%d)\n", fromPoint->let, fromPoint->num, tempPoint.let, tempPoint.num);
				getPlayerMove(Morabaraba,fromPoint, toPoint, player);
			}

		}
		else {

			printf("You have no cow at (%c,%d)\n", tempPoint.let, tempPoint.num);
			getPlayerMove(Morabaraba,fromPoint, toPoint, player);

		}
		break;
	case FLYING:

		break;
	}


}


void runGame(GAME **Morabaraba) {
#if defined(__APPLE__) || defined(__unix__) 
	system("clear");
#elif defined(_WIN32) || defined(WIN32)
	//system("@cls");
#endif

	
	if (DEPTH_REACHED < (MAX_STAGES - 1) && BACKINGSTATE==NOT_BACKING) { //set up stages
		Morabaraba[DEPTH_REACHED + 1] = Game__FromGame(Morabaraba[DEPTH_REACHED]);
		DEPTH_REACHED += 1;


	}
	else if (BACKINGSTATE == NOT_BACKING)
	{
		shift(Morabaraba);
	}

	printf("Stage: %d/%d\n", (CURRENT_DEPTH + 1), (DEPTH_REACHED ));
	Game__PrintBoard(Morabaraba[CURRENT_DEPTH]);


	

	POINT_ toPoint, fromPoint;
	if (BACKINGSTATE==NOT_BACKING) {
		getPlayerMove(Morabaraba[CURRENT_DEPTH + 1], &fromPoint, &toPoint, (Morabaraba[CURRENT_DEPTH + 1])->currentPlayer); //fromPoint and toPoint returned must be valid
	}
	else {
	//	printf("%d sdfdfdf: \n", CURRENT_DEPTH);
		getPlayerMove(Morabaraba[CURRENT_DEPTH ], &fromPoint, &toPoint, (Morabaraba[CURRENT_DEPTH ])->currentPlayer); //fromPoint and toPoint returned must be valid
	//	if (BACKING == NOT_BACKING) {
			CURRENT_DEPTH -= 1;
	//	}
	}

	if (BACKINGSTATE == BACKING) {
			printf("GOING BACK TO STAGE %d!\n", (CURRENT_DEPTH+1));
		    //Morabaraba[CURRENT_DEPTH + 1] = Game__FromGame(Morabaraba[CURRENT_DEPTH]);
			
			return runGame(Morabaraba);
	}
//	if (DEPTH_REACHED < (MAX_STAGES - 1)) {
	//	CURRENT_DEPTH += 1;
	//}
//	printf("update:  %c\n", Morabaraba[0]->gameBoard.A1.symbol);
	Game__UpdatePlayer(Morabaraba[CURRENT_DEPTH+1], &fromPoint, &toPoint, (Morabaraba[CURRENT_DEPTH+1])->currentPlayer);
	if(CURRENT_DEPTH<DEPTH_REACHED)
		CURRENT_DEPTH += 1;
	//struct Coords * playerMills = GameGetPlayerMills(p1);
	//printf("update:  %c\n", Morabaraba[0]->gameBoard.A1.symbol);

	DEPTH_REACHED = CURRENT_DEPTH;
	
	


	runGame(Morabaraba);

}

void startGame() {
	
	GAME **Morabaraba= malloc(sizeof(GAME*)*5); //to keep track of game states 
	for (int i = 0; i < 5; i++) {
		
		Morabaraba[i] = malloc(sizeof(GAME));
	
	}
	
	init__Game(*Morabaraba,"Player 1","Player 2");
	BACKINGSTATE = NOT_BACKING;
	runGame(Morabaraba);

}


int main() {
#if defined(__APPLE__) || defined(__unix__)
	setTerminalSettings();
#endif

	startGame();

#if defined(__APPLE__) || defined(__unix__)
	resetTerminalSettings();
#elif defined(_WIN32) || defined(WIN32)
	_getch();
#endif
}
