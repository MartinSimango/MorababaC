#include "stdafx.h"


//     

//                                         **************************GAMEBOARD***************************************************

PLAYER * Game__CreatePlayer(char *name, int id, char symbol, int numberOfPieces, enum PlayerState playerState, CoordsList* positions) {
	PLAYER * player = malloc(sizeof(PLAYER));
#if defined(__APPLE__) || defined(__unix__) 
	strcpy(player->name, name);

#elif defined(_WIN32) || defined(WIN32)
	strcpy_s(player->name, sizeof(player->name), name);
#endif
	player->symbol = symbol;
	player->numberOfPieces = numberOfPieces;
	player->playerState = playerState;
	player->positions = positions;
	player->id = id;
	return player;

}
void Game__SetUpPlayers(GAME *game,const char *player_1_name,const char *player_2_name) {
	
	CoordsList *player1_positions = malloc(sizeof(CoordsList));
	init__CoordsList(player1_positions);
	game->gamePlayer_1=*Game__CreatePlayer(player_1_name, 0, 'x', 4, PLACING, player1_positions);
	
	CoordsList *player2_positions = malloc(sizeof(CoordsList));
	init__CoordsList(player2_positions);
	game->gamePlayer_2 = *Game__CreatePlayer(player_2_name, 1, 'o', 4, PLACING, player2_positions);
}




void Game__PrintBoard(const GAME * game) {

	char ps1 = ' ', ps2 = '*';
	if (game->whosTurn == 0) {

		ps1 = '*';
		ps2 = ' ';

	}
	printf("      1   2   3       4      5   6   7 \n\n");

	printf("  A  (%c)-------------(%c)------------(%c) \n", 
		game->gameBoard.A1.symbol, 
		game->gameBoard.A4.symbol,
		game->gameBoard.A7.symbol);
	printf("      |\\              |             /|\n");
	printf("      | \\             |            / |\n");
	printf("      |  \\            |           /  |\n");
	printf("  B   |  (%c)---------(%c)--------(%c)  |\n", 	
		game->gameBoard.B2.symbol, 
		game->gameBoard.B4.symbol, 
		game->gameBoard.B6.symbol);
	printf("      |   |\\          |         /|   |\n");
	printf("      |   | \\         |        / |   |\n");
	printf("      |   |  \\        |       /  |   |\n");
	printf("  C   |   |  (%c)-----(%c)----(%c)  |   |          %cPlayer 1 (%c)           %cPlayer 2 (%c)\n", 
		game->gameBoard.C3.symbol, 
		game->gameBoard.C4.symbol, 
		game->gameBoard.C5.symbol, ps1, 
		game->gamePlayer_1.symbol, ps2, 
		game->gamePlayer_2.symbol);
	printf("      |   |   |              |   |   |          ----------              ----------\n");
	printf("      |   |   |              |   |   |          Unplaced Cows : %d       Unplaced Cows : %d\n", 
		game->gamePlayer_1.numberOfPieces, 
		game->gamePlayer_2.numberOfPieces);
	printf("  D  (%c)-(%c)-(%c)            (%c)-(%c)-(%c)         Cows alive : %d         Cows alive : %d\n",
		game->gameBoard.D1.symbol,
		game->gameBoard.D2.symbol, 
		game->gameBoard.D3.symbol, 
		game->gameBoard.D5.symbol, 
		game->gameBoard.D6.symbol, 
		game->gameBoard.D7.symbol, 12, 12);
	printf("      |   |   |              |   |   |          Cows killed : %d         Cows killed : %d\n", 0, 0);
	printf("      |   |   |              |   |   |\n");
	printf("  E   |   |  (%c)-----(%c)----(%c)  |   |\n", 
		game->gameBoard.E3.symbol, 
		game->gameBoard.E4.symbol, 
		game->gameBoard.E5.symbol);
	printf("      |   |  /        |       \\  |   |\n");
	printf("      |   | /         |        \\ |   |\n");
	printf("      |   |/          |         \\|   |\n");
	printf("  F   |  (%c)---------(%c)--------(%c)  |\n", 
		game->gameBoard.F2.symbol, 
		game->gameBoard.F4.symbol, 
		game->gameBoard.F6.symbol);
	printf("      |  /            |           \\  |\n");
	printf("      | /             |            \\ |\n");
	printf("      |/              |             \\|\n");
	printf("  G  (%c)-------------(%c)------------(%c)\n", 
		game->gameBoard.G1.symbol, 
		game->gameBoard.G4.symbol, 
		game->gameBoard.G7.symbol);

	/*             board.[0].Symbol board.[1].Symbol board.[2].Symbol board.[3].Symbol board.[4].Symbol board.[5].Symbol board.[6].Symbol board.[7].Symbol board.[8].Symbol ps1 game->gamePlayer_1.Symbol
	ps2 game->gamePlayer_2.Symbol game->gamePlayer_1.NumberOfPieces game->gamePlayer_2.NumberOfPieces board.[9].Symbol board.[10].Symbol board.[11].Symbol board.[12].Symbol board.[13].Symbol board.[14].Symbol
	game->gamePlayer_1.Positions.Length game->gamePlayer_2.Positions.Length (12-(game->gamePlayer_2.NumberOfPieces+game->gamePlayer_2.Positions.Length)) (12-(game->gamePlayer_1.NumberOfPieces+game->gamePlayer_1.Positions.Length))
	board.[15].Symbol board.[16].Symbol board.[17].Symbol board.[18].Symbol board.[19].Symbol board.[20].Symbol board.[21].Symbol board.[22].Symbol board.[23].Symbol
	printf "%s" boardString*/
}
int Game__IsValidPlace(const GAME *game,const POINT_ pos) {
	for (int i = 0; i<COORDNUM; i++) {

		struct Coords* element = CoordsList__getElementAt(&(game->startBoard), i);

		if (element->pos.let == pos.let && element->pos.num == pos.num) {

			if (element->symbol == ' ') {

				return 1;
			}
		}
	}
	return 0;
}

