#pragma once

#include "stdafx.h"

#define SERVER__PORT 3005

enum instructionType {
    CONNECTED=0,
    MOVEMADE=1,
    GETGAME=2,
    PRINTBOARD=3
};


struct network_data_st{
    GAME * game;
	enum instructionType INSTRUCTION;
    int lastest_player_id;


};

typedef struct network_data_st GAME_NETWORK_DATA;