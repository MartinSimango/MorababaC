#include "stdafx.h"

void setUpPlayers() {
#if defined(__APPLE__) || defined(__unix__) 

	strcpy(GamePlayer1.name, "Player 1");
	strcpy(GamePlayer2.name, "Player 1");


#elif defined(_WIN32) || defined(WIN32)

	strcpy_s(GamePlayer1.name,sizeof(GamePlayer1.name), "Player 1");
	strcpy_s(GamePlayer2.name, sizeof(GamePlayer1.name), "Player 2");

#endif

	GamePlayer1.id = 1;

	GamePlayer1.symbol = 'x';

	GamePlayer1.numberOfPieces = 4;

	GamePlayer1.playerState = PLACING;

	GamePlayer1.positions = (List*)malloc(sizeof(List));

	initList(GamePlayer1.positions);

	GamePlayer2.id = 2;

	GamePlayer2.symbol = 'o';

	GamePlayer2.numberOfPieces = 4;

	GamePlayer2.playerState = PLACING;

	GamePlayer2.positions = (List*)malloc(sizeof(List));

	initList(GamePlayer2.positions);


}
//     

//                                         **************************GAMEBOARD***************************************************








void GamePrintBoard(int whosTurn) {

#if defined(__APPLE__) || defined(__unix__) 

	system("clear");

#elif defined(_WIN32) || defined(WIN32)

	system("@cls");

#endif

	char ps1 = ' ', ps2 = '*';
	if (whosTurn == 1) {

		ps1 = '*';
		ps2 = ' ';

	}
	printf("      1   2   3       4      5   6   7 \n\n");

	printf("  A  (%c)-------------(%c)------------(%c) \n", A1.symbol, A4.symbol, A7.symbol);
	printf("      |\\              |             /|\n");
	printf("      | \\             |            / |\n");
	printf("      |  \\            |           /  |\n");
	printf("  B   |  (%c)---------(%c)--------(%c)  |\n", B2.symbol, B4.symbol, B6.symbol);
	printf("      |   |\\          |         /|   |\n");
	printf("      |   | \\         |        / |   |\n");
	printf("      |   |  \\        |       /  |   |\n");
	printf("  C   |   |  (%c)-----(%c)----(%c)  |   |          %cPlayer 1 (%c)           %cPlayer 2 (%c)\n", C3.symbol, C4.symbol, C5.symbol, ps1, GamePlayer1.symbol, ps2, GamePlayer2.symbol);
	printf("      |   |   |              |   |   |          ----------              ----------\n");
	printf("      |   |   |              |   |   |          Unplaced Cows : %d       Unplaced Cows : %d\n", GamePlayer1.numberOfPieces, GamePlayer2.numberOfPieces);
	printf("  D  (%c)-(%c)-(%c)            (%c)-(%c)-(%c)         Cows alive : %d         Cows alive : %d\n", D1.symbol, D2.symbol, D3.symbol, D5.symbol, D6.symbol, D7.symbol, 12, 12);
	printf("      |   |   |              |   |   |          Cows killed : %d         Cows killed : %d\n", 0, 0);
	printf("      |   |   |              |   |   |\n");
	printf("  E   |   |  (%c)-----(%c)----(%c)  |   |\n", E3.symbol, E4.symbol, E5.symbol);
	printf("      |   |  /        |       \\  |   |\n");
	printf("      |   | /         |        \\ |   |\n");
	printf("      |   |/          |         \\|   |\n");
	printf("  F   |  (%c)---------(%c)--------(%c)  |\n", F2.symbol, F4.symbol, F6.symbol);
	printf("      |  /            |           \\  |\n");
	printf("      | /             |            \\ |\n");
	printf("      |/              |             \\|\n");
	printf("  G  (%c)-------------(%c)------------(%c)\n", G1.symbol, G4.symbol, G7.symbol);

	/*             board.[0].Symbol board.[1].Symbol board.[2].Symbol board.[3].Symbol board.[4].Symbol board.[5].Symbol board.[6].Symbol board.[7].Symbol board.[8].Symbol ps1 GamePlayer1.Symbol
	ps2 GamePlayer2.Symbol GamePlayer1.NumberOfPieces GamePlayer2.NumberOfPieces board.[9].Symbol board.[10].Symbol board.[11].Symbol board.[12].Symbol board.[13].Symbol board.[14].Symbol
	GamePlayer1.Positions.Length GamePlayer2.Positions.Length (12-(GamePlayer2.NumberOfPieces+GamePlayer2.Positions.Length)) (12-(GamePlayer1.NumberOfPieces+GamePlayer1.Positions.Length))
	board.[15].Symbol board.[16].Symbol board.[17].Symbol board.[18].Symbol board.[19].Symbol board.[20].Symbol board.[21].Symbol board.[22].Symbol board.[23].Symbol
	printf "%s" boardString*/
}
int GameIsValidPlace(struct Point pos) {
	for (int i = 0; i<CoordNum; i++) {

		struct Coords* element = getElementAt(&startBoard, i);

		if (element->pos.let == pos.let && element->pos.num == pos.num) {

			if (element->symbol == ' ') {

				return 1;
			}
		}
	}
	return 0;
}

