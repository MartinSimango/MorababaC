#pragma once

#include "stdafx.h"

#define SERVER__PORT 3005

enum InstructionFromClient {
    PLAYER_MOVE=0 ,
    GET_WHOS_TURN,
    KILL_COW
};

enum InstructionFromServer {
    DO_NOTHING=0,
    MOVE_PIECE,
    REMOVE_PIECE,
    GAME_START,

};

struct network_data_st{
	enum InstructionFromClient CLIENT_INSTRUCTION;
   	enum InstructionFromServer SERVER_INSTRUCTION;
    int lastest_player_id;
    int current_player_id;
    char fromLet,toLet;
    int fromNum,toNum;

};

typedef struct network_data_st GAME_NETWORK_DATA;