int Game__IsValidFrom(const GAME *game,POINT_ pos, const PLAYER*player){
	struct Coords * coord = CoordsList__getCoord(&(game->startBoard), pos);

	if (!coord) { //make sure the coord actually exists

		return 0;
	}
	return CoordsList__itemExits(player->positions, *coord);
}

int Game__IsValidTo(const GAME *game,POINT_ pos, PLAYER *player) {
	struct Coords * coord = CoordsList__getCoord(&(game->startBoard), pos);

	if (!coord) { //make sure the coord actually exists

		return 0;
	}

	if (!CoordsList__itemExits(&(game->startBoard), *coord)) {

		return 0;
	}
	if (player->playerState == FLYING) { //don't need to check the neighbours if FLYING

		return Game__IsValidPlace(game,pos);
	}
	CoordsList *playerPositions = player->positions;
	for (int i = 0; i<player->positions->length; i++) {

		struct Coords *element = CoordsList__getElementAt(playerPositions, i);

		for (int j = 0; j<COORD_MAXPOSSIBLEMOVES; j++) { //max of 4 possible moves

			struct Coords *coord = CoordsList__getCoord(&(game->startBoard), element->possibleMoves[j]);

			if (!coord) { //if the coord in the possibleMoves array is not valid

				continue;
			}

			if (Coords__isEqual(*CoordsList__getCoord(&(game->startBoard), pos), *coord) && Game__IsValidPlace(game,pos)) {

				return 1;

			}

		}
	}
	
	return 0;



}
void Game__AddPiece(GAME *game,PLAYER*player, const POINT_PTR toPoint){

	if (!CoordsList__addItem(player->positions, CoordsList__getCoord(&(game->startBoard), *toPoint))) {

		perror("Something really bad happened!(Add piece)");
		exit(EXIT_FAILURE);

	}
}

