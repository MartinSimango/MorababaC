#pragma once

#include "coordsList.h"

enum PlayerState { FLYING = 0, MOVING = 1, PLACING = 2 };


struct Player{
	char name[255];
	int id;
	char symbol;
	int numberOfPieces;
	enum PlayerState playerState;
	CoordsList * positions;
};

typedef struct Player PLAYER;

struct Game {
	CoordsList startBoard; 
	CoordsList *allBoardMills;
	PLAYER gamePlayer_1, gamePlayer_2,*currentPlayer;
	GAMEBOARD gameBoard;
	int whosTurn;



};

typedef struct Game GAME;
PLAYER * Game__CreatePlayer(char *name, int id, char symbol, int numberOfPieces, enum PlayerState playerState, CoordsList positions);
void Game__SetUpPlayers(GAME *game,const char *player_1_name,const char *player_2_name);
void Game__PrintBoard(const GAME *game);

void Game__AddPiece(GAME *game,PLAYER*player, const POINT_PTR toPoint);
void Game__RemovePiece(GAME *game,PLAYER*player, const POINT_PTR fromPoint); 
void Game__CheckStateChange(PLAYER*player);
void Game__PlaceMove(GAME *game,PLAYER*player, const POINT_PTR toPoint);
void Game__MovePiece(GAME *game,PLAYER*player, const POINT_PTR toPoint, const POINT_PTR fromPoint); 
void Game__UpdatePlayer(GAME *game,const POINT_PTR fromPoint, const POINT_PTR toPoint, PLAYER* player);

void init__Game(GAME *game,const char* player_1_name,const char *player_2_name);

struct Coords * Game__GetPlayerMills(GAME *game,PLAYER *player);

int Game__IsValidPlace(const GAME *game,const POINT_ pos);
int Game__IsValidFrom(const GAME *game,POINT_ pos, const PLAYER*player);
int Game__IsValidTo(const GAME *game,POINT_ pos, PLAYER *player);

PLAYER * Game__PlayerFrom(PLAYER *player);

void create__allBoardMills(GAME *game);
void create__startBoard(GAME *game);

GAME * Game__FromGame(GAME *game);