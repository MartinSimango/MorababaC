#pragma once

#include "List.h"

enum PlayerState { FLYING = 0, MOVING = 1, PLACING = 2 };

struct Player {
	char name[255];
	int id;
	char symbol;
	int numberOfPieces;
	enum PlayerState playerState;
	List * positions;
}GamePlayer1, GamePlayer2;



void setUpPlayers();
void GamePrintBoard(int whosTurn);
int GameIsValidPlace(struct Point pos);
int GameIsValidFrom(struct Point pos, struct Player*player);
int GameIsValidTo(struct Point pos, struct Player *player, enum PlayerState playerState);
void GameAddPiece(struct Player*player, const struct Point *toPoint);
void GameRemovePiece(struct Player*player, const struct Point *fromPoint);
void GamePheckStateChange(struct Player*player);
void GamePlaceMove(struct Player*player, const struct Point *toPoint);
void GameMovePiece(struct Player*player, const struct Point*toPoint, const struct Point*fromPoint);
void GameUpdatePlayer(const struct Point * fromPoint, const struct Point *toPoint, struct Player* player);
struct Coords * GameGetPlayerMills(struct Player*player);
void setUpGame();