void Game__RemovePiece(GAME *game,PLAYER*player, const POINT_PTR fromPoint){

	if (!CoordsList__removeItem(player->positions, *CoordsList__getCoord(&(game->startBoard), *fromPoint))) { //should never happen
		perror("Something really bad happened!(Remove piece)");
		exit(EXIT_FAILURE);

	}
}
void Game__CheckStateChange(PLAYER*player){

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
void Game__PlaceMove(GAME *game,PLAYER*player, const POINT_PTR toPoint) {

	struct Coords * coord = CoordsList__getCoord(&(game->startBoard), *toPoint);
	coord->symbol = player->symbol;

	Game__AddPiece(game,player, toPoint);
	player->numberOfPieces--;

	Game__CheckStateChange(player);


}

void Game__MovePiece(GAME *game,PLAYER*player, const POINT_PTR toPoint, const POINT_PTR fromPoint) {

	struct Coords * coord = CoordsList__getCoord(&(game->startBoard), *fromPoint);
	Game__RemovePiece(game,player, fromPoint);

	coord->symbol = ' '; //make the coord you're moving from blank
	coord = CoordsList__getCoord(&(game->startBoard), *toPoint);
	coord->symbol = player->symbol;

	Game__AddPiece(game,player, toPoint);

}
void Game__UpdatePlayer(GAME *game,const POINT_PTR fromPoint, const POINT_PTR toPoint, PLAYER* player){

	switch (player->playerState) {

	case PLACING:

		Game__PlaceMove(game,player, toPoint);
		break;

	default:

		Game__MovePiece(game,player, toPoint, fromPoint);
		break;

	}
		game->whosTurn= (game->whosTurn+1)%2;
		if(game->whosTurn==0)
		{
			game->currentPlayer= &(game->gamePlayer_1);
		}
		else
		{
			game->currentPlayer= &(game->gamePlayer_2);
		}

}
struct Coords * Game__GetPlayerMills(GAME *game, PLAYER *player){
	return 0; //to be completed
}



void create__allBoardMills (GAME*game) {
	//all coordinate combinations that can form a mill CoordsList__addItem(game->allBoardMills,if all are occupied by the same player)

	game->allBoardMills = (CoordsList*)malloc(sizeof(CoordsList) * MILLNUM);

	init__CoordsList(game->allBoardMills);


	CoordsList__addItem(game->allBoardMills, *(game->gameBoard.AA17));
	CoordsList__addItem(game->allBoardMills, *(game->gameBoard.BB26));
	CoordsList__addItem(game->allBoardMills, *(game->gameBoard.CC35));

	CoordsList__addItem(game->allBoardMills, *(game->gameBoard.DD13));
	CoordsList__addItem(game->allBoardMills, *(game->gameBoard.DD57));
	CoordsList__addItem(game->allBoardMills, *(game->gameBoard.EE35));

	CoordsList__addItem(game->allBoardMills, *(game->gameBoard.FF26));
	CoordsList__addItem(game->allBoardMills, *(game->gameBoard.GG17));
	CoordsList__addItem(game->allBoardMills, *(game->gameBoard.AG11));

	CoordsList__addItem(game->allBoardMills, *(game->gameBoard.BF22));
	CoordsList__addItem(game->allBoardMills, *(game->gameBoard.CE33));
	CoordsList__addItem(game->allBoardMills, *(game->gameBoard.AC44));

	CoordsList__addItem(game->allBoardMills, *(game->gameBoard.EG44));
	CoordsList__addItem(game->allBoardMills, *(game->gameBoard.CE55));
	CoordsList__addItem(game->allBoardMills, *(game->gameBoard.BF66));

	CoordsList__addItem(game->allBoardMills, *(game->gameBoard.AG77));
	CoordsList__addItem(game->allBoardMills, *(game->gameBoard.AC13));
	CoordsList__addItem(game->allBoardMills, *(game->gameBoard.CA57));

	CoordsList__addItem(game->allBoardMills, *(game->gameBoard.GE13));
	CoordsList__addItem(game->allBoardMills, *(game->gameBoard.EG57));

	/*COORD_PTR *cor =getElementAt(game->allBoardMills,0);
	//cor;
	printf("Char: (%c,%d)\n",cor[2].pos.let,cor[2].pos.num);
	A1.symbol='B';
	printf("Char: %c \n",getElementAt(game->allBoardMills,0)->symbol);*/

}
void create__startBoard(GAME*game) {
	
	init__CoordsList(&(game->startBoard));
 
	 CoordsList__addItem(&(game->startBoard), &(game->gameBoard.A1));
	 CoordsList__addItem(&(game->startBoard), &(game->gameBoard.A4));
	 CoordsList__addItem(&(game->startBoard), &(game->gameBoard.A7));

	 CoordsList__addItem(&(game->startBoard), &(game->gameBoard.B2));
	 CoordsList__addItem(&(game->startBoard), &(game->gameBoard.B4));
	 CoordsList__addItem(&(game->startBoard), &(game->gameBoard.B6));

	 CoordsList__addItem(&(game->startBoard), &(game->gameBoard.C3));
	 CoordsList__addItem(&(game->startBoard), &(game->gameBoard.C4));
	 CoordsList__addItem(&(game->startBoard), &(game->gameBoard.C5));

	 CoordsList__addItem(&(game->startBoard), &(game->gameBoard.D1));
	 CoordsList__addItem(&(game->startBoard), &(game->gameBoard.D2));
	 CoordsList__addItem(&(game->startBoard), &(game->gameBoard.D3));
	 CoordsList__addItem(&(game->startBoard), &(game->gameBoard.D5));
	 CoordsList__addItem(&(game->startBoard), &(game->gameBoard.D6));
	 CoordsList__addItem(&(game->startBoard), &(game->gameBoard.D7));

	 CoordsList__addItem(&(game->startBoard), &(game->gameBoard.E3));
	 CoordsList__addItem(&(game->startBoard), &(game->gameBoard.E4));
	 CoordsList__addItem(&(game->startBoard), &(game->gameBoard.E5));

	 CoordsList__addItem(&(game->startBoard), &(game->gameBoard.F2));
	 CoordsList__addItem(&(game->startBoard), &(game->gameBoard.F4));
	 CoordsList__addItem(&(game->startBoard), &(game->gameBoard.F6));

	 CoordsList__addItem(&(game->startBoard), &(game->gameBoard.G1));
	 CoordsList__addItem(&(game->startBoard), &(game->gameBoard.G4));
	 CoordsList__addItem(&(game->startBoard), &(game->gameBoard.G7));
}
void init__Game(GAME *game,const char* player_1_name,const char *player_2_name){
	init__startBoard(&(game->gameBoard));
	create__startBoard(game);
	init__Mills(&(game->gameBoard));
	create__allBoardMills(game);
	Game__SetUpPlayers(game,player_1_name,player_2_name);
	game->whosTurn=0; //make it player 1's turn
	game->currentPlayer= &(game->gamePlayer_1);
}


PLAYER * Game__PlayerFrom(PLAYER *player) {
	return 
	Game__CreatePlayer(player->name, player->id, player->symbol,player->numberOfPieces, player->playerState,
					CoordsList__FromCoordList(player->positions));

}

GAME * Game__FromGame(GAME *game) {
	GAME *newGame = malloc(sizeof(GAME));
	newGame->whosTurn = game->whosTurn;
	newGame->allBoardMills= (CoordsList__FromCoordList(game->allBoardMills));
	//newGame->currentPlayer = Game__PlayerFrom(game->currentPlayer);
	
    // newGame->startBoard = *CoordsList__FromCoordList(&game->startBoard);
	/*for (int i = 0; i < game->startBoard.length; i++) {
		COORD_PTR coordToAdd = Coord__FromCoord(CoordsList__getElementAt(&(game->startBoard), i));
		CoordsList__addItem(&newGame->startBoard, coordToAdd);
	}*/

     newGame->gamePlayer_1 = *Game__PlayerFrom(&(game->gamePlayer_1));
	 newGame->gamePlayer_2 = *Game__PlayerFrom(&(game->gamePlayer_2));
	 if (newGame->whosTurn == 0)
	 {
		 newGame->currentPlayer = &(newGame->gamePlayer_1);
	 }
	 else
	 {
		 newGame->currentPlayer = &(newGame->gamePlayer_2);
	 }
	 newGame->gameBoard = *Gameboard__FromGameboard(&(game->gameBoard));
	 create__startBoard(newGame);
	//  init__Mills(&(newGame->gameBoard)); //reinitilize the mills to correspond to this newboards mills
										 // so that A1 corresponds to this A1 and not the old boards A1



	return newGame;

}

