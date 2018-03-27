// Moraba.cpp : Defines the entry point for the console application.
//ab

#include "stdafx.h"


#if defined(__APPLE__) || defined(__unix__)                   /* __unix__ is usually defined by compilers targeting Unix systems */	
    void setTerminalSettings();
    void resetTerminalSettings();
#endif

struct Point getPos(char * what);
void getPlayerMove(GAME *Morabaraba,struct Point * fromPoint, struct Point *toPoint, struct Player* player);
void runGame(GAME *Morabaraba);
void startGame();