int GameIsValidFrom(struct Point pos, struct Player*player) {
	struct Coords * coord = getCoords(&startBoard, pos);

	if (!coord) { //make sure the coord actually exists

		return 0;
	}
	return itemExits(player->positions, *coord);
}
int GameIsValidTo(struct Point pos, struct Player *player, enum PlayerState playerState) {
	struct Coords * coord = getCoords(&startBoard, pos);

	if (!coord) { //make sure the coord actually exists

		return 0;
	}

	if (!itemExits(&startBoard, *coord)) {

		return 0;
	}
	if (playerState == FLYING) {

		return GameIsValidPlace(pos);
	}
	List *playerPositions = player->positions;
	for (int i = 0; i<player->positions->length; i++) {

		struct Coords *element = getElementAt(playerPositions, i);

		for (int j = 0; j<4; j++) { //max of 4 possible moves

			struct Coords *coord = getCoords(&startBoard, element->possibleMoves[j]);

			if (!coord) { //if the coord in the possibleMoves array is not valid

				continue;
			}

			if (isEqual(*getCoords(&startBoard, pos), *coord) && GameIsValidPlace(pos)) {

				return 1;
			}

		}
	}
	return 0;


}
void GameAddPiece(struct Player*player, const struct Point *toPoint) {

	if (!addItem(player->positions, getCoords(&startBoard, *toPoint))) {

		perror("Something really bad happened!(Add piece)");
		exit(EXIT_FAILURE);

	}
}
void GameRemovePiece(struct Player*player, const struct Point *fromPoint) {

	if (!removeItem(player->positions, *getCoords(&startBoard, *fromPoint))) { //should never happen

		perror("Something really bad happened!(Remove piece)");
		exit(EXIT_FAILURE);

	}
}
void GameCheckStateChange(struct Player*player) {

	switch (player->playerState) {

	case PLACING:

		if (player->numberOfPieces == 0) {

			player->playerState = MOVING;

		}

		break;

	case MOVING:

		if (player->positions->length == 3) {

			player->playerState = FLYING;

		}

		break;

	case FLYING:

		break;

	}


}
void GamePlaceMove(struct Player*player, const struct Point *toPoint) {

	struct Coords * coord = getCoords(&startBoard, *toPoint);
	coord->symbol = player->symbol;

	GameAddPiece(player, toPoint);
	player->numberOfPieces--;

	GameCheckStateChange(player);

}

void GameMovePiece(struct Player*player, const struct Point*toPoint, const struct Point*fromPoint) {

	struct Coords * coord = getCoords(&startBoard, *fromPoint);
	GameRemovePiece(player, fromPoint);

	coord->symbol = ' '; //make the coord you're moving from blank
	coord = getCoords(&startBoard, *toPoint);
	coord->symbol = player->symbol;

	GameAddPiece(player, toPoint);
}
void GameUpdatePlayer(const struct Point * fromPoint, const struct Point *toPoint, struct Player* player) {

	switch (player->playerState) {

	case PLACING:

		GamePlaceMove(player, toPoint);
		break;

	default:

		GameMovePiece(player, toPoint, fromPoint);
		break;

	}

}
struct Coords * GameGetPlayerMills(struct Player*player) {
	return 0; //to be completed
}

void setUpGame() {

	setUpStartBoard();
	createStartBoard();

	setUpMills();
	createMills();

	setUpPlayers();
}
