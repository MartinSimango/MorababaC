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




struct Point getPos(char * what) {

	int valid = 0;
	struct Point retPoint;
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

#ifdef defined(__APPLE__) || defined(__unix__)

		scanf("%c", &c);

#elif defined(_WIN32) || defined(WIN32)

		c = _getch();
		printf("%c", c);

#endif

		int num = atoi(&c);

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

void getPlayerMove(struct Point * fromPoint, struct Point *toPoint, struct Player* player) { //struct Coords* availableBoard

	struct Point tempPoint;
	char askString[255];

	switch (player->playerState) {
	case PLACING:
		#if defined(__APPLE__) || defined(__unix__)
		
		sprintf(askString, "%s's turn\nWhere do you want to place the cow?", player->name);

        #elif defined(_WIN32) || defined(WIN32)
		sprintf_s(askString,sizeof(askString), "%s's turn\nWhere do you want to place the cow?", player->name);
		#endif
		tempPoint = getPos(askString);

		if (GameIsValidPlace(tempPoint))
		{
			toPoint->let = tempPoint.let;
			toPoint->num = tempPoint.num;
		}
		else
		{
			printf("(%c,%d) is not a valid move\n", tempPoint.let, tempPoint.num);
			getPlayerMove(fromPoint, toPoint, player);
		}
		break;

	case MOVING:
		#if defined(__APPLE__) || defined(__unix__)
		sprintf(askString, "%s's turn\nWhere do you want to move the cow from?", player->name);
		#elif defined(_WIN32) || defined(WIN32)
		sprintf_s(askString, sizeof(askString), "%s's turn\nWhere do you want to move the cow from?", player->name);
		#endif
		tempPoint = getPos(askString);

		if (GameIsValidFrom(tempPoint, player))
		{
			fromPoint->let = tempPoint.let;
			fromPoint->num = tempPoint.num;
			#if defined(__APPLE__) || defined(__unix__)
			sprintf(askString, "Where do you want to move the cow to?");
			#elif defined(_WIN32) || defined(WIN32)
			sprintf_s(askString, sizeof(askString), "%s's turn\nWhere do you want to move the cow to?", player->name);
			#endif
			tempPoint = getPos(askString);

			if (GameIsValidTo(tempPoint, player, player->playerState))
			{
				toPoint->let = tempPoint.let;
				toPoint->num = tempPoint.num;
			}
			else
			{
				printf("You cannot move from (%c,%d) to (%c,%d)\n", fromPoint->let, fromPoint->num, tempPoint.let, tempPoint.num);
				getPlayerMove(fromPoint, toPoint, player);
			}

		}
		else {

			printf("You have no cow at (%c,%d)\n", tempPoint.let, tempPoint.num);
			getPlayerMove(fromPoint, toPoint, player);

		}
		break;
	case FLYING:

		break;
	}


}

void runGame(struct Player *p1, struct Player *p2) {
	GamePrintBoard(p1->id);
	struct Point* toPoint = (struct Point*) malloc(sizeof(struct Point));
	struct Point* fromPoint = (struct Point*) malloc(sizeof(struct Point));
	getPlayerMove(fromPoint, toPoint, p1); //fromPoint and toPoint returned must be valid
 	GameUpdatePlayer(fromPoint, toPoint, p1); //update player after they have moved
	free(toPoint);
    free(fromPoint);
	struct Coords * playerMills = GameGetPlayerMills(p1);
	runGame(p2, p1);

}

void startGame() {
	setUpGame(); //setup startboard and game mills
	runGame(&GamePlayer1, &GamePlayer2);

}


int main() {
#ifdef  defined(__APPLE__) || defined(__unix__);
	setTerminalSettings();
#endif

	startGame();
#if  defined(__APPLE__) || defined(__unix__)
	resetTerminalSettings();
#elif defined(_WIN32) || defined(WIN32)
	_getch();

#endif
}